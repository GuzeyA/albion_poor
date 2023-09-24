#pragma once
#include "includes.h"
#include "sdk.h"
#include "unityengine.h"
#include "aimbot.h"
#include "esp.h"
#include "misc.h"
#include "conditions.h"

std::string string_To_UTF8(const std::wstring& str)
{
	//int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	//wchar_t* pwBuf = new wchar_t[nwLen + 1];
	//ZeroMemory(pwBuf, nwLen * 2 + 2);

	//::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	//delete[]pwBuf;
	delete[]pBuf;

	//pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

//static void DrawActorOnRadar(const Vector3& DeltaFromLocal, const UniqueColor& col, const std::string& UpperText, const std::string& LowerText)
//{
//
//	auto CheatVars = GET_SETVAR(m_CheatVars, C_CheatVars);
//
//	if (DeltaFromLocal.x > CheatVars.zoom || DeltaFromLocal.x < -CheatVars.zoom)
//		return;
//
//	if (DeltaFromLocal.z > CheatVars.zoom || DeltaFromLocal.z < -CheatVars.zoom)
//		return;
//
//	float RelX = DeltaFromLocal.z / CheatVars.zoom * (CheatVars.sizex / 2);
//	float RelY = DeltaFromLocal.x / CheatVars.zoom * (CheatVars.sizey / 2);
//
//	ImGui::SetWindowFontScale(CheatVars.TextScale);
//
//	float PointSize = 5 * CheatVars.PointScale;
//	//float X = CheatVars.posx + (CheatVars.sizex / 2) + RelX - (PointSize / 2);
//	//float Y = CheatVars.posy + (CheatVars.sizey / 2) + RelY - (PointSize / 2);
//
//	//X = X * cos(DEG2RAD(CheatVars.angle1)) + Y * sin(DEG2RAD(CheatVars.angle1));
//	//Y = -X * sin(DEG2RAD(CheatVars.angle2)) + Y * cos(DEG2RAD(CheatVars.angle2));
//
//	//X = (X / sqrt(2)) - (Y / sqrt(2));
//	//Y = (X / sqrt(2)) + (Y / sqrt(2));
//
//	if (!UpperText.empty())
//		Drawing::DrawString({ X, Y }, UpperText.c_str(), UniqueColor(255, 255, 255), UniqueAlignment::Alignment_Bottom | UniqueAlignment::Alignment_Center_x);
//	Drawing::DrawFilledRect({ X - PointSize / 2, Y - PointSize / 2 }, { PointSize + 1, PointSize + 1 }, col);
//	Drawing::DrawOutlinedRect({ X - 1 - PointSize / 2, Y - 1 - PointSize / 2 }, { PointSize + 2, PointSize + 2 }, UniqueColor(0, 0, 0, 255));
//	if (!LowerText.empty())
//		Drawing::DrawString({ X, Y + (PointSize / 2) + 1 }, LowerText.c_str(), UniqueColor(255, 255, 255), /*UniqueAlignment::Alignment_Top |*/ UniqueAlignment::Alignment_Center_x);
//
//	ImGui::SetWindowFontScale(1.f);
//}

//#include "directx_helper.hpp"


//bool world_to_screen(uintptr_t main_camera, ImVec2 DisplaySize, const Vector3& world, Vector3& screen_out) {
//	D3DXMATRIX m_world;
//	d3d_helper::tmpD3DXMatrixIdentity(&m_world);
//
//	//auto& io = ImGui::GetIO();
//	auto display = DisplaySize;
//	auto w = display.x;
//	auto h = display.y;
//
//	D3DVIEWPORT9 v_viewport;
//	v_viewport.X = 0;
//	v_viewport.Y = 0;
//	v_viewport.Width = w;
//	v_viewport.Height = h;
//	v_viewport.MinZ = 1.f;
//	v_viewport.MaxZ = 0.f;
//
//	auto screen_v = D3DXVECTOR3();
//	auto world_v = D3DXVECTOR3();
//	world_v.x = world.x;
//	world_v.y = world.z;
//	world_v.z = world.y;
//
//	auto projection_matrix = reinterpret_cast<D3DMATRIX*>(main_camera + 0x9C); //Camera::GetProjectionMatrix
//	auto view_matrix = reinterpret_cast<D3DMATRIX*>(main_camera + 0x5C); //Camera::GetWorldToCameraMatrix
//
//	d3d_helper::tmpD3DXVec3Project(&screen_v, &world_v, &v_viewport, projection_matrix, view_matrix, &m_world);
//
//	if (screen_v.z < 0.0001f) {
//		screen_out.x = -1;
//		screen_out.y = -1;
//		return false;
//	}
//
//	screen_out.x = screen_v.x / w * w;
//	screen_out.y = screen_v.y / h * h;
//
//	return true;
//}
//bool W2S(const Vector3& world, Vector3& screen_out)
//{
//	world_to_screen
//}
enum class MyMobType : uint32_t
{
	Boss,
	MiniBoss,
	Wood,
	Rock,
	Ore,
	Fiber,
	Hide,
	WispDefault,
	WispUncommon,
	WispRare,
	WispEpic,
	WispLegendary,
	MistsBoss,
	ChestHidden,
	AvalonDrone,
	Hostile,
	DungeonSolo,
	DungeonCorrupt,
	DungeonHellgate,
	DungeonGroup,
	DungeonMist,
	ChestLootBag,
	MAX_MOB_TYPE
};
struct BasicTypeInfo
{
	unsigned int ResourceTypeHash;
	MyMobType MobType;

};

struct EntityData_s
{
	uintptr_t MainComponent;
	uintptr_t TransformComponent;
	unsigned int HashedClassName;

	void* ComponentMono;
	void* GameObject;
	//uintptr_t ComponentPtr;

	BasicTypeInfo TypeInfo;
};

std::vector<EntityData_s> MyEntityList;
std::vector<EntityData_s> MyFarEntityList;


bool SpecialCaseResources(unsigned int ResourseNameHash, int& Tier, int& Rarity)
{
	if (ResourseNameHash == h("hui"))
	{
		Tier = 4;
		Rarity = 6;
		return true;
	}
	return false;
}

class AlbionHack
{
private:
	static bool IsValidEntity(uintptr_t Entity)
	{
		return (Entity > 0x1000000000 && Entity < 0x30000000000);
	}
	static bool IsValidEntityVTable(uintptr_t EntityVTable)
	{
		return (EntityVTable > (uintptr_t)GlobalVars::g_hModuleBase && EntityVTable < GlobalVars::g_pModuleEnd);
	}
	static void EntityHandler(C_CheatVars* CheatVars, std::vector<EntityData_s>& TmpEntityList, std::vector<EntityData_s>& TmpFarEntityList)
	{
	
		__try
		{
			GlobalUnityVariables::LocalPlayerInfo = UnityEngine::GetLocalInfo();
			uint32_t MyHashedAlliance = 0;
			uint32_t MyHashedGuild = 0;
			//if (Utils::IsValidPtr(GlobalUnityVariables::LocalPlayerInfo.ComponentMono))
			//{
			//	Utils::Print("1\n");
			//	uintptr_t LocalPlayerInfo = Utils::SecureCall<uintptr_t>((void*)Address_GetPlayerInfo, GlobalUnityVariables::LocalPlayerInfo.ComponentMono);
			//	Utils::Print("2\n");
			//	if (Utils::IsValidPtr(LocalPlayerInfo))
			//	{
			//		Utils::Print("3\n");
			//		System_String_o* LocalAliance = *(System_String_o**)((uintptr_t)LocalPlayerInfo + Offset_PlInfoAliance);
			//		if (Utils::IsValidPtr(LocalAliance))
			//		{
			//			Utils::Print("4\n");
			//			MyHashedAlliance = crypto::hash_string((wchar_t*)&LocalAliance->fields.m_firstChar);
			//		}
			//		Utils::Print("5\n");
			//		System_String_o* LocalGuild = *(System_String_o**)((uintptr_t)LocalPlayerInfo + Offset_PlInfoGuild);
			//		if (Utils::IsValidPtr(LocalGuild))
			//		{
			//			Utils::Print("6\n");
			//			MyHashedGuild = crypto::hash_string((wchar_t*)&LocalGuild->fields.m_firstChar);
			//		}
			//		Utils::Print("7\n");
			//	}
			//	Utils::Print("8\n");
			//}
			if (CheatVars->Radar)
			{	
				//Utils::Print("9\n");
				auto gameobjectmanager = UnityEngine::GetGameObjectManager();

				if (!Utils::IsValidPtr(gameobjectmanager))
					return;

				for (auto i = gameobjectmanager->CurrentObjects; std::uintptr_t(i) != std::uintptr_t(&gameobjectmanager->LastCurrentObject); i = i->nextObjectLink) {
					
					if (!Utils::IsValidPtr(i))
						continue;

					auto gameobject = i->object;

					if (!Utils::IsValidPtr(gameobject))
						continue;

					auto component_size = *reinterpret_cast<int32_t*>(std::uintptr_t(gameobject) + Offset_ComponentsSize);
					auto components_ptr = *reinterpret_cast<uintptr_t*>(std::uintptr_t(gameobject) + Offset_ComponentsPtr);

					if (!Utils::IsValidPtr(components_ptr))
						continue;

					for (auto compoment_index = 0; compoment_index < component_size; compoment_index++) {
						auto current_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (compoment_index * 0x10) + 0x8);
						if (!current_compoment)
							continue;

						auto compoment_mono = *reinterpret_cast<Il2CppObject**>(current_compoment + Offset_MonoPtr);

						if (!Utils::IsValidPtr(compoment_mono))
							continue;

						if (!compoment_mono || reinterpret_cast<Il2CppClass*>(compoment_mono->klass) != compoment_mono->klass->_1.klass)
							continue;

						//auto szName = compoment_mono->klass->_1.name;
						unsigned int HashedClassName = crypto::hash_string(compoment_mono->klass->_1.name);

						if (HashedClassName == h("RemotePlayerCharacterView"))
						{
							auto Player = (RemotePlayerCharacterView_o*)compoment_mono;
							//static auto getnamefnptr = Player->klass->vtable._99_get_Name.methodPtr;

							auto transform_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);

							if (!Utils::IsValidPtr(transform_compoment))
								continue;

							//uintptr_t PlayerInfo = Utils::SecureCall<uintptr_t>((void*)Address_GetPlayerInfo, Player);

							//if (!Utils::IsValidPtr(PlayerInfo))
							//	continue;

							//System_String_o* PlAliance = *(System_String_o**)((uintptr_t)PlayerInfo + Offset_PlInfoAliance);
							//System_String_o* PlGuild = *(System_String_o**)((uintptr_t)PlayerInfo + Offset_PlInfoGuild);
							//bool PlInParty = *(bool*)((uintptr_t)PlayerInfo + Offset_PlInfoInParty);

							Vector3 PlayerPos = UnityEngine::GetPosition(transform_compoment);

							if (CheatVars->FilterPlayers /*&& Condition::PlayerCheck(PlAliance, PlGuild, PlInParty, MyHashedAlliance, MyHashedGuild, CheatVars)*/)
							{
								EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Player, gameobject, {0, MyMobType::MAX_MOB_TYPE} };
								TmpEntityList.push_back(Tmp);
								//wchar_t* PlayerName = (wchar_t*)&Utils::SecureCall<System_String_o*>(getnamefnptr, Player)->fields.m_firstChar;
								//auto Format = xorstr("[%i m]");
								//MY_FORMAT_A(Format.crypt_get(), (int)PlayerPos.Distance(GlobalUnityVariables::LocalPlayerInfo.Position));
								//Esp::DrawEspRadar(PlayerPos, UniqueColor(255, 0, 0), CheatVars->PlayersName ? string_To_UTF8(PlayerName) : "", CheatVars->PlayersDistance ? Buffer : "");
							}
						}
						else if (HashedClassName == h("Harvestable"))
						{
							auto Harvestable = (Harvestable_o*)compoment_mono;

							auto transform_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);

							if (!Utils::IsValidPtr(transform_compoment))
								continue;

							Vector3 ItemPos = UnityEngine::GetPosition(transform_compoment);

							if (CheatVars->FilterResources)
							{
								wchar_t* ResourceType = (wchar_t*)&Harvestable->fields.ResourceType->fields.m_firstChar;
								unsigned int ResourceHash = crypto::hash_string(ResourceType);

								//auto Format = xorstr("[%i m]");
								//MY_FORMAT_A(Format.crypt_get(), (int)ItemPos.Distance(GlobalUnityVariables::LocalPlayerInfo.Position));

								if (CheatVars->ResourcesDebug)
								{
									EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Harvestable, gameobject,  {0, MyMobType::MAX_MOB_TYPE} };
									TmpFarEntityList.push_back(Tmp);
									//std::string Str = string_To_UTF8(ResourceType) + " " + std::to_string(Harvestable->fields.Charges) + " " + std::to_string(Harvestable->fields.Tier) + "." + std::to_string(Harvestable->fields.RareState);
									//Esp::DrawEspRadar(ItemPos, UniqueColor(144, 0, 230), Str, CheatVars->ResourcesDistance ? Buffer : "");
								}
								else
								{
									if (Harvestable->fields.Charges > 0)
									{
										//std::string Str = /*string_To_UTF8(ResourceType) + " " +*/ std::to_string(Harvestable->fields.Tier) + "." + std::to_string(Harvestable->fields.RareState);

										if (ResourceHash == h("WOOD") || ResourceHash == h("WOOD_GIANTTREE"))
										{
											if (CheatVars->FilterWood)
											{
												if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityWood))
												{
													EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Harvestable, gameobject, {ResourceHash, MyMobType::MAX_MOB_TYPE} };
													TmpFarEntityList.push_back(Tmp);
												}
												//Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->WoodColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											}
										}
										else if (ResourceHash == h("ROCK"))
										{
											if (CheatVars->FilterRock)
											{
												if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityRock))
												{
													EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Harvestable, gameobject, {ResourceHash, MyMobType::MAX_MOB_TYPE} };
													TmpFarEntityList.push_back(Tmp);
												}
												//Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->RockColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											}
										}
										else if (ResourceHash == h("ORE"))
										{
											if (CheatVars->FilterOre)
											{
												if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityOre))
												{
													EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Harvestable, gameobject, {ResourceHash, MyMobType::MAX_MOB_TYPE} };
													TmpFarEntityList.push_back(Tmp);
												}
												//Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->OreColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											}
										}
										else if (ResourceHash == h("FIBER"))
										{
											if (CheatVars->FilterFiber)
											{
												if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityFiber))
												{
													EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Harvestable, gameobject, {ResourceHash, MyMobType::MAX_MOB_TYPE} };
													TmpFarEntityList.push_back(Tmp);
												}
												//Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->FiberColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											}
										}
										else if (ResourceHash == h("HIDE"))
										{
											if (CheatVars->FilterHide)
											{
												if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityHide))
												{
													EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Harvestable, gameobject, {ResourceHash, MyMobType::MAX_MOB_TYPE} };
													TmpFarEntityList.push_back(Tmp);
												}
												//Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->HideColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											}
										}
									}
								}
							}
						}
						else if (HashedClassName == h("MobView"))
						{
							auto Mob = (MobView_o*)compoment_mono;
							if (CheatVars->FilterMobs)
							{
								uintptr_t mobptr = *reinterpret_cast<uintptr_t*>((uintptr_t)Mob + 0x18);
								if (!Utils::IsValidPtr(mobptr))
									continue;

								uintptr_t mob2 = *reinterpret_cast<uintptr_t*>(mobptr + Offset_Mob2);
								if (!Utils::IsValidPtr(mob2))
									continue;

								uintptr_t mob3 = *reinterpret_cast<uintptr_t*>(mob2 + Offset_Mob3);
								if (!Utils::IsValidPtr(mob3))
									continue;

								auto transform_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);

								if (!Utils::IsValidPtr(transform_compoment))
									continue;

								Vector3 MobPos = UnityEngine::GetPosition(transform_compoment);

								//wchar_t* name = reinterpret_cast<wchar_t*>(mob3 + Offset_MobName);

								int MobRare = *reinterpret_cast<int*>(mobptr + Offset_MabRare);
								int MobTier = *reinterpret_cast<int*>(mob2 + Offset_MobTier);


								uintptr_t pMob = Utils::SecureCall<uintptr_t>((void*)Address_GetMob, Mob);
								if (!Utils::IsValidPtr(pMob))
									continue;

								bd5_o* pMobInfo = Utils::SecureCall<bd5_o*>((void*)Address_GetMobInfo, pMob);
								if (!Utils::IsValidPtr(pMobInfo))
									continue;

								//MobTypeCategory MobType = (MobTypeCategory)pMobInfo->fields.d7;
								//MobAlignments MobAlign = (MobAlignments)pMobInfo->fields.df;
								MobTypeCategory MobType = *(MobTypeCategory*)((uintptr_t)pMobInfo + Offset_MobTypeCategory);
								MobAlignments MobAlign = *(MobAlignments*)((uintptr_t)pMobInfo + Offset_MobAlignment);
								std::string_view obj_name = gameobject->Name;
								unsigned int MobNameHash = crypto::hash_string(gameobject->Name);

								//auto Format = xorstr("[%i m]");
								//MY_FORMAT_A(Format.crypt_get(), (int)MobPos.Distance(GlobalUnityVariables::LocalPlayerInfo.Position));

								//std::string Str = /*string_To_UTF8(ResourceType) + " " +*/ std::to_string(MobTier) + "." + std::to_string(MobRare);
								if (CheatVars->MobsDebug)
								{
									EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::MAX_MOB_TYPE } };
									TmpEntityList.push_back(Tmp);
									//std::string Str = string_To_UTF8(ResourceType) + " " + std::to_string(MobType) + " " + std::to_string(Harvestable->fields.Tier) + "." + std::to_string(Harvestable->fields.RareState);
									//Esp::DrawEspRadar(MobPos, UniqueColor(144, 0, 230), obj_name, CheatVars->MobsDistance ? Buffer : "");
								}
								else
								{
									if (MobType == Boss)
									{
										if (CheatVars->FilterMobBoss)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::Boss} };
											TmpEntityList.push_back(Tmp);
										}
										//Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobBossColor), xorstr_("Boss"), CheatVars->MobsDistance ? Buffer : "");
									}
									else if (MobType == MiniBoss)
									{
										if (CheatVars->FilterMobMiniBoss)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::MiniBoss} };
											TmpEntityList.push_back(Tmp);
										}
										//Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobMiniBossColor), xorstr_("Mini Boss"), CheatVars->MobsDistance ? Buffer : "");
									}
									else if (obj_name.find("_HIDE_") != std::string::npos)
									{
										if (CheatVars->FilterMobHide)
											if (Condition::TierCheck(MobTier, MobRare, CheatVars->RarityMobHide))
											{
												EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::Hide} };
												TmpEntityList.push_back(Tmp);
											}
										//Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobHideColor), Str, CheatVars->MobsDistance ? Buffer : "");
									}
									else if (obj_name.find("_ORE_") != std::string::npos)
									{
										if (CheatVars->FilterMobOre)
											if (Condition::TierCheck(MobTier, MobRare, CheatVars->RarityMobOre))
											{
												EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::Ore} };
												TmpEntityList.push_back(Tmp);
											}
										//Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobOreColor), Str, CheatVars->MobsDistance ? Buffer : "");
									}
									else if (obj_name.find("_FIBER_") != std::string::npos)
									{
										if (CheatVars->FilterMobFiber)
											if (Condition::TierCheck(MobTier, MobRare, CheatVars->RarityMobFiber))
											{
												EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::Fiber} };
												TmpEntityList.push_back(Tmp);
											}
										//Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobFiberColor), Str, CheatVars->MobsDistance ? Buffer : "");
									}
									else if (obj_name.find("_WOOD_") != std::string::npos)
									{
										if (CheatVars->FilterMobWood)
											if (Condition::TierCheck(MobTier, MobRare, CheatVars->RarityMobWood))
											{
												EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::Wood} };
												TmpEntityList.push_back(Tmp);
											}
										//Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobWoodColor), Str, CheatVars->MobsDistance ? Buffer : "");
									}
									else if (obj_name.find("_ROCK_") != std::string::npos)
									{
										if (CheatVars->FilterMobRock)
											if (Condition::TierCheck(MobTier, MobRare, CheatVars->RarityMobRock))
											{
												EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::Rock} };
												TmpEntityList.push_back(Tmp);
											}
										//Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobRockColor), Str, CheatVars->MobsDistance ? Buffer : "");
									}
									else if (obj_name.find("_WISP_LEGENDARY") != std::string::npos)
									{
										if (CheatVars->FilterMobWisp && CheatVars->FilterMobWispLegendary)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::WispLegendary} };
											TmpEntityList.push_back(Tmp);
										}
									}
									else if (obj_name.find("_WISP_RARE_") != std::string::npos)
									{
										if (CheatVars->FilterMobWisp && CheatVars->FilterMobWispEpic)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::WispEpic} };
											TmpEntityList.push_back(Tmp);
										}
									}
									else if (obj_name.find("_WISP_UNCOMMON") != std::string::npos)
									{
										if (CheatVars->FilterMobWisp && CheatVars->FilterMobWispRare)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::WispRare} };
											TmpEntityList.push_back(Tmp);
										}
									}
									else if (obj_name.find("_WISP_STANDART") != std::string::npos)
									{
										if (CheatVars->FilterMobWisp && CheatVars->FilterMobWispUncommon)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::WispUncommon} };
											TmpEntityList.push_back(Tmp);
										}
									}
									else if (obj_name.find("_WISP_") != std::string::npos)
									{
										if (CheatVars->FilterMobWisp && CheatVars->FilterMobWispDefault)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::WispDefault} };
											TmpEntityList.push_back(Tmp);
										}
									}
									else if (MobNameHash == h("MOB_ARCANE_CRYSTALSPIDER_BOSS_01"))
									{
										if (CheatVars->FilterMobMistsBoss)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::MistsBoss} };
											TmpEntityList.push_back(Tmp);
										}
									}
									else if (MobNameHash == h("MOB_MISTS_SPIDER_BOSS_01"))
									{
										if (CheatVars->FilterMobMistsBoss)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::MistsBoss} };
											TmpEntityList.push_back(Tmp);
										}
									}
									else if (MobNameHash == h("MOB_MISTS_GRIFFIN_BOSS_01"))
									{
										if (CheatVars->FilterMobMistsBoss)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::MistsBoss} };
											TmpEntityList.push_back(Tmp);
										}
									}
									else if (MobNameHash == h("MOB_ROAMING_CHEST_01"))
									{
										if (CheatVars->HiddenChestColor && CheatVars->RadarFilterChest)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::ChestHidden} };
											TmpEntityList.push_back(Tmp);
										}
									}
									else if (MobNameHash == h("MOB_AVALON_TREASURE_MINION"))
									{
										if (CheatVars->FilterMobAvalonTreasure && CheatVars->RadarFilterChest)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::AvalonDrone} };
											TmpEntityList.push_back(Tmp);
										}
									}
									else if (MobAlign == Hostile)
									{
										if (CheatVars->FilterMobHostile)
										{
											EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Mob, gameobject, {0, MyMobType::Hostile} };
											TmpEntityList.push_back(Tmp);
										}
									}
								}
							}
						}
						else if (HashedClassName == h("RandomDungeonExitObjectView"))
						{
							auto Dungeon = (Assets_Scripts_SimulationObjectViews_SimulationObjects_WorldObjects_StaticObjects_RandomDungeonExitObjectView_o*)compoment_mono;

							auto transform_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);

							if (!Utils::IsValidPtr(transform_compoment))
								continue;

							//uintptr_t DungeonInfo = Utils::SecureCall<uintptr_t>((void*)Address_GetDungeonInfo, Dungeon);

							//if (!Utils::IsValidPtr(DungeonInfo))
							//	continue;

							//uint8_t Enchantment = *(uint8_t*)((uintptr_t)DungeonInfo + Offset_DnInfoEnchant);

							Vector3 DungeonPos = UnityEngine::GetPosition(transform_compoment);
							std::string_view obj_name = gameobject->Name;
							//unsigned int DungeonNameHash = crypto::hash_string(gameobject->Name);

							if (obj_name.find("CORRUPT") != std::string::npos)
							{
								if (CheatVars->RadarFilterDungeon && CheatVars->FilterCorruptDungeon)
								{
									EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Dungeon, gameobject, {0, MyMobType::DungeonCorrupt} };
									TmpEntityList.push_back(Tmp);
								}
							}
							else if (obj_name.find("_SOLO_") != std::string::npos)
							{
								if (CheatVars->RadarFilterDungeon && CheatVars->FilterSoloDungeon /*&& Condition::EnchantCheck(Enchantment, CheatVars->EnchantmentSoloDungeon)*/)
								{
									EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Dungeon, gameobject, {0, MyMobType::DungeonSolo} };
									TmpEntityList.push_back(Tmp);
								}
							}
							else if (obj_name.find("_HELLGATE_") != std::string::npos)
							{
								if (CheatVars->RadarFilterDungeon && CheatVars->FilterHellgateDungeon)
								{
									EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Dungeon, gameobject, {0, MyMobType::DungeonHellgate} };
									TmpEntityList.push_back(Tmp);
								}
							}
							else if (obj_name.find("_WISP_") != std::string::npos)
							{
								if (CheatVars->RadarFilterDungeon && CheatVars->FilterMistsDungeon)
								{
									EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Dungeon, gameobject, {0, MyMobType::DungeonMist} };
									TmpEntityList.push_back(Tmp);
								}
							}
							else
							{
								if (CheatVars->RadarFilterDungeon && CheatVars->FilterGroupDungeon/* && Condition::EnchantCheck(Enchantment, CheatVars->EnchantmentGroupDungeon)*/)
								{
									EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, Dungeon, gameobject, {0, MyMobType::DungeonGroup} };
									TmpEntityList.push_back(Tmp);
								}
							}
						}
						else if (HashedClassName == h("LootObjectView"))
						{
							auto LootBag = compoment_mono;

							auto transform_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);

							if (!Utils::IsValidPtr(transform_compoment))
								continue;

							Vector3 LootBagPos = UnityEngine::GetPosition(transform_compoment);
							std::string_view obj_name = gameobject->Name;

							if (obj_name.find("_LOOTBAG_") != std::string::npos)
							{
								if (CheatVars->RadarFilterChest && CheatVars->FilterLootBag)
								{
									EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, LootBag, gameobject, {0, MyMobType::ChestLootBag} };
									TmpEntityList.push_back(Tmp);
								}
							}
						}
						else if (HashedClassName == h("Vfx"))
						{
							auto LootBag = compoment_mono;

							auto transform_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);

							if (!Utils::IsValidPtr(transform_compoment))
								continue;

							Vector3 LootBagPos = UnityEngine::GetPosition(transform_compoment);
							//std::string_view obj_name = gameobject->Name;
							unsigned int LootBagNameHash = crypto::hash_string(gameobject->Name);
							if (LootBagNameHash == h("fx_lootbag(Clone)"))
							{
								if (CheatVars->RadarFilterChest && CheatVars->FilterLootBag)
								{
									EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, LootBag, gameobject, {0, MyMobType::ChestLootBag} };
									TmpEntityList.push_back(Tmp);
								}
							}
						}
						else if (HashedClassName == h("HarvestableObjectView"))
						{
							auto HarvestableObjectView = (HarvestableObjectView_o*)compoment_mono;

							auto Harvestable = (Harvestable_o*)HarvestableObjectView->fields.d;

							//uintptr_t unk1 = *(uintptr_t*)((uintptr_t)HarvestableObjectView + 0x18);
							//uint32_t charges = *(uint32_t*)((uintptr_t)unk1 + 0x90);
							//uint32_t Maxcharges = *(uint32_t*)((uintptr_t)unk1 + 0x98);

							auto transform_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);

							if (!Utils::IsValidPtr(transform_compoment))
								continue;

							Vector3 ItemPos = UnityEngine::GetPosition(transform_compoment);

							if (CheatVars->FilterResources)
							{
								wchar_t* ResourceType = (wchar_t*)&Harvestable->fields.ResourceType->fields.m_firstChar;
								unsigned int ResourceHash = crypto::hash_string(ResourceType);

								//auto Format = xorstr("[%i m]");
								//MY_FORMAT_A(Format.crypt_get(), (int)ItemPos.Distance(GlobalUnityVariables::LocalPlayerInfo.Position));

								if (CheatVars->ResourcesDebug)
								{
									EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, HarvestableObjectView, gameobject,  {0, MyMobType::MAX_MOB_TYPE} };
									TmpEntityList.push_back(Tmp);
									//std::string Str = string_To_UTF8(ResourceType) + " " + std::to_string(Harvestable->fields.Charges) + " " + std::to_string(Harvestable->fields.Tier) + "." + std::to_string(Harvestable->fields.RareState);
									//Esp::DrawEspRadar(ItemPos, UniqueColor(144, 0, 230), Str, CheatVars->ResourcesDistance ? Buffer : "");
								}
								else
								{
									if (Harvestable->fields.Charges > 0)
									{
										//std::string Str = /*string_To_UTF8(ResourceType) + " " +*/ std::to_string(Harvestable->fields.Tier) + "." + std::to_string(Harvestable->fields.RareState);

										if (ResourceHash == h("WOOD") || ResourceHash == h("WOOD_GIANTTREE"))
										{
											if (CheatVars->FilterWood)
											{
												if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityWood))
												{
													EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, HarvestableObjectView, gameobject, {ResourceHash, MyMobType::MAX_MOB_TYPE} };
													TmpEntityList.push_back(Tmp);
												}
												//Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->WoodColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											}
										}
										else if (ResourceHash == h("ROCK"))
										{
											if (CheatVars->FilterRock)
											{
												if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityRock))
												{
													EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, HarvestableObjectView, gameobject, {ResourceHash, MyMobType::MAX_MOB_TYPE} };
													TmpEntityList.push_back(Tmp);
												}
												//Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->RockColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											}
										}
										else if (ResourceHash == h("ORE"))
										{
											if (CheatVars->FilterOre)
											{
												if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityOre))
												{
													EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, HarvestableObjectView, gameobject, {ResourceHash, MyMobType::MAX_MOB_TYPE} };
													TmpEntityList.push_back(Tmp);
												}
												//Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->OreColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											}
										}
										else if (ResourceHash == h("FIBER"))
										{
											if (CheatVars->FilterFiber)
											{
												if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityFiber))
												{
													EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, HarvestableObjectView, gameobject, {ResourceHash, MyMobType::MAX_MOB_TYPE} };
													TmpEntityList.push_back(Tmp);
												}
												//Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->FiberColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											}
										}
										else if (ResourceHash == h("HIDE"))
										{
											if (CheatVars->FilterHide)
											{
												if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityHide))
												{
													EntityData_s Tmp = { current_compoment, transform_compoment, HashedClassName, HarvestableObjectView, gameobject, {ResourceHash, MyMobType::MAX_MOB_TYPE} };
													TmpEntityList.push_back(Tmp);
												}
												//Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->HideColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		__except (1)
		{

		}
	}
	static void RadarFrame(C_CheatVars* CheatVars, ImGuiWindowFlags WindowFlags)
	{
		const auto& io = ImGui::GetIO();

		static ImVec2 PrevPos = { 256.f,256.f };
		static bool ShouldCheckAndClamp = false;
		//float NewPosX = std::clamp(PrevPos.x, 0.f, io.DisplaySize.x);
		//float NewPosY = std::clamp(PrevPos.y, 0.f, io.DisplaySize.y);

		if (ShouldCheckAndClamp && !Utils::myGetAsyncKeyState(0))
		{
			float NewPosX = std::clamp(PrevPos.x, 0.f, io.DisplaySize.x);
			float NewPosY = std::clamp(PrevPos.y, 0.f, io.DisplaySize.y);
			ImGui::SetNextWindowPos(ImVec2(NewPosX, NewPosY));

			WindowFlags |= ImGuiWindowFlags_NoMove;

			ShouldCheckAndClamp = false;
		}
		//ImGui::SetNextWindowPos(ImVec2(NewPosX, NewPosY));
		ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(io.DisplaySize.x, io.DisplaySize.y));

		if (ImGui::Begin(xorstr_("Radar"), &CheatVars->Radar, WindowFlags))
		{

			ImDrawList* draw_list = ImGui::GetWindowDrawList();

			ImVec2 winpos = ImGui::GetWindowPos();
			ImVec2 winsize = ImGui::GetWindowSize();

			if (PrevPos != winpos)
			{
				ShouldCheckAndClamp = true;
				PrevPos = winpos;
			}
			draw_list->AddLine(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y), ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y), ImColor(255, 130, 20, 255), 1.f);
			draw_list->AddLine(ImVec2(winpos.x, winpos.y + winsize.y * 0.5f), ImVec2(winpos.x + winsize.x, winpos.y + winsize.y * 0.5f), ImColor(255, 130, 20, 255), 1.f);

			Vector3 LocalPos = UnityEngine::GetPosition(GlobalUnityVariables::LocalPlayerInfo.TransformComponent);
			std::vector<void*> VisitedHarvestables;
			for (auto it = MyEntityList.begin(); it != MyEntityList.end(); it++)
			{
				EntityData_s& Current = *it;



				if (Current.HashedClassName == h("RemotePlayerCharacterView"))
				{
					auto Player = (RemotePlayerCharacterView_o*)Current.ComponentMono;

					if (CheatVars->FilterPlayers)
					{
						if (!UnityEngine::ValidateEntity(Current.MainComponent, Current.HashedClassName))
							continue;

						static auto getnamefn = Address_PlayerGetName;//Player->klass->vtable._99_get_Name.methodPtr;
						static auto ismountedfn = Address_PlayerIsMounted;//Player->klass->vtable._211_get_IsMounted.methodPtr;

						Vector3 PlayerPos = UnityEngine::GetPosition(Current.TransformComponent);

						uintptr_t unk1 = *(uintptr_t*)((uintptr_t)Player + 0x18);
						uintptr_t unk2 = *(uintptr_t*)((uintptr_t)unk1 + Offset_PlayerUnk2);
						float hp = *(float*)((uintptr_t)unk2 + Offset_PlayerHp);
						float maxhp = *(float*)((uintptr_t)unk2 + Offset_PlayerMaxHp);

						bool IsMounted = Utils::SecureCall<bool>((void*)ismountedfn, Player);
						wchar_t* PlayerName = (wchar_t*)&Utils::SecureCall<System_String_o*>((void*)getnamefn, Player)->fields.m_firstChar;

						auto Format = xorstr("[%i m]");
						MY_FORMAT_A(Format.crypt_get(), (int)PlayerPos.Distance(LocalPos));

						if (CheatVars->PlayersHealth && CheatVars->PlayersHealthRenderType != 1)
						{
							auto Format2 = xorstr("%s (%d/%d)");
							char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), CheatVars->PlayersName ? string_To_UTF8(PlayerName).c_str() : "", (int)hp, (int)maxhp);

							Esp::DrawEspRadarPlayer(PlayerPos, UniqueColor(IsMounted ? CheatVars->PlayersMountedColor : CheatVars->PlayersColor), Str, CheatVars->PlayersDistance ? Buffer : "", hp, maxhp);
						}
						else
							Esp::DrawEspRadarPlayer(PlayerPos, UniqueColor(IsMounted ? CheatVars->PlayersMountedColor : CheatVars->PlayersColor), CheatVars->PlayersName ? string_To_UTF8(PlayerName) : "", CheatVars->PlayersDistance ? Buffer : "", hp, maxhp);
					}
				}
				else if (Current.HashedClassName == h("HarvestableObjectView"))
				{
					//auto Harvestable = (Harvestable_o*)Current.ComponentMono;

					auto HarvestableObjectView = (HarvestableObjectView_o*)Current.ComponentMono;

					if (!UnityEngine::ValidateEntity(Current.MainComponent, Current.HashedClassName))
						continue;

					auto Harvestable = (Harvestable_o*)HarvestableObjectView->fields.d;

					uintptr_t unk1 = *(uintptr_t*)((uintptr_t)HarvestableObjectView + 0x18);
					uint32_t charges = *(uint32_t*)((uintptr_t)unk1 + 0x90);
					uint32_t Maxcharges = *(uint32_t*)((uintptr_t)unk1 + 0x98);


					Vector3 ItemPos = UnityEngine::GetPosition(Current.TransformComponent);

					//if (CheatVars->ResourceRestrictDistance)
					//	if (ItemPos.Distance(LocalPos) > 45.f)
					//		continue;

					if (CheatVars->FilterResources)
					{
						auto Format = xorstr("[%i m]");
						MY_FORMAT_A(Format.crypt_get(), (int)ItemPos.Distance(LocalPos));

						unsigned int ResourceHash = Current.TypeInfo.ResourceTypeHash;

						if (CheatVars->ResourcesDebug)
						{
							wchar_t* ResourceType = (wchar_t*)&Harvestable->fields.ResourceType->fields.m_firstChar;
							std::string Str = string_To_UTF8(ResourceType) + " " + std::to_string(Harvestable->fields.Charges) + " " + std::to_string(Harvestable->fields.Tier) + "." + std::to_string(Harvestable->fields.RareState);
							Esp::DrawEspRadar(ItemPos, UniqueColor(144, 0, 230), Str, CheatVars->ResourcesDistance ? Buffer : "");
							VisitedHarvestables.push_back(Harvestable);
						}
						else
						{
							if (Harvestable->fields.Charges > 0)
							{
								if (ResourceHash == h("WOOD") || ResourceHash == h("WOOD_GIANTTREE"))
								{
									if (CheatVars->FilterWood)
									{
										if (CheatVars->ResourcesCharges)
										{
											auto Format2 = xorstr("%d.%d (%d/%d)");
											char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState, charges, Maxcharges);
											Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->WoodColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											VisitedHarvestables.push_back(Harvestable);
										}
										else
										{
											auto Format2 = xorstr("%d.%d");
											char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState);
											Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->WoodColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											VisitedHarvestables.push_back(Harvestable);
										}
									}
								}
								else if (ResourceHash == h("ROCK"))
								{
									if (CheatVars->FilterRock)
									{
										if (CheatVars->ResourcesCharges)
										{
											auto Format2 = xorstr("%d.%d (%d/%d)");
											char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState, charges, Maxcharges);
											Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->RockColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											VisitedHarvestables.push_back(Harvestable);
										}
										else
										{
											auto Format2 = xorstr("%d.%d");
											char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState);
											Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->RockColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											VisitedHarvestables.push_back(Harvestable);
										}
									}
								}
								else if (ResourceHash == h("ORE"))
								{
									if (CheatVars->FilterOre)
									{
										if (CheatVars->ResourcesCharges)
										{
											auto Format2 = xorstr("%d.%d (%d/%d)");
											char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState, charges, Maxcharges);
											Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->OreColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											VisitedHarvestables.push_back(Harvestable);
										}
										else
										{
											auto Format2 = xorstr("%d.%d");
											char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState);
											Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->OreColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											VisitedHarvestables.push_back(Harvestable);
										}
									}
								}
								else if (ResourceHash == h("FIBER"))
								{
									if (CheatVars->FilterFiber)
									{
										if (CheatVars->ResourcesCharges)
										{
											auto Format2 = xorstr("%d.%d (%d/%d)");
											char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState, charges, Maxcharges);
											Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->FiberColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											VisitedHarvestables.push_back(Harvestable);
										}
										else
										{
											auto Format2 = xorstr("%d.%d");
											char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState);
											Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->FiberColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											VisitedHarvestables.push_back(Harvestable);
										}
									}
								}
								else if (ResourceHash == h("HIDE"))
								{
									if (CheatVars->FilterHide)
									{
										if (CheatVars->ResourcesCharges)
										{
											auto Format2 = xorstr("%d.%d (%d/%d)");
											char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState, charges, Maxcharges);
											Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->HideColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											VisitedHarvestables.push_back(Harvestable);
										}
										else
										{
											auto Format2 = xorstr("%d.%d");
											char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState);
											Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->HideColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
											VisitedHarvestables.push_back(Harvestable);
										}
									}
								}
							}
						}
					}
				}
				else if (Current.HashedClassName == h("MobView"))
				{
					auto Mob = (MobView_o*)Current.ComponentMono;
					if (CheatVars->FilterMobs)
					{
						if (!UnityEngine::ValidateEntity(Current.MainComponent, Current.HashedClassName))
							continue;

						uintptr_t mobptr = *reinterpret_cast<uintptr_t*>((uintptr_t)Mob + 0x18);
						if (!Utils::IsValidPtr(mobptr))
							continue;

						uintptr_t mob2 = *reinterpret_cast<uintptr_t*>(mobptr + Offset_Mob2);
						if (!Utils::IsValidPtr(mob2))
							continue;

						uintptr_t mob3 = *reinterpret_cast<uintptr_t*>(mob2 + Offset_Mob3);
						if (!Utils::IsValidPtr(mob3))
							continue;

						Vector3 MobPos = UnityEngine::GetPosition(Current.TransformComponent);

						//wchar_t* name = reinterpret_cast<wchar_t*>(mob3 + Offset_MobName);

						int MobRare = *reinterpret_cast<int*>(mobptr + Offset_MabRare);
						int MobTier = *reinterpret_cast<int*>(mob2 + Offset_MobTier);


						uintptr_t pMob = Utils::SecureCall<uintptr_t>((void*)Address_GetMob, Mob);
						if (!Utils::IsValidPtr(pMob))
							continue;

						bd5_o* pMobInfo = Utils::SecureCall<bd5_o*>((void*)Address_GetMobInfo, pMob);
						if (!Utils::IsValidPtr(pMobInfo))
							continue;

						//MobTypeCategory MobType = (MobTypeCategory)pMobInfo->fields.d7;

						//std::string obj_name = gameobject->Name;

						auto Format = xorstr("[%i m]");
						MY_FORMAT_A(Format.crypt_get(), (int)MobPos.Distance(LocalPos));

						//std::string Str = /*string_To_UTF8(ResourceType) + " " +*/ std::to_string(MobTier) + "." + std::to_string(MobRare);
						if (CheatVars->MobsDebug)
						{
							//std::string Str = string_To_UTF8(ResourceType) + " " + std::to_string(MobType) + " " + std::to_string(Harvestable->fields.Tier) + "." + std::to_string(Harvestable->fields.RareState);


							Esp::DrawEspRadar(MobPos, UniqueColor(144, 0, 230), ((GameObject*)Current.GameObject)->Name, CheatVars->MobsDistance ? Buffer : "");
						}
						else
						{
							if (Current.TypeInfo.MobType == MyMobType::Boss)
							{
								if (CheatVars->FilterMobBoss)
								{
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobBossColor), xorstr_("Boss"), CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::MiniBoss)
							{
								if (CheatVars->FilterMobMiniBoss)
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobMiniBossColor), xorstr_("Mini Boss"), CheatVars->MobsDistance ? Buffer : "");
							}
							else if (Current.TypeInfo.MobType == MyMobType::Hide)
							{
								if (CheatVars->FilterMobHide)
								{
									auto Format2 = xorstr("%d.%d");
									char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), MobTier, MobRare);
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobHideColor), Str, CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::Ore)
							{
								if (CheatVars->FilterMobOre)
								{
									auto Format2 = xorstr("%d.%d");
									char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), MobTier, MobRare);
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobOreColor), Str, CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::Fiber)
							{
								if (CheatVars->FilterMobFiber)
								{
									auto Format2 = xorstr("%d.%d");
									char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), MobTier, MobRare);
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobFiberColor), Str, CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::Wood)
							{
								if (CheatVars->FilterMobWood)
								{
									auto Format2 = xorstr("%d.%d");
									char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), MobTier, MobRare);
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobWoodColor), Str, CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::Rock)
							{
								if (CheatVars->FilterMobRock)
								{
									auto Format2 = xorstr("%d.%d");
									char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), MobTier, MobRare);
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobRockColor), Str, CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::WispDefault)
							{
								if (CheatVars->FilterMobWispDefault)
								{
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobWispDefaultColor), "Wisp", CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::WispEpic)
							{
								if (CheatVars->FilterMobWispEpic)
								{
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobWispEpicColor), "Wisp Epic", CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::WispUncommon)
							{
								if (CheatVars->FilterMobWispUncommon)
								{
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobWispUncommonColor), "Wisp Uncommon", CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::WispRare)
							{
								if (CheatVars->FilterMobWispRare)
								{
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobWispRareColor), "Wisp Rare", CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::WispLegendary)
							{
								if (CheatVars->FilterMobWispLegendary)
								{
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobWispLegendaryColor), "Wisp Legendary", CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::MistsBoss)
							{
								if (CheatVars->FilterMobMistsBoss)
								{
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobMistsBossColor), "Mists Boss", CheatVars->MobsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::ChestHidden)
							{
								if (CheatVars->FilterChestHidden)
								{
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->HiddenChestColor), "Hidden Chest", CheatVars->ChestsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::AvalonDrone)
							{
								if (CheatVars->FilterMobAvalonTreasure)
								{
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobAvalonTreasureMobColor), "Avalon Drone", CheatVars->ChestsDistance ? Buffer : "");
								}
							}
							else if (Current.TypeInfo.MobType == MyMobType::Hostile)
							{
								if (CheatVars->FilterMobHostile)
								{
									auto Format2 = xorstr("NPC %d.%d");
									char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), MobTier, MobRare);
									Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobHostileColor), Str, CheatVars->ChestsDistance ? Buffer : "");
								}
							}
						}
						/*else if (obj_name.find("HIDE") != std::string::npos ||
							obj_name.find("ORE") != std::string::npos ||
							obj_name.find("FIBER") != std::string::npos ||
							obj_name.find("WOOD") != std::string::npos ||
							obj_name.find("ROCK") != std::string::npos)
						{




						}*/
						//.std::wstring subname = std::wstring(name).substr(1, 1);


						//
						//std::cout << "MobRare: " << MobRare << " MobType: " << test1->fields.d7 << " ";


						//std::wcout << "MobName: " << name << std::endl;

						//auto current_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);
						//Mobpos = get_position(current_compoment);
						////std::wcout <<"MobName: " << (wchar_t*)&(Mob->fields.v->fields.m_firstChar) << " ";
						//std::cout << "Cord: " << Mobpos << " Dist: " << Mobpos.Distance(LocalPlayerPos) << std::endl;
					}
				}
				else if (Current.HashedClassName == h("RandomDungeonExitObjectView"))
				{
					auto Dungeon = (Assets_Scripts_SimulationObjectViews_SimulationObjects_WorldObjects_StaticObjects_RandomDungeonExitObjectView_o*)Current.ComponentMono;

					if (!UnityEngine::ValidateEntity(Current.MainComponent, Current.HashedClassName))
						continue;

					Vector3 DungeonPos = UnityEngine::GetPosition(Current.TransformComponent);

					auto Format = xorstr("[%i m]");
					MY_FORMAT_A(Format.crypt_get(), (int)DungeonPos.Distance(LocalPos));
					if (Current.TypeInfo.MobType == MyMobType::DungeonGroup)
					{
						if (CheatVars->FilterGroupDungeon)					
							Esp::DrawEspRadar(DungeonPos, UniqueColor(CheatVars->GroupDungeonColor), xorstr_("Group Dungeon"), CheatVars->DungeonsDistance ? Buffer : "");			
					}
					else if (Current.TypeInfo.MobType == MyMobType::DungeonSolo)
					{
						if (CheatVars->FilterSoloDungeon)
							Esp::DrawEspRadar(DungeonPos, UniqueColor(CheatVars->SoloDungeonColor), xorstr_("Solo Dungeon"), CheatVars->DungeonsDistance ? Buffer : "");					
					}
					else if (Current.TypeInfo.MobType == MyMobType::DungeonCorrupt)
					{
						if (CheatVars->FilterCorruptDungeon)
							Esp::DrawEspRadar(DungeonPos, UniqueColor(CheatVars->CorruptDungeonColor), xorstr_("Corrupt Dungeon"), CheatVars->DungeonsDistance ? Buffer : "");
					}
					else if (Current.TypeInfo.MobType == MyMobType::DungeonHellgate)
					{
						if (CheatVars->FilterHellgateDungeon)
							Esp::DrawEspRadar(DungeonPos, UniqueColor(CheatVars->HellgateDungeonColor), xorstr_("Hellgate Dungeon"), CheatVars->DungeonsDistance ? Buffer : "");
					}
					else if (Current.TypeInfo.MobType == MyMobType::DungeonMist)
					{
						if (CheatVars->FilterMistsDungeon)
							Esp::DrawEspRadar(DungeonPos, UniqueColor(CheatVars->FilterMistsDungeon), xorstr_("Mist Portal"), CheatVars->DungeonsDistance ? Buffer : "");
					}
				}
				else if (Current.HashedClassName == h("LootObjectView"))
				{
					if (!UnityEngine::ValidateEntity(Current.MainComponent, Current.HashedClassName))
						continue;

					Vector3 LootBagPos = UnityEngine::GetPosition(Current.TransformComponent);

					auto Format = xorstr("[%i m]");
					MY_FORMAT_A(Format.crypt_get(), (int)LootBagPos.Distance(LocalPos));

					if (Current.TypeInfo.MobType == MyMobType::ChestLootBag)
					{
						if (CheatVars->FilterLootBag)
							Esp::DrawEspRadar(LootBagPos, UniqueColor(CheatVars->LootBagColor), xorstr_("Mob Loot Bag"), CheatVars->ChestsDistance ? Buffer : "");
					}
				}
				else if (Current.HashedClassName == h("Vfx"))
				{
					if (!UnityEngine::ValidateEntity(Current.MainComponent, Current.HashedClassName))
						continue;

					Vector3 LootBagPos = UnityEngine::GetPosition(Current.TransformComponent);

					auto Format = xorstr("[%i m]");
					MY_FORMAT_A(Format.crypt_get(), (int)LootBagPos.Distance(LocalPos));

					if (Current.TypeInfo.MobType == MyMobType::ChestLootBag)
					{
						if (CheatVars->FilterLootBag)
							Esp::DrawEspRadar(LootBagPos, UniqueColor(CheatVars->LootBagColor), xorstr_("Player Loot Bag"), CheatVars->ChestsDistance ? Buffer : "");
					}
				}
			}
			for (auto it = MyFarEntityList.begin(); it != MyFarEntityList.end(); it++)
			{
				EntityData_s& Current = *it;

				if (!CheatVars->ResourceDontShowSpawnPoints && Current.HashedClassName == h("Harvestable"))
				{
					auto Harvestable = (Harvestable_o*)Current.ComponentMono;

					if (!UnityEngine::ValidateEntity(Current.MainComponent, Current.HashedClassName))
						continue;

					if (std::find(VisitedHarvestables.begin(), VisitedHarvestables.end(), Harvestable) != VisitedHarvestables.end())
						continue;
					//if(VisitedHarvestables.find(Harvestable))
					Vector3 ItemPos = UnityEngine::GetPosition(Current.TransformComponent);

					if (CheatVars->FilterResources)
					{
						auto Format = xorstr("[%i m]");
						MY_FORMAT_A(Format.crypt_get(), (int)ItemPos.Distance(LocalPos));

						unsigned int ResourceHash = Current.TypeInfo.ResourceTypeHash;

						if (CheatVars->ResourcesDebug)
						{
							wchar_t* ResourceType = (wchar_t*)&Harvestable->fields.ResourceType->fields.m_firstChar;
							std::string Str = string_To_UTF8(ResourceType) + " " + std::to_string(Harvestable->fields.Charges) + " " + std::to_string(Harvestable->fields.Tier) + "." + std::to_string(Harvestable->fields.RareState);
							Esp::DrawEspRadar(ItemPos, UniqueColor(144, 0, 230), Str, CheatVars->ResourcesDistance ? Buffer : "");
						}
						else
						{
							if (Harvestable->fields.Charges > 0)
							{
								if (ResourceHash == h("WOOD") || ResourceHash == h("WOOD_GIANTTREE"))
								{
									if (CheatVars->FilterWood)
									{
										auto Format2 = xorstr("%d.%d");
										char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState);
										Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->WoodColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
									}
								}
								else if (ResourceHash == h("ROCK"))
								{
									if (CheatVars->FilterRock)
									{
										auto Format2 = xorstr("%d.%d");
										char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState);
										Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->RockColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
									}
								}
								else if (ResourceHash == h("ORE"))
								{
									if (CheatVars->FilterOre)
									{
										auto Format2 = xorstr("%d.%d");
										char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState);
										Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->OreColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
									}
								}
								else if (ResourceHash == h("FIBER"))
								{
									if (CheatVars->FilterFiber)
									{
										auto Format2 = xorstr("%d.%d");
										char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState);
										Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->FiberColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
									}
								}
								else if (ResourceHash == h("HIDE"))
								{
									if (CheatVars->FilterHide)
									{
										auto Format2 = xorstr("%d.%d");
										char Str[64] = { 0 }; sprintf(Str, Format2.crypt_get(), Harvestable->fields.Tier, Harvestable->fields.RareState);
										Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->HideColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
									}
								}
							}
						}
					}
				}
			}

			//for (auto i = gameobjectmanager->CurrentObjects; std::uintptr_t(i) != std::uintptr_t(&gameobjectmanager->LastCurrentObject); i = i->nextObjectLink) {
			//
			// 					if (!Utils::IsValidPtr(i))
			//						continue;
			//	auto gameobject = i->object;

			//	auto component_size = *reinterpret_cast<int32_t*>(std::uintptr_t(gameobject) + Offset_ComponentsSize);
			//	auto components_ptr = *reinterpret_cast<uintptr_t*>(std::uintptr_t(gameobject) + Offset_ComponentsPtr);

			//	for (auto compoment_index = 0; compoment_index < component_size; compoment_index++) {
			//		auto current_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (compoment_index * 0x10) + 0x8);
			//		if (!current_compoment)
			//			continue;

			//		auto compoment_mono = *reinterpret_cast<Il2CppObject**>(current_compoment + Offset_MonoPtr);
			//		if (!compoment_mono || reinterpret_cast<Il2CppClass*>(compoment_mono->klass) != compoment_mono->klass->_1.klass)
			//			continue;

			//		//auto szName = compoment_mono->klass->_1.name;
			//		unsigned int HashedClassName = crypto::hash_string(compoment_mono->klass->_1.name);

			//		if (HashedClassName == h("RemotePlayerCharacterView"))
			//		{
			//			auto Player = (RemotePlayerCharacterView_o*)compoment_mono;
			//			static auto getnamefnptr = Player->klass->vtable._99_get_Name.methodPtr;

			//			auto transform_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);
			//			Vector3 PlayerPos = UnityEngine::GetPosition(transform_compoment);

			//			if (CheatVars->FilterPlayers)
			//			{
			//				wchar_t* PlayerName = (wchar_t*)&Utils::SecureCall<System_String_o*>(getnamefnptr, Player)->fields.m_firstChar;
			//				auto Format = xorstr("[%i m]");
			//				MY_FORMAT_A(Format.crypt_get(), (int)PlayerPos.Distance(LocalPos));
			//				Esp::DrawEspRadar(PlayerPos, UniqueColor(255, 0, 0), CheatVars->PlayersName ? string_To_UTF8(PlayerName) : "", CheatVars->PlayersDistance ? Buffer : "");
			//			}
			//		}
			//		else if (HashedClassName == h("Harvestable"))
			//		{
			//			auto Harvestable = (Harvestable_o*)compoment_mono;

			//			auto transform_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);
			//			Vector3 ItemPos = UnityEngine::GetPosition(transform_compoment);

			//			if (CheatVars->FilterResources)
			//			{
			//				wchar_t* ResourceType = (wchar_t*)&Harvestable->fields.ResourceType->fields.m_firstChar;
			//				unsigned int ResourceHash = crypto::hash_string(ResourceType);

			//				auto Format = xorstr("[%i m]");
			//				MY_FORMAT_A(Format.crypt_get(), (int)ItemPos.Distance(LocalPos));

			//				if (CheatVars->ResourcesDebug)
			//				{
			//					std::string Str = string_To_UTF8(ResourceType) + " " + std::to_string(Harvestable->fields.Charges) + " " + std::to_string(Harvestable->fields.Tier) + "." + std::to_string(Harvestable->fields.RareState);
			//					Esp::DrawEspRadar(ItemPos, UniqueColor(144, 0, 230), Str, CheatVars->ResourcesDistance ? Buffer : "");
			//				}
			//				else
			//				{
			//					if (Harvestable->fields.Charges > 0)
			//					{
			//						std::string Str = /*string_To_UTF8(ResourceType) + " " +*/ std::to_string(Harvestable->fields.Tier) + "." + std::to_string(Harvestable->fields.RareState);

			//						if (ResourceHash == h("WOOD") || ResourceHash == h("WOOD_GIANTTREE"))
			//						{
			//							if (CheatVars->FilterWood)
			//							{
			//								//if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityWood))
			//									Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->WoodColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
			//							}
			//						}
			//						else if (ResourceHash == h("ROCK"))
			//						{
			//							if (CheatVars->FilterRock)
			//							{
			//								//if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityRock))
			//									Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->RockColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
			//							}
			//						}
			//						else if (ResourceHash == h("ORE"))
			//						{
			//							if (CheatVars->FilterOre)
			//							{
			//								//if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityOre))
			//									Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->OreColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
			//							}
			//						}
			//						else if (ResourceHash == h("FIBER"))
			//						{
			//							if (CheatVars->FilterFiber)
			//							{
			//								//if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityFiber))
			//									Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->FiberColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
			//							}
			//						}
			//						else if (ResourceHash == h("HIDE"))
			//						{
			//							if (CheatVars->FilterHide)
			//							{
			//								//if (Condition::TierCheck(Harvestable->fields.Tier, Harvestable->fields.RareState, CheatVars->RarityHide))
			//									Esp::DrawEspRadar(ItemPos, UniqueColor(CheatVars->HideColor), Str, CheatVars->ResourcesDistance ? Buffer : "");
			//							}
			//						}
			//					}
			//				}
			//			}
			//		}
			//		else if (HashedClassName == h("MobView"))
			//		{
			//			auto Mob = (MobView_o*)compoment_mono;
			//			if (CheatVars->FilterMobs)
			//			{
			//				uintptr_t mobptr = *reinterpret_cast<uintptr_t*>((uintptr_t)Mob + 0x18);
			//				if (!Utils::IsValidPtr(mobptr))
			//					continue;

			//				uintptr_t mob2 = *reinterpret_cast<uintptr_t*>(mobptr + 0xD8);
			//				if (!Utils::IsValidPtr(mob2))
			//					continue;

			//				uintptr_t mob3 = *reinterpret_cast<uintptr_t*>(mob2 + 0x10);
			//				if (!Utils::IsValidPtr(mob3))
			//					continue;

			//				auto transform_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);
			//				Vector3 MobPos = UnityEngine::GetPosition(transform_compoment);

			//				wchar_t* name = reinterpret_cast<wchar_t*>(mob3 + 0x14);

			//				int MobRare = *reinterpret_cast<int*>(mobptr + 0x1D0);
			//				int MobTier = *reinterpret_cast<int*>(mob2 + 0xD8);


			//				uintptr_t pMob = Utils::SecureCall<uintptr_t>((void*)Address_GetMob, Mob);
			//				if (!Utils::IsValidPtr(pMob))
			//					continue;

			//				bd5_o* pMobInfo = Utils::SecureCall<bd5_o*>((void*)Address_GetMobInfo, pMob);
			//				if (!Utils::IsValidPtr(pMobInfo))
			//					continue;

			//				MobTypeCategory MobType = (MobTypeCategory)pMobInfo->fields.d7;

			//				std::string obj_name = gameobject->Name;

			//				auto Format = xorstr("[%i m]");
			//				MY_FORMAT_A(Format.crypt_get(), (int)MobPos.Distance(LocalPos));

			//				std::string Str = /*string_To_UTF8(ResourceType) + " " +*/ std::to_string(MobTier) + "." + std::to_string(MobRare);
			//				if (CheatVars->ResourcesDebug)
			//				{
			//					//std::string Str = string_To_UTF8(ResourceType) + " " + std::to_string(MobType) + " " + std::to_string(Harvestable->fields.Tier) + "." + std::to_string(Harvestable->fields.RareState);
			//					Esp::DrawEspRadar(MobPos, UniqueColor(144, 0, 230), obj_name, CheatVars->MobsDistance ? Buffer : "");
			//				}
			//				else
			//				{
			//					if (MobType == Boss)
			//					{
			//						if (CheatVars->FilterMobBoss)
			//							Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobBossColor), xorstr_("Boss"), CheatVars->MobsDistance ? Buffer : "");
			//					}
			//					else if (MobType == MiniBoss)
			//					{
			//						if (CheatVars->FilterMobMiniBoss)
			//							Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobMiniBossColor), xorstr_("Mini Boss"), CheatVars->MobsDistance ? Buffer : "");
			//					}
			//					else if (obj_name.find("HIDE") != std::string::npos)
			//					{
			//						if (CheatVars->FilterMobHide)
			//							if (Condition::TierCheck(MobTier, MobRare, CheatVars->RarityMobHide))
			//								Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobHideColor), Str, CheatVars->MobsDistance ? Buffer : "");
			//					}
			//					else if (obj_name.find("ORE") != std::string::npos)
			//					{
			//						if (CheatVars->FilterMobOre)
			//							if (Condition::TierCheck(MobTier, MobRare, CheatVars->RarityMobOre))
			//								Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobOreColor), Str, CheatVars->MobsDistance ? Buffer : "");
			//					}
			//					else if (obj_name.find("FIBER") != std::string::npos)
			//					{
			//						if (CheatVars->FilterMobFiber)
			//							if (Condition::TierCheck(MobTier, MobRare, CheatVars->RarityMobFiber))
			//								Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobFiberColor), Str, CheatVars->MobsDistance ? Buffer : "");
			//					}
			//					else if (obj_name.find("_WOOD_") != std::string::npos)
			//					{
			//						if (CheatVars->FilterMobWood)
			//							if (Condition::TierCheck(MobTier, MobRare, CheatVars->RarityMobWood))
			//								Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobWoodColor), Str, CheatVars->MobsDistance ? Buffer : "");
			//					}
			//					else if (obj_name.find("ROCK") != std::string::npos)
			//					{
			//						if (CheatVars->FilterMobRock)
			//							if (Condition::TierCheck(MobTier, MobRare, CheatVars->RarityMobRock))
			//								Esp::DrawEspRadar(MobPos, UniqueColor(CheatVars->MobRockColor), Str, CheatVars->MobsDistance ? Buffer : "");
			//					}
			//				}
			//				/*else if (obj_name.find("HIDE") != std::string::npos ||
			//					obj_name.find("ORE") != std::string::npos ||
			//					obj_name.find("FIBER") != std::string::npos ||
			//					obj_name.find("WOOD") != std::string::npos ||
			//					obj_name.find("ROCK") != std::string::npos)
			//				{




			//				}*/
			//				//.std::wstring subname = std::wstring(name).substr(1, 1);


			//				//
			//				//std::cout << "MobRare: " << MobRare << " MobType: " << test1->fields.d7 << " ";


			//				//std::wcout << "MobName: " << name << std::endl;

			//				//auto current_compoment = *reinterpret_cast<uintptr_t*>(components_ptr + (0 * 0x10) + 0x8);
			//				//Mobpos = get_position(current_compoment);
			//				////std::wcout <<"MobName: " << (wchar_t*)&(Mob->fields.v->fields.m_firstChar) << " ";
			//				//std::cout << "Cord: " << Mobpos << " Dist: " << Mobpos.Distance(LocalPlayerPos) << std::endl;
			//			}
			//		}
			//	}
			//}
			ImGui::End();
		}
	}
public:
	static void ReadThread()
	{
		const auto CheatVars = GET_SETVAR_PTR(m_CheatVars, C_CheatVars);
		while (!global::bPanickKey)
		{
			//MyEntityList.clear();

			//uintptr_t MainCamera = UnityEngine::GetMainCamera();
			//GlobalUnityVariables::LocalPlayerInfo = UnityEngine::GetLocalInfo();

			CExceptionHandler ExceptionHandler;
			CLogger Logger(xorstr_("READ"));

			LogCallBegining(__FUNCTION__, __LINE__); LogCallEnding(__FUNCTION__, __LINE__);
			std::vector<EntityData_s> TmpEntityList;
			std::vector<EntityData_s> TmpFarEntityList;

			LogCallBegining(__FUNCTION__, __LINE__); EntityHandler(CheatVars, TmpEntityList, TmpFarEntityList); LogCallEnding(__FUNCTION__, __LINE__);

			MyEntityList = TmpEntityList;
			MyFarEntityList = TmpFarEntityList;
			Sleep(1);
			LogCallBegining(__FUNCTION__, __LINE__); LogCallEnding(__FUNCTION__, __LINE__);
		}
	}
	static void RadarWindowFrame()
	{
		auto CheatVars = GET_SETVAR_PTR(m_CheatVars, C_CheatVars);

		GlobalUnityVariables::MainCamera = UnityEngine::GetMainCamera();

		if (!Utils::IsValidPtr(GlobalUnityVariables::MainCamera))
			return;

		if (!Utils::IsValidPtr(GlobalUnityVariables::LocalPlayerInfo.TransformComponent))
			return;

		if (!UnityEngine::ValidateLocalPlayer(GlobalUnityVariables::LocalPlayerInfo.MainComponent))
			return;

		if (!UnityEngine::ValidateCamera(GlobalUnityVariables::MainCamera))
			return;

		if (CheatVars->Radar)
		{
			auto gameobjectmanager = UnityEngine::GetGameObjectManager();

			ImGui::SetNextWindowSize(ImVec2(256, 256), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX));
			//ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = { 0.f, 0.f, 0.f, CheatVars.Transperancy / 255.f };// IM_COL32(0, 0, 0, CheatVars.Transperancy);
			ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 0, 0, CheatVars->Transperancy));

			ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;

			if (!Menu::bShowMenu)
				WindowFlags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

			__try
			{
				LogCallBegining(__FUNCTION__, __LINE__); RadarFrame(CheatVars, WindowFlags); LogCallEnding(__FUNCTION__, __LINE__); 
			}
			__except(1)
			{

			}

			ImGui::PopStyleColor();
		}
	}
	static void Frame()
	{
		LogCallBegining(__FUNCTION__, __LINE__); LogCallEnding(__FUNCTION__, __LINE__);

		//ProcessPlayerArray();

		static bool ResetOnce = false;
		if (Menu::bShowMenu)
		{

			ResetOnce = true;
		}
		else if (ResetOnce)
		{

			ResetOnce = false;
		}

		GlobalUnityVariables::MainCamera = UnityEngine::GetMainCamera();

		if (!Utils::IsValidPtr(GlobalUnityVariables::MainCamera))
			return;

		if (!Utils::IsValidPtr(GlobalUnityVariables::LocalPlayerInfo.TransformComponent))
			return;

		if (!UnityEngine::ValidateLocalPlayer(GlobalUnityVariables::LocalPlayerInfo.MainComponent))
			return;

		if (!UnityEngine::ValidateCamera(GlobalUnityVariables::MainCamera))
			return;

		auto CheatVars = GET_SETVAR(m_CheatVars, C_CheatVars);

		//Vector3 LocalPos = UnityEngine::GetPosition(GlobalUnityVariables::LocalPlayerInfo.TransformComponent);

		//ImGui::SetWindowFontScale(2.f);

		//std::string Str = std::to_string(LocalPos.x) + " " + std::to_string(LocalPos.y) + " " + std::to_string(LocalPos.z);
		//Drawing::DrawShadowedString({ 45, 45 }, Str.c_str(), UniqueColor(255, 255, 255), false);


		//const auto matrix = *reinterpret_cast<Matrix4x4*>(GlobalUnityVariables::MainCamera + 0xDC);


		//for (int i = 0; i < 4; i++)
		//{
		//	Vector4 Column = { matrix[0][i],
		//			 matrix[1][i],
		//			 matrix[2][i],
		//			 matrix[3][i] 
		//	};
		//	Str = std::to_string(Column.x) + " " + std::to_string(Column.y) + " " + std::to_string(Column.z) + " " + std::to_string(Column.w);
		//	Drawing::DrawShadowedString({ 45.f, 90.f + (i * 30.f)}, Str.c_str(), UniqueColor(255, 255, 255), false);
		//}
		////auto translation = matrix.GetColumn(3);

		////Str = std::to_string(translation.x) + " " + std::to_string(translation.y) + " " + std::to_string(translation.z);
		////Drawing::DrawShadowedString({ 45, 90 }, Str.c_str(), UniqueColor(255, 255, 255), false);

		////Str = std::to_string(translation.x) + " " + std::to_string(translation.y) + " " + std::to_string(translation.z);
		////Drawing::DrawShadowedString({ 45, 120 }, Str.c_str(), UniqueColor(255, 255, 255), false);

		////Str = std::to_string(translation.x) + " " + std::to_string(translation.y) + " " + std::to_string(translation.z);
		////Drawing::DrawShadowedString({ 45, 150 }, Str.c_str(), UniqueColor(255, 255, 255), false);

		////Str = std::to_string(translation.x) + " " + std::to_string(translation.y) + " " + std::to_string(translation.z);
		////Drawing::DrawShadowedString({ 45, 180 }, Str.c_str(), UniqueColor(255, 255, 255), false);

		//ImGui::SetWindowFontScale(1.f);

		LogCallBegining(__FUNCTION__, __LINE__); LogCallEnding(__FUNCTION__, __LINE__);
	}
};