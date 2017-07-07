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
		_keyBuffer[i + 1] = _keyBuffer[i]; // 키 버퍼를 한칸씩 밀어준다.
	}

	int keyTemp = 0;

	if (KEYMANAGER->isStayKeyDown(KEY_UP))		keyTemp += C_UP;
	if (KEYMANAGER->isStayKeyDown(KEY_DOWN))	keyTemp += C_DOWN;
	if (KEYMANAGER->isStayKeyDown(KEY_LEFT))	keyTemp += C_LEFT;
	if (KEYMANAGER->isStayKeyDown(KEY_RIGHT))	keyTemp += C_RIGHT;
	if (KEYMANAGER->isStayKeyDown(KEY_PUNCH))	keyTemp += C_PUNCH;
	if (KEYMANAGER->isStayKeyDown(KEY_PPUNCH))	keyTemp += C_PPUNCH;
	if (KEYMANAGER->isStayKeyDown(KEY_KICK))	keyTemp += C_KICK;
	if (KEYMANAGER->isStayKeyDown(KEY_PKICK))	keyTemp += C_PKICK;

	_keyBuffer[0] = keyTemp;
}

void CommandQueue::updateCommandBuffer()
{
	// [0, ..... 0] = 60개
	//int currentKey;
	
	bool isDifferentKey = false;
	bool isHoldKey = false;
	int keyHoldCount = 0;
	int commandArrayIndex = -1;
	for (int i = 0; i < KEYBUFFERSIZE; ++i)
	{
		if (_commandBuffer[commandArrayIndex] == _keyBuffer[i])
		{
			keyHoldCount++;
		}
		else
		{
			keyHoldCount = 0;
			isDifferentKey = true;
		}
		if (keyHoldCount < KEYHOLDCHECKTIME)
		{
			
		}
		if (isDifferentKey) // 기존의 키와 다른 버튼이 눌렸다면
		{
			commandArrayIndex++;
			_commandBuffer[commandArrayIndex] = _keyBuffer[i];
			//count = 0;
		}

		
		//++count;
	}
}

void CommandQueue::renderKeyBuffer()
{

}

void CommandQueue::renderCommandBuffer()
{

}

bool CommandQueue::checkCommand(vector<int> vInt) // 기술 등록시 사용하는 함수
{
	return false;
}
