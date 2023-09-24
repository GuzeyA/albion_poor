#pragma once
#include "includes.h"
#include "il2cpp.h"

enum MobTypeCategory : int
{
	Critter = 0,
	Trash = 1,
	Standard = 2,
	Champion = 3,
	MiniBoss = 4,
	Boss = 5,
	Chest = 6,
	Vanity = 7,
	Summon = 8,
	Other = 9,
};

enum MobAlignments : int
{
	Hostile = 0,
	Guard = 1,
	PvpRuleDepended = 2,
	Decoration = 3,
	Friendly = 4,
};

class GameObject
{
public:
	char pad_0000[48]; //0x0000
	class ComponentList* N0000028C; //0x0030
	char pad_0038[8]; //0x0038
	uint32_t ComponentSize; //0x0040
	char pad_0044[12]; //0x0044
	uint32_t Layer; //0x0050
	uint16_t Tag; //0x0054
	char pad_0056[1]; //0x0056
	uint8_t IsActive; //0x0057
	char pad_0058[8]; //0x0058
	char* Name; //0x0060

	const char* get_name() {
		return *reinterpret_cast<const char**>(std::uintptr_t(this) + 0x60);
	}

	int16_t get_object_tag() {
		return *reinterpret_cast<int16_t*>(std::uintptr_t(this) + 0x54);
	}
}; //Size: 0x0068

class game_object_manager
{
public:
	class LastObjectBase* LastTaggedObject; //0x0000
	class BaseObject* TaggedObjects; //0x0008
	class LastObjectBase* LastActiveObject; //0x0010
	class BaseObject* ActiveObjects; //0x0018
	class LastObjectBase* LastCurrentObject; //0x0020
	class BaseObject* CurrentObjects; //0x0028
}; //Size: 0x0030

class BaseObject
{
public:
	char pad_0000[8]; //0x0000
	class BaseObject* nextObjectLink; //0x0008
	class GameObject* object; //0x0010
}; //Size: 0x0018

class LastObjectBase
{
public:
	char pad_0000[16]; //0x0000
	class GameObject* lastobject; //0x0010
}; //Size: 0x0018