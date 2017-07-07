#pragma once
#include "stdafx.h"

class Character;
class image;
class Camera2D;

class CharacterAction
{
public:
	CharacterAction();
	virtual ~CharacterAction();

	virtual void init() = 0;
	virtual void execute(Character & character) = 0;
	virtual void render(Camera2D & camera) = 0;

	virtual bool isActionEnd();

	const std::string getKey() { return key_; }
	const int getFrameCount() { return frameCount_; }

	virtual const RECT getAttackRect() = 0;
	virtual const RECT getHitRect() = 0;
	virtual const RECT getBodyRect() = 0;

	void setMaxFrameCount(int count) { maxFrameCount_ = count; }

protected:
	std::string key_;

	int frameCount_, maxFrameCount_;

	image * frameImage_;

	virtual void command() = 0;
};

