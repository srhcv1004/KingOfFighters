#include "stdafx.h"
#include "mainGame.h"

//�������� �����ϴ� ��
HINSTANCE	_hInstance;		//window App ������ȣ
HWND		_hWnd;			//������ �ڵ�
mainGame	_mg;
POINT		_ptMouse;		//���콺 ��ǥ ���� POINT ����

//=============================================================================

LPTSTR _lpszClass = TEXT("Theta API");	//������ â �ؽ�Ʈ

//�Լ� ���漱�� == �Լ��� ������Ÿ�� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowsSize(int x, int y, int width, int height);

//�̰� �����Լ�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;	//�ü������ �߻��ϴ� �޽��� ������ �����ϱ� ���� ����ü
	WNDCLASS	wndClass;	//������(â)�� ������ �����ϱ� ���� ����ü

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸� ����
	wndClass.cbWndExtra = 0;										//������ ���� �޸� ����
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��׶��� Į��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//������ Ŀ�� ��� (���� ȭ��ǥ)
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������ ������ ���
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = _lpszClass;							//������ Ŭ�����̸�
	wndClass.lpszMenuName = NULL;									//������ �޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ ��Ÿ��

	//������ ���� ���
	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,				//������ â ������ġ X
		WINSTARTY,				//������ â ������ġ y
		WINSIZEX,				//������ â ����ũ��
		WINSIZEY,				//������ â ����ũ��
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	//Ŭ���̾�Ʈ ���� ������ �Ϸ�.
	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//������ â ȭ�鿡 �����ִ� ��ɾ�
	ShowWindow(_hWnd, cmdShow);

	//���ΰ��� Ŭ������ �̴�(�ʱ�ȭ) �Լ��� �����ϸ�
	if (FAILED(_mg.init()))
	{
		//����ó��
		return 0;
	}

	//�޽��� ����
	//GetMessage : �޽����� ������ �׶� ������ ����
	//PeekMessage : �׽� ������ ����

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);		//Ű���� �Է��ϴ� ���� �� �޽��� ó���� ���
			DispatchMessage(&message);		//������ ������� �޽������� �����ϴ� ���
		}
		else
		{
			//���⼭ ó���Ѵ�
			TIMEMANAGER->update(60.0f);
			_mg.update();
			_mg.render();
		}

	}

	//������ �Լ��� �ؿ� �ִٴ°� �޽����� �� �������� ���ΰ��� �����ض�
	_mg.release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

//Ŭ���̾�Ʈ ���� ������ �Լ�
void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}
