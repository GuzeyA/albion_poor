#pragma once
#include "includes.h"
#include "sdk.h"

struct PositionInfo
{
	Vector3 Pos;
	float Time;
};
struct MyPlayerData
{	
	bool bValid = false;
};
struct BaseObjectInfo
{
	GameObject* GameObject;
	uintptr_t TransformComponent;
	uintptr_t MainComponent;
	uintptr_t ComponentMono;
};
namespace GlobalUnityVariables
{
	uintptr_t MainCamera;
	BaseObjectInfo LocalPlayerInfo;
}

class UnityEngine
{
public:
	static bool ValidateEntity(uintptr_t main_compoment, unsigned int HashToCompare)
	{
		if (!Utils::IsValidPtr(main_compoment))
			return false;

		auto compoment_mono = *reinterpret_cast<Il2CppObject**>(main_compoment + Offset_MonoPtr);
		if (!Utils::IsValidPtr(compoment_mono) || reinterpret_cast<Il2CppClass*>(compoment_mono->klass) != compoment_mono->klass->_1.klass)
			return false;

		unsigned int HashedClassName = crypto::hash_string(compoment_mono->klass->_1.name);

		return (HashedClassName == HashToCompare);
	}
	static bool ValidateCamera(uintptr_t camera_compoment)
	{
		if (!Utils::IsValidPtr(camera_compoment))
			return false;

		auto compoment_mono = *reinterpret_cast<Il2CppObject**>(camera_compoment + Offset_MonoPtr);
		if (!Utils::IsValidPtr(compoment_mono) || reinterpret_cast<Il2CppClass*>(compoment_mono->klass) != compoment_mono->klass->_1.klass)
			return false;

		unsigned int HashedClassName = crypto::hash_string(compoment_mono->klass->_1.name);

		return (HashedClassName == h("Camera") && *reinterpret_cast<bool*>(camera_compoment + 0x38));
	}
	static bool ValidateLocalPlayer(uintptr_t lplayer_compoment)
	{
		if (!Utils::IsValidPtr(lplayer_compoment))
			return false;

		auto compoment_mono = *reinterpret_cast<Il2CppObject**>(lplayer_compoment + Offset_MonoPtr);
		if (!Utils::IsValidPtr(compoment_mono) || reinterpret_cast<Il2CppClass*>(compoment_mono->klass) != compoment_mono->klass->_1.klass)
			return false;

		unsigned int HashedClassName = crypto::hash_string(compoment_mono->klass->_1.name);

		return (HashedClassName == h("LocalPlayerCharacterView"));
	}
	static uintptr_t GetMainCamera()
	{
		auto gameobjectmanager = GetGameObjectManager();
		uintptr_t MainCamera = 0;
		for (auto i = gameobjectmanager->ActiveObjects; std::uintptr_t(i) != std::uintptr_t(&gameobjectmanager->LastActiveObject); i = i->nextObjectLink)
		{
			if (!Utils::IsValidPtr(i))
				continue;

			auto gameobject = i->object;

			auto component_size = *reinterpret_cast<int32_t*>(std::uintptr_t(gameobject) + Offset_ComponentsSize);
			auto components_ptr = *reinterpret_cast<uintptr_t*>(std::uintptr_t(gameobject) + Offset_ComponentsPtr);

			for (auto compoment_index = 0; compoment_index < component_size; compoment_index++)
			{
				auto current_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (compoment_index * 0x10) + 0x8);
				if (!current_compoment)
					continue;

				auto compoment_mono = *reinterpret_cast<Il2CppObject**>(current_compoment + Offset_MonoPtr);
				if (!compoment_mono || reinterpret_cast<Il2CppClass*>(compoment_mono->klass) != compoment_mono->klass->_1.klass)
					continue;

				unsigned int HashedClassName = crypto::hash_string(compoment_mono->klass->_1.name);

				if (HashedClassName == h("Camera"))
				{
					if (*reinterpret_cast<bool*>(current_compoment + 0x38))
					{
						MainCamera = current_compoment;
						return MainCamera;
					}
				}
			}
		}
		return 0;
	}
	static BaseObjectInfo GetLocalInfo()
	{
		auto gameobjectmanager = GetGameObjectManager();
		//GlobalUnityVariables::LocalPlayerInfo.GameObject = 0;
		//GlobalUnityVariables::LocalPlayerInfo.TransformComponent = 0;
		BaseObjectInfo Ret = { 0, 0, 0, 0 };
		for (auto i = gameobjectmanager->CurrentObjects; std::uintptr_t(i) != std::uintptr_t(&gameobjectmanager->LastCurrentObject); i = i->nextObjectLink) {
			if (!Utils::IsValidPtr(i))
				continue;

			auto gameobject = i->object;

			auto component_size = *reinterpret_cast<int32_t*>(std::uintptr_t(gameobject) + Offset_ComponentsSize);
			auto components_ptr = *reinterpret_cast<uintptr_t*>(std::uintptr_t(gameobject) + Offset_ComponentsPtr);

			for (auto compoment_index = 0; compoment_index < component_size; compoment_index++) {
				auto current_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (compoment_index * 0x10) + 0x8);
				if (!current_compoment)
					continue;

				auto compoment_mono = *reinterpret_cast<Il2CppObject**>(current_compoment + Offset_MonoPtr);
				if (!compoment_mono || reinterpret_cast<Il2CppClass*>(compoment_mono->klass) != compoment_mono->klass->_1.klass)
					continue;

				unsigned int HashedClassName = crypto::hash_string(compoment_mono->klass->_1.name);

				if (HashedClassName == h("LocalPlayerCharacterView"))
				{
					auto transform_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);

					Ret.GameObject = gameobject;
					Ret.TransformComponent = transform_compoment;
					Ret.MainComponent = current_compoment;
					Ret.ComponentMono = (uintptr_t)compoment_mono;
					return Ret;
				}
			}
		}
		return Ret;
	}
	static game_object_manager* GetGameObjectManager()
	{
		return *(game_object_manager**)(Address_GameObjectManager);
	}
	static bool WorldToScreen(const Vector3& position, Vector2& output, float DirectionUpScale)
	{
		const auto& io = ImGui::GetIO();

		const auto matrix = *reinterpret_cast<Matrix4x4*>(GlobalUnityVariables::MainCamera + 0xDC);
		auto translation = matrix.GetColumn(3);
		const auto up = matrix.GetColumn(1);
		translation += up * DirectionUpScale;
		const auto w = translation.Dot(position) + matrix[3][3];

		if (w < 0.098f)
		{
			return false;
		}

		const auto right = matrix.GetColumn(0);


		const auto x = right.Dot(position) + matrix[3][0];
		const auto y = up.Dot(position) + matrix[3][1];

		output.x = (io.DisplaySize[0] * 0.5f) * (1.f + (x / w));
		output.y = (io.DisplaySize[1] * 0.5f) * (1.f - (y / w));

		return true;
	}
	static bool WorldToScreen(const Vector3& position, Vector2& output)
	{
		const auto& io = ImGui::GetIO();

		const auto matrix = *reinterpret_cast<Matrix4x4*>(GlobalUnityVariables::MainCamera + 0xDC);
		const auto translation = matrix.GetColumn(3);
		const auto w = translation.Dot(position) + matrix[3][3];

		if (w < 0.098f)
		{
			return false;
		}

		const auto right = matrix.GetColumn(0);
		const auto up = matrix.GetColumn(1);

		const auto x = right.Dot(position) + matrix[3][0];
		const auto y = up.Dot(position) + matrix[3][1];

		output.x = (io.DisplaySize[0] * 0.5f) * (1.f + (x / w));
		output.y = (io.DisplaySize[1] * 0.5f) * (1.f - (y / w));

		return true;
	}
	static void WorldToScreenOut(const Vector3& position, Vector2& output)
	{
		const auto& io = ImGui::GetIO();

		const auto matrix = *reinterpret_cast<Matrix4x4*>(GlobalUnityVariables::MainCamera + 0xDC);
		const auto translation = matrix.GetColumn(3);
		const auto w = translation.Dot(position) + matrix[3][3];

		const auto right = matrix.GetColumn(0);
		const auto up = matrix.GetColumn(1);

		const auto x = right.Dot(position) + matrix[3][0];
		const auto y = up.Dot(position) + matrix[3][1];

		output.x = (io.DisplaySize[0] * 0.5f) * (1.f + (x / w));
		output.y = (io.DisplaySize[1] * 0.5f) * (1.f - (y / w));
	}
	static uint64_t GetComponentByID(uint64_t ComponentList, int id)
	{
		return *reinterpret_cast<uintptr_t*>(ComponentList + (0x8 + (id * 0x10)));
	}

	static std::string GetComponentName(uintptr_t complist, int index)
	{
		if (index == 0)
			return "Transform";

		uint64_t comp = GetComponentByID(complist, index);

		uint64_t fields = *reinterpret_cast<uintptr_t*>(comp + 0x28);//Ilcpp2Object

		uint64_t klass = *reinterpret_cast<uintptr_t*>(fields);//Il2CppClass

		uint64_t ptrname = *reinterpret_cast<uintptr_t*>(klass + 0x10);//Name

		return (char*)(ptrname);
	}

	static Vector3 GetPosition(uint64_t transform_internal) {
		auto some_ptr = *reinterpret_cast<uint64_t*>(transform_internal + 0x38);
		auto index = *reinterpret_cast<int32_t*>(transform_internal + 0x38 + sizeof(uint64_t));
		if (!some_ptr)
			return Vector3();

		auto relation_array = *reinterpret_cast<uint64_t*>(some_ptr + 0x18);
		if (!relation_array)
			return Vector3();

		auto dependency_index_array = *reinterpret_cast<uint64_t*>(some_ptr + 0x20);
		if (!dependency_index_array)
			return Vector3();

		__m128i temp_0;
		__m128 xmmword_1410D1340 = { -2.f, 2.f, -2.f, 0.f };
		__m128 xmmword_1410D1350 = { 2.f, -2.f, -2.f, 0.f };
		__m128 xmmword_1410D1360 = { -2.f, -2.f, 2.f, 0.f };
		__m128 temp_1;
		__m128 temp_2;
		auto temp_main = *reinterpret_cast<__m128*>(relation_array + index * 48);
		auto dependency_index = *reinterpret_cast<int32_t*>(dependency_index_array + 4 * index);

		while (dependency_index >= 0) {
			auto relation_index = 6 * dependency_index;

			temp_0 = *reinterpret_cast<__m128i*>(relation_array + 8 * relation_index + 16);
			temp_1 = *reinterpret_cast<__m128*>(relation_array + 8 * relation_index + 32);
			temp_2 = *reinterpret_cast<__m128*>(relation_array + 8 * relation_index);

			__m128 v10 = _mm_mul_ps(temp_1, temp_main);
			__m128 v11 = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, 0));
			__m128 v12 = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, 85));
			__m128 v13 = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, -114));
			__m128 v14 = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, -37));
			__m128 v15 = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, -86));
			__m128 v16 = _mm_castsi128_ps(_mm_shuffle_epi32(temp_0, 113));
			__m128 v17 = _mm_add_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v11, xmmword_1410D1350), v13),
								_mm_mul_ps(_mm_mul_ps(v12, xmmword_1410D1360), v14)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), -86))),
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v15, xmmword_1410D1360), v14),
								_mm_mul_ps(_mm_mul_ps(v11, xmmword_1410D1340), v16)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 85)))),
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v12, xmmword_1410D1340), v16),
								_mm_mul_ps(_mm_mul_ps(v15, xmmword_1410D1350), v13)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0))),
						v10)),
				temp_2);

			temp_main = v17;
			dependency_index = *reinterpret_cast<int32_t*>(dependency_index_array + 4 * dependency_index);
		}

		return *reinterpret_cast<Vector3*>(&temp_main);
	}
};