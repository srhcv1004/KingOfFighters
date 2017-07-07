#pragma once

enum class DIRECTION
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LEFTUP,
	RIGHTUP,
	LEFTDOWN,
	RIGHTDOWN
};

namespace CHARACTER
{
	enum NAME
	{
		TERRY,
		HEAVY_D,
		RALF,
		ATHENA
	};

	enum class CONDITION
	{
		NONE,
		NORMAL,
		SUPER_ARMOR,
		STUN,
		GUARD_BREAK
	};
}

namespace ACTION
{
	enum class ATTACK_TYPE
	{
		NORMAL,
		FLY,
		DOWN,
		PUSH,
		GRAB
	};

	struct AttackData
	{
		std::string key;
		ATTACK_TYPE type;
		int damage;
		short stunPercent;

		AttackData() : type(ACTION::ATTACK_TYPE::NORMAL), damage(0), stunPercent(0) {}
	};
}

namespace UI
{
	//const int MAP_BORDER_RIGHT = ;
	//const int MAP_BORDER_BOTTOM = ;
}