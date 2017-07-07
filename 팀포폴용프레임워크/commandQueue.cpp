#include "stdafx.h"
#include "commandQueue.h"

CommandQueue::CommandQueue(){}
CommandQueue::~CommandQueue(){}

HRESULT CommandQueue::init(void)
{
	initKeyBuffer();
	initCommandBuffer();

	_debugMode = true;

	return S_OK;
}

void CommandQueue::release(void)
{
	updateKeyBuffer();
	updateCommandBuffer();
}

void CommandQueue::update(void)
{
	updateKeyBuffer();
	updateCommandBuffer();
}

void CommandQueue::render(void)
{
	if (_debugMode)
	{
		renderKeyBuffer();
		renderCommandBuffer();
	}
}
void CommandQueue::initKeyBuffer()
{
	for (int i = 0; i < KEYBUFFERSIZE; ++i)
	{
		_keyBuffer[i] = C_IDLE;
	}
}

void CommandQueue::initCommandBuffer()
{
	for (int i = 0; i < COMMANDBUFFERSIZE; ++i)
	{
		_commandBuffer[i] = C_IDLE;
	}
}

void CommandQueue::updateKeyBuffer()
{
	for (int i = KEYBUFFERSIZE - 2; i >= 0; --i)
	{
		_keyBuffer[i + 1] = _keyBuffer[i]; // Ű ���۸� ��ĭ�� �о��ش�.
	}

	int keyTemp = 0;

	if (KEYMANAGER->isStayKeyDown(KEY_UP))		keyTemp += C_UP;
	if (KEYMANAGER->isStayKeyDown(KEY_DOWN))	keyTemp += C_UP;
	if (KEYMANAGER->isStayKeyDown(KEY_LEFT))	keyTemp += C_UP;
	if (KEYMANAGER->isStayKeyDown(KEY_RIGHT))	keyTemp += C_UP;
	if (KEYMANAGER->isStayKeyDown(KEY_PUNCH))	keyTemp += C_UP;
	if (KEYMANAGER->isStayKeyDown(KEY_PPUNCH))	keyTemp += C_UP;
	if (KEYMANAGER->isStayKeyDown(KEY_KICK))	keyTemp += C_UP;
	if (KEYMANAGER->isStayKeyDown(KEY_PKICK))	keyTemp += C_UP;
}

void CommandQueue::updateCommandBuffer()
{

}

void CommandQueue::renderKeyBuffer()
{

}

void CommandQueue::renderCommandBuffer()
{

}

bool CommandQueue::checkCommand(vector<int> vInt) // ��� ��Ͻ� ����ϴ� �Լ�
{
	return false;
}
