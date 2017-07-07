#pragma once
#include "stdafx.h"
#include "singletonBase.h"

class CharacterAction;

class CharacterActionManager : public singletonBase<CharacterActionManager>
{
public:
	CharacterActionManager();
	~CharacterActionManager();

	void addAction(std::string key, CharacterAction * action);
	void getAction(std::string key);

	void addAttackData(std::string key, ACTION::AttackData data);
	void getAttackData(std::string key);

private:
	std::map<std::string, CharacterAction *> actionMap_;
	std::map<std::string, ACTION::AttackData> attackDataMap_;

};