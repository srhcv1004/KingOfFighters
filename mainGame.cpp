#include "stdafx.h"
#include "mainGame.h"

//======================================
// �����ڶ� �Ҹ��ڴ� ���� �ʴ´�
//======================================
mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}


//======================================
// �����ڶ� �Ҹ��ڴ� ���� �ʴ´�
//======================================


//�ʱ�ȭ�� ������ ���⿡�ٰ� �ض�
HRESULT mainGame::init(void)
{
	gameNode::init(true);


	return S_OK;
}

//�޸� ������ ������ ���⿡�ٰ� �ض�
void mainGame::release(void)
{
	gameNode::release();

}

//������(��) ������ ���⿡�ٰ� �ض�
void mainGame::update(void)
{
	gameNode::update();

}

//������ ���⿡�� �׷��� 
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ������� ================


	//===============�Ʒ��� �ǵ������� =================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
