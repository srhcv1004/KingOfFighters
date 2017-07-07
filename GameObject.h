#pragma once
#include "stdafx.h"
//#include "Camera2D.h"

class Character;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void init();
	void init(std::vector<CHARACTER::NAME> & characterList, std::vector<short> playerNumberList);
	void update();
	void render();		// camera 하위에 넘겨주기


	bool isGameOver();
	bool isKO(short playerNumber);

	bool isUpdate() { return update_; }
	bool isRender() { return render_; }

	std::vector<CHARACTER::NAME> getCharacterList();

	void setUpdate(bool update) { update_ = update; }
	void setRender(bool render) { render_ = render; }

private:
	std::vector<Character *> characterList_;
	//Camera2D camera_;

	bool update_;
	bool render_;

	int delayedFrame_;

	void gravity();
	void collisionCheck();
	void checkOutOfScreen();
};