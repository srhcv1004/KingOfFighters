#pragma once
#include "gameNode.h"
#include "CommandQueueDefine.h"
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

	bool checkCommand(vector<int> vInt); // ��� ��Ͻ� ����ϴ� �Լ�.
	//int�� ���Ϳ� Ŀ�ǵ带 ���������� ������ ��. Ŀ�ǵ�� commandQueueDefine����
};