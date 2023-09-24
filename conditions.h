#pragma once
#include "includes.h"

class Condition
{
private:
	static bool IsSameAlliance(System_String_o* Alliance, uint32_t MyHashedAlliance)
	{
		if (MyHashedAlliance == 0)
			return false;

		if (!Utils::IsValidPtr(Alliance))
			return false;

		return crypto::hash_string((wchar_t*)&Alliance->fields.m_firstChar) == MyHashedAlliance;
	}
	static bool IsSameGuild(System_String_o* Guild, uint32_t MyHashedGuild)
	{
		if (MyHashedGuild == 0)
			return false;

		if (!Utils::IsValidPtr(Guild))
			return false;

		return crypto::hash_string((wchar_t*)&Guild->fields.m_firstChar) == MyHashedGuild;
	}
public:
	static bool PlayerCheck(System_String_o* Alliance, System_String_o* Guild, bool InParty, uint32_t MyHashedAlliance, uint32_t MyHashedGuild, C_CheatVars* CheatVars)
	{
		if (CheatVars->PlayersAllianceFilter)
		{
			if (IsSameAlliance(Alliance, MyHashedAlliance))
				return false;
		}
		if (CheatVars->PlayersGuildFilter)
		{
			if (IsSameGuild(Alliance, MyHashedAlliance))
				return false;
		}
		if (CheatVars->PlayersInPartyFiltter)
		{
			if (InParty)
				return false;
		}
		return true;
	}
	static bool EnchantCheck(int Enchant, const Enchantments& Enchantment)
	{
		if (Enchant == 0)
			return Enchantment.b0;
		else if (Enchant == 1)
			return Enchantment.b1;
		else if (Enchant == 2)
			return Enchantment.b2;
		else if (Enchant == 3)
			return Enchantment.b3;
		else if (Enchant == 4)
			return Enchantment.b4;
	}
	static bool TierCheck(int Tier, int RareState, const Rarities& Rarity)
	{
		if (Tier == 1 && RareState == 0)
			return Rarity.b10;

		else if (Tier == 2 && RareState == 0)
			return Rarity.b20;

		else if (Tier == 3 && RareState == 0)
			return Rarity.b30;

		else if (Tier == 4 && RareState == 0)
			return Rarity.b40;
		else if (Tier == 4 && RareState == 1)
			return Rarity.b41;
		else if (Tier == 4 && RareState == 2)
			return Rarity.b42;
		else if (Tier == 4 && RareState == 3)
			return Rarity.b43;

		else if (Tier == 5 && RareState == 0)
			return Rarity.b50;
		else if (Tier == 5 && RareState == 1)
			return Rarity.b51;
		else if (Tier == 5 && RareState == 2)
			return Rarity.b52;
		else if (Tier == 5 && RareState == 3)
			return Rarity.b53;

		else if (Tier == 6 && RareState == 0)
			return Rarity.b60;
		else if (Tier == 6 && RareState == 1)
			return Rarity.b61;
		else if (Tier == 6 && RareState == 2)
			return Rarity.b62;
		else if (Tier == 6 && RareState == 3)
			return Rarity.b63;

		else if (Tier == 7 && RareState == 0)
			return Rarity.b70;
		else if (Tier == 7 && RareState == 1)
			return Rarity.b71;
		else if (Tier == 7 && RareState == 2)
			return Rarity.b72;
		else if (Tier == 7 && RareState == 3)
			return Rarity.b73;

		else if (Tier == 8 && RareState == 0)
			return Rarity.b80;
		else if (Tier == 8 && RareState == 1)
			return Rarity.b81;
		else if (Tier == 8 && RareState == 2)
			return Rarity.b82;
		else if (Tier == 8 && RareState == 3)
			return Rarity.b83;
	}
};