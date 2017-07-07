#pragma once
#include "gameNode.h"
#include "commandQueueDefine.h"
#include <vector>



class CommandQueue : public gameNode
{
private:
	int _keyBuffer[KEYBUFFERSIZE];
	int _commandBuffer[COMMANDBUFFERSIZE];

	bool _debugMode;


public:
	CommandQueue();
	~CommandQueue();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void initKeyBuffer();
	void initCommandBuffer();

	void updateKeyBuffer();
	void updateCommandBuffer();

	void renderKeyBuffer();
	void renderCommandBuffer();

	bool checkCommand(vector<int> vInt); // 기술 등록시 사용하는 함수.
	//int형 벡터에 커맨드를 순차적으로 넣으면 됨. 커맨드는 commandQueueDefine참조
};