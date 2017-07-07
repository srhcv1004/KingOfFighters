#pragma once
#include "stdafx.h"

class CharacterAction;
class Camera2D;

class Character
{
public:
	Character();
	virtual ~Character();

	virtual void init();
	virtual void update();
	virtual void render(Camera2D & camera);

	bool isJump();
	bool isAttack();
	bool isHit();
	bool isKO();

	const short getPlayerNumber() { return playerNumber_; }
	const CHARACTER::NAME getName() { return name_; }
	const CHARACTER::CONDITION getCondition() { return condition_; }
	const float getX() { return x_; }
	const float getY() { return y_; }
	const int getHP() { return hp_; }
	const int getMaxHP() { return maxHP_; }
	const DIRECTION getLookDirection() { return lookAt_; }
	CharacterAction * getAction() { return action_; }

	void setLook(DIRECTION lookTo);
	void setCondition(CHARACTER::CONDITION condition) { condition_ = condition; }
	void setAction(CharacterAction * action);

	void move(int x, int y);
	void hit(const ACTION::AttackData & attackData);

protected:
	short playerNumber_;			// 1P, 2P, ...
	CHARACTER::NAME name_;
	CHARACTER::CONDITION condition_;

	int hp_, maxHP_;
	float x_, y_;

	DIRECTION lookAt_;

	// state, behavior, action, ...
	CharacterAction * action_;
};

