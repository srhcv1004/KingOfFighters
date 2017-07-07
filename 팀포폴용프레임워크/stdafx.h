#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <tchar.h>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "soundManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "sceneManager.h"
#include "utils.h"
#include "additionalUtils.h"
#include "txtData.h"
#include "digManager.h"


using namespace std;
using namespace THETA_UTIL;

//==============================
// ## �����ι� ## 17.04.26 ##
//==============================

#define WINNAME (LPTSTR)(TEXT("Theta API"))	//������ â �̸�
#define WINSTARTX 20						//������ ������ǥX
#define WINSTARTY 20						//������ ������ǥY
#define WINSIZEX 1024						//������ ����ũ��
#define WINSIZEY 768						//������ ����ũ��
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//�̱���ȭ ��Ų Ŭ���� ������ȭ
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define DIG digManager::getSingleton()


//==============================
// ## ��ũ���Լ� ## 17.04.26 ##
//==============================

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL;}}

//==============================
// ## �������� ## 17.05.01 ##
//==============================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;