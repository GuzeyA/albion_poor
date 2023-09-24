#pragma once
#include "includes.h"

uintptr_t Address_GameObjectManager;

uintptr_t Address_GetMob;
uintptr_t Address_GetMobInfo;

uintptr_t Address_PlayerIsMounted;
uintptr_t Address_PlayerGetName;

uintptr_t Address_GetPlayerInfo;
uintptr_t Address_GetDungeonInfo;

DWORD Offset_MobTier;
DWORD Offset_MobDangerState;
DWORD Offset_MobAlignment;
DWORD Offset_MobTypeCategory;

DWORD Offset_PlInfoInParty;
DWORD Offset_PlInfoGuild;
DWORD Offset_PlInfoAliance;

DWORD Offset_DnInfoEnchant;

#define Offset_NativePtr 0x10
#define Offset_CompomentOwner 0x30
#define Offset_ComponentsSize 0x40
#define Offset_ComponentsPtr 0x30
#define Offset_MonoPtr 0x28
#define Offset_TransformCompoment 0x8

//#define Offset_MobTier 0xE8
#define Offset_MabRare 0x1D0
#define Offset_MobName 0x14

#define Offset_Mob2 0xD8
#define Offset_Mob3 0x10

#define Offset_PlayerUnk2 0x80
#define Offset_PlayerHp 0x10
#define Offset_PlayerMaxHp 0x40

//#define ALIGN_DOWN_BY(length, alignment) \
//    ((ULONG_PTR)(length) & ~((ULONG_PTR)(alignment) - 1))
//
//#define ALIGN_DOWN_POINTER_BY(address, alignment) \
//    ((PVOID)((ULONG_PTR)(address) & ~((ULONG_PTR)(alignment) - 1)))
//BOOL PTRCheck(LPCVOID lp, UINT_PTR ucb)
//{
//	SYSTEM_INFO sysInfo{};
//	GetSystemInfo(&sysInfo);
//	ULONG PageSize;
//	BOOLEAN Result = FALSE;
//	volatile CHAR* Current;
//	PCHAR Last;
//
//	if (!ucb) return FALSE;
//	if (!lp) return TRUE;
//	PageSize = sysInfo.dwPageSize;
//
//	Current = (volatile CHAR*)lp;
//	Last = (PCHAR)((ULONG_PTR)lp + ucb - 1);
//
//	if (Last < Current) return TRUE;
//
//	__try
//	{
//		*Current;
//
//		Current = (volatile CHAR*)ALIGN_DOWN_POINTER_BY(Current, PageSize);
//		Last = (PCHAR)ALIGN_DOWN_POINTER_BY(Last, PageSize);
//
//		while (Current != Last)
//		{
//			Current += PageSize;
//		}
//	}
//	__except (EXCEPTION_EXECUTE_HANDLER)
//	{
//		Result = TRUE;
//	}
//	return Result;
//}
//bool IsBadReadPtr(void* p)
//{
//	MEMORY_BASIC_INFORMATION mbi = { 0 };
//	if (::VirtualQuery(p, &mbi, sizeof(mbi)))
//	{
//		DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
//		bool b = !(mbi.Protect & mask);
//		// check the page is not a guard page
//		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;
//
//		return b;
//	}
//	return true;
//}
//bool isVaild(void* p)
//{
//	__try
//	{
//		memcpy(p, p, 8);
//	}
//	__except (1) { return false; }
//	return true;
//}
#include "dumper.h"
#if DUMPOFFSETS
#define BeginDump()   Utils::Print(/*xorstr_*/("[Dump for 22.09.2021]\nMainInstance = 0x%p\n"), (uintptr_t)GlobalVars::g_hModuleBase);
#define Addy(Off) Utils::Print(/*xorstr_*/("%s = 0x%p\n"), /*xorstr_*/(#Off), Off - (uintptr_t)GlobalVars::g_hModuleBase);
#define Offy(Off) Utils::Print(/*xorstr_*/("%s = 0x%p\n"), /*xorstr_*/(#Off), Off);
#define Indx(Idx) Utils::Print(/*xorstr_*/("%s = %d\n"), /*xorstr_*/(#Idx), Idx);
#define NTab(Tab) Utils::Print(/*xorstr_*/("[%s]\n"), Tab);
#endif
//#include "PhysX_3.4/Include/PxScene.h"
//#include "PhysX_3.4/Include/PxPhysics.h"
class Offsets
{
private:
public:
	static void InitStaticOffsets()
	{
		auto MainInstance = (uintptr_t)GlobalVars::g_hModuleBase;
		Address_GameObjectManager = RVA((uintptr_t)Utils::FindSignature(xorstr_("48 8B 05 ? ? ? ? 66 83 F9 05"), xorstr_(L"UnityPlayer.dll")), 7);
		//typedef uintptr_t(*getInfo)(void* a1);
		//getInfo fn = (getInfo)(GameAssembly + 0x04EFB70);
		//uintptr_t test = fn(Mob);
		//getInfo fn1 = (getInfo)(GameAssembly + 0x10A60E0);
		//bd5_o* test1 = (bd5_o*)fn1((void*)test);
		Address_GetMob = RVA((uintptr_t)Utils::FindSignature(xorstr_("E8 ? ? ? ? 48 85 C0 74 78 4C 8B 00"), xorstr_(L"GameAssembly.dll")), 5);
		Address_GetMobInfo = RVA((uintptr_t)Utils::FindSignature(xorstr_("E8 ? ? ? ? 45 33 C9 45 8B 87"), xorstr_(L"GameAssembly.dll")), 5);
		Offset_MobTier = StaticDumper::GetMobTierOffset();
		Offset_MobDangerState = StaticDumper::GetMobDangerStateOffset();
		Offset_MobAlignment = StaticDumper::GetMobAlignmentOffset();
		Offset_MobTypeCategory = StaticDumper::GetMobTypeCategoryOffset();

		Offset_PlInfoInParty = StaticDumper::GetPlInfoInPartyOffset();
		Offset_PlInfoGuild = StaticDumper::GetPlInfoGuildOffset();
		Offset_PlInfoAliance = StaticDumper::GetPlInfoAlianceOffset();

		Offset_DnInfoEnchant = StaticDumper::GetDnInfoEnchantOffset();

		Address_PlayerIsMounted = RVA((uintptr_t)Utils::FindSignature(xorstr_("E8 ? ? ? ? 33 D2 48 8B CF 0F B6 D8 E8 ? ? ? ? 33 ED"), xorstr_(L"GameAssembly.dll")), 5);
		Address_PlayerGetName = RVA((uintptr_t)Utils::FindSignature(xorstr_("E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8B F0 F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 33 D2 49 8B CE E8 ? ? ? ? 48 85 ED"), xorstr_(L"GameAssembly.dll")), 5);
		Address_GetPlayerInfo = RVA((uintptr_t)Utils::FindSignature(xorstr_("E8 ? ? ? ? 3B F3 0F 8D ? ? ? ?"), xorstr_(L"GameAssembly.dll")), 5);
		Address_GetDungeonInfo = RVA((uintptr_t)Utils::FindSignature(xorstr_("E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 44 38 25 ? ? ? ? 0F B6 B0 ? ? ? ?"), xorstr_(L"GameAssembly.dll")), 5);

#if DUMPOFFSETS
		Print();
#endif

	}
#if DUMPOFFSETS
	static void Print()
	{
		BeginDump();

		NTab(xorstr_("General Addresses"));

		NTab(xorstr_("General Offsets"));


		NTab(xorstr_("Dumper Offsets & Addresses"));


		NTab(xorstr_("VMT Functions"));


		NTab(xorstr_("Functions"));

	}
#endif
};