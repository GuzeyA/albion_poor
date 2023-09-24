#pragma once
#include "includes.h"
#include "sdk.h"

class Esp
{
private:
	struct EspBox
	{
		float x = 0;
		float y = 0;
		float w = 0;
		float h = 0;
		bool IsValid = false;
		EspBox()
		{
			x = y = w = h = 0.f;
			IsValid = false;
		}
		EspBox(float X, float Y, float W, float H, bool Valid)
		{
			x = X;
			y = Y;
			w = W;
			h = H;
			IsValid = Valid;
		}
	};
	static void DrawCornerBox(int x, int y, int w, int h, int cx, int cy, const UniqueColor& clrColor)
	{
		Drawing::DrawLine(UniqueVector2(x, y), UniqueVector2(x + (w / cx), y), clrColor);
		Drawing::DrawLine(UniqueVector2(x, y), UniqueVector2(x, y + (h / cy)), clrColor);

		Drawing::DrawLine(UniqueVector2(x + w, y), UniqueVector2(x + w - (w / cx), y), clrColor);
		Drawing::DrawLine(UniqueVector2(x + w, y), UniqueVector2(x + w, y + (h / cy)), clrColor);

		Drawing::DrawLine(UniqueVector2(x, y + h), UniqueVector2(x + (w / cx), y + h), clrColor);
		Drawing::DrawLine(UniqueVector2(x, y + h), UniqueVector2(x, y + h - (h / cy)), clrColor);

		Drawing::DrawLine(UniqueVector2(x + w, y + h), UniqueVector2(x + w - (w / cx), y + h), clrColor);
		Drawing::DrawLine(UniqueVector2(x + w, y + h), UniqueVector2(x + w, y + h - (h / cy)), clrColor);
	}

	void VectorTransform(const Vector3& in1, float in2[4][4], Vector3& out)
	{
		out.x = in1.Dot(Vector3(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
		out.y = in1.Dot(Vector3(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
		out.z = in1.Dot(Vector3(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
	}
	public:
	static void AngleVectors(const Vector3& angles, Vector3& forward)
	{
		float sp, sy, cp, cy;

		sy = sin(DEG2RAD(angles[1]));
		cy = cos(DEG2RAD(angles[1]));
			 
		sp = sin(DEG2RAD(angles[0]));
		cp = cos(DEG2RAD(angles[0]));

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}
	private:
		static Vector2 RotatePoint(Vector2 Pivot, float angle, Vector2 p)
		{
			float s = sin(angle);
			float c = cos(angle);

			// translate point back to origin:
			p.x -= Pivot.x;
			p.y -= Pivot.y;

			// rotate point
			float xnew = p.x * c - p.y * s;
			float ynew = p.x * s + p.y * c;

			// translate point back:
			p.x = xnew + Pivot.x;
			p.y = ynew + Pivot.y;

			return p;
		}
	static void VectorAngles(const Vector3& forward, Vector3& angles)
	{
		float tmp, yaw, pitch;

		if (forward.y == 0 && forward.x == 0)
		{
			yaw = 0;

			if (forward.z > 0)
				pitch = 270;
			else
				pitch = 90;
		}
		else
		{
			yaw = RAD2DEG(atan2(forward.y, forward.x));

			if (yaw < 0)
				yaw += 360;

			tmp = forward.Length2D();
			pitch = RAD2DEG(atan2(-forward.z, tmp));

			if (pitch < 0)
				pitch += 360;
		}
		angles.x = pitch;
		angles.y = yaw;
		angles.z = 0;
	}
	static void RotateTriangle(Vector2 points[3], float rotation)
	{
		auto points_center = (points[0] + points[1] + points[2]) / 3;

		for (auto i = 0; i < 3; i++)
		{
			auto& point = points[i];
			point -= points_center;

			const auto temp_x = point.x;
			const auto temp_y = point.y;

			const auto theta = DEG2RAD(rotation);
			const auto c = cos(theta);
			const auto s = sin(theta);

			point.x = temp_x * c - temp_y * s;
			point.y = temp_x * s + temp_y * c;

			point += points_center;
		}
	}
	static void DrawHealthBar(float EspX, float EspY, float EspH, float Health, float MaxHealth)
	{
		float health = (float)Health * 100 / (float)MaxHealth;

		if (health > 100)
			health = 100;

		int r = 255 - health * 2.55;
		int g = health * 2.55;

		float healthBar = (EspH) / 100.f * health;
		float healthBarDelta = (EspH) - healthBar;

		constexpr float widthhealth = 3.f;
		constexpr float offsetx = 3.f;
		UniqueColor IncapacitedColor = UniqueColor(255, 220, 51, 255);

		Drawing::DrawOutlinedRect({ EspX - offsetx - 1 - widthhealth - 1, EspY - 1 }, { widthhealth + 2, EspH + 2 }, UniqueColor(0, 0, 0, 255));
		Drawing::DrawFilledRect({ EspX - offsetx - 1 - widthhealth, EspY + healthBarDelta }, { widthhealth, healthBar }, UniqueColor(r, g, 0, 255));
	}
	static void DrawActorOnRadar(const Vector3& EnemyOrigin, const UniqueColor& col, const std::string& UpperText, const std::string& LowerText)
	{
		ImVec2 winpos = ImGui::GetWindowPos();
		ImVec2 winsize = ImGui::GetWindowSize();

		auto CheatVars = GET_SETVAR(m_CheatVars, C_CheatVars);

		//Vector2 screenpos;
		Vector3 LocalOrigin = UnityEngine::GetPosition(GlobalUnityVariables::LocalPlayerInfo.TransformComponent);
		//const auto matrix = *reinterpret_cast<Matrix4x4*>(GlobalUnityVariables::MainCamera + 0xDC);
		//if (matrix[3][2] > 0) {
		//	if (!UnityEngine::WorldToScreen(EnemyOrigin, screenpos, CheatVars.Zoom * -1))
		//		return;
		//}
		//else
		//{
		//	if (!UnityEngine::WorldToScreen(EnemyOrigin, screenpos, CheatVars.Zoom))
		//		return;
		//}

		//screenpos = screenpos / *(Vector2*)&GlobalVars::g_vecScreenSize * *(Vector2*)&winsize;

		//float X = winpos.x + screenpos.x;
		//float Y = winpos.y + screenpos.y;

		const Vector3 DeltaFromLocal = EnemyOrigin - LocalOrigin;

		if (DeltaFromLocal.x > CheatVars.Zoom || DeltaFromLocal.x < -CheatVars.Zoom)
			return;

		if (DeltaFromLocal.z > CheatVars.Zoom || DeltaFromLocal.z < -CheatVars.Zoom)
			return;

		ImGui::SetWindowFontScale(CheatVars.TextScale);

		float PointSize = 5 * CheatVars.PointScale;

		float RelX = DeltaFromLocal.z / CheatVars.Zoom * (winsize.x / 2);
		float RelY = DeltaFromLocal.x / CheatVars.Zoom * (winsize.y / 2);

		float X = winpos.x + (winsize.x / 2) + RelX;
		float Y = winpos.y + (winsize.y / 2) + RelY;

		Vector2 Final;
		Final = RotatePoint({ winpos.x + (winsize.x / 2) ,  winpos.y + (winsize.y / 2) }, DEG2RAD(-60.f), { X , Y });

		Vector2 Final2;
		Final2 = RotatePoint({ winpos.x + (winsize.x / 2) ,  winpos.y + (winsize.y / 2) }, DEG2RAD(-30.f), { X , Y });
		

		X = Final.x;
		Y = Final2.y;
		if (!UpperText.empty())
			Drawing::DrawString({ X, Y - (PointSize / 2) - 2 }, UpperText.c_str(), UniqueColor(255, 255, 255), UniqueAlignment::Alignment_Bottom | UniqueAlignment::Alignment_Center_x);

		//Drawing::DrawFilledRect({ X - PointSize / 2, Y - PointSize / 2 }, { PointSize + 1, PointSize + 1 }, col);

		//Drawing::DrawOutlinedRect({ X - 1 - PointSize / 2, Y - 1 - PointSize / 2 }, { PointSize + 2, PointSize + 2 }, UniqueColor(0, 0, 0, 255));

		Drawing::DrawFilledCircle({ X, Y }, PointSize, col);
		Drawing::DrawOutlinedCircle({ X, Y }, PointSize + 1, UniqueColor(0, 0, 0, 255));

		if (!LowerText.empty())
			Drawing::DrawString({ X, Y + (PointSize / 2) + 2 }, LowerText.c_str(), UniqueColor(255, 255, 255), /*UniqueAlignment::Alignment_Top |*/ UniqueAlignment::Alignment_Center_x);

		ImGui::SetWindowFontScale(1.f);
	}
	static void DrawPlayerOnRadar(const Vector3& EnemyOrigin, const UniqueColor& col, const std::string& UpperText, const std::string& LowerText, float Health, float MaxHealth)
	{
		ImVec2 winpos = ImGui::GetWindowPos();
		ImVec2 winsize = ImGui::GetWindowSize();

		auto CheatVars = GET_SETVAR(m_CheatVars, C_CheatVars);

		Vector3 LocalOrigin = UnityEngine::GetPosition(GlobalUnityVariables::LocalPlayerInfo.TransformComponent);
		const Vector3 DeltaFromLocal = EnemyOrigin - LocalOrigin;

		if (DeltaFromLocal.x > CheatVars.Zoom || DeltaFromLocal.x < -CheatVars.Zoom)
			return;

		if (DeltaFromLocal.z > CheatVars.Zoom || DeltaFromLocal.z < -CheatVars.Zoom)
			return;

		ImGui::SetWindowFontScale(CheatVars.TextScale);

		float PointSize = 5 * CheatVars.PointScale;

		float RelX = DeltaFromLocal.z / CheatVars.Zoom * (winsize.x / 2);
		float RelY = DeltaFromLocal.x / CheatVars.Zoom * (winsize.y / 2);

		float X = winpos.x + (winsize.x / 2) + RelX;
		float Y = winpos.y + (winsize.y / 2) + RelY;

		Vector2 Final;
		Final = RotatePoint({ winpos.x + (winsize.x / 2) ,  winpos.y + (winsize.y / 2) }, DEG2RAD(-60.f), { X , Y });

		Vector2 Final2;
		Final2 = RotatePoint({ winpos.x + (winsize.x / 2) ,  winpos.y + (winsize.y / 2) }, DEG2RAD(-30.f), { X , Y });


		X = Final.x;
		Y = Final2.y;
		if (!UpperText.empty())
			Drawing::DrawString({ X, Y - (PointSize / 2) - 2 }, UpperText.c_str(), UniqueColor(255, 255, 255), UniqueAlignment::Alignment_Bottom | UniqueAlignment::Alignment_Center_x);

		Drawing::DrawFilledCircle({ X, Y }, PointSize, col);
		Drawing::DrawOutlinedCircle({ X, Y }, PointSize + 1, UniqueColor(0, 0, 0, 255));

		EspBox Box;
		Box.x = X - (PointSize / 2);
		Box.y = Y - (PointSize);
		Box.w = PointSize * 2;
		Box.h = PointSize * 2;
		Box.IsValid = true;

		if (CheatVars.PlayersHealth && CheatVars.PlayersHealthRenderType != 0)
			DrawHealthBar(Box.x, Box.y, Box.h, Health, MaxHealth);

		if (!LowerText.empty())
			Drawing::DrawString({ X, Y + (PointSize / 2) + 2 }, LowerText.c_str(), UniqueColor(255, 255, 255), /*UniqueAlignment::Alignment_Top |*/ UniqueAlignment::Alignment_Center_x);

		ImGui::SetWindowFontScale(1.f);
	}
public:
	static void DrawEspRadar(const Vector3& EnemyOrigin, const UniqueColor& Color, const std::string& UpperText, const std::string& LowerText)
	{
		auto CheatVars = GET_SETVAR(m_CheatVars, C_CheatVars);

		if (CheatVars.Radar)
		{
			DrawActorOnRadar(EnemyOrigin, Color, UpperText, LowerText);
		}
	}
	static void DrawEspRadarPlayer(const Vector3& PlayerOrigin, const UniqueColor& Color, const std::string& UpperText, const std::string& LowerText, float Health, float MaxHealth)
	{
		auto CheatVars = GET_SETVAR(m_CheatVars, C_CheatVars);

		if (CheatVars.Radar)
		{
			DrawPlayerOnRadar(PlayerOrigin, Color, UpperText, LowerText, Health, MaxHealth);
		}
	}
};