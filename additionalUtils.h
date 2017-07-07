#pragma once
#include "stdafx.h"

//define
#ifndef PI
#define PI 3.141592654f
#endif
#ifndef PI2
#define PI2 PI * 2
#endif
#ifndef DEGREE
#define DEGREE /180*PI  // �ﰢ�Լ� ��� �� ���� �ڿ� �ٿ��� ���. ex) 180 DEGREE ��� �ϸ� PI�� ��.
#endif
#ifndef BOOL
typedef int BOOL;
#endif


//��� �����
namespace THETA_UTIL
{
	//enum
	typedef enum DIRECTION_8
	{
		DI8_L,	// left
		DI8_R,	// right
		DI8_T,	// top
		DI8_B,	// bottom
		DI8_LT,  // left top
		DI8_RT,	// right top
		DI8_LB,	// left bottom
		DI8_RB,	// right bottom
		DI8_END
	}DI_8; // 8����
	typedef enum DIRECTION_4
	{
		DI4_LEFT,	// left
		DI4_RIGHT,	// right
		DI4_TOP,		// top
		DI4_BOTTOM,	// bottom
		DI4_END
	}DI_4; // 4����
	//struct
	typedef struct tagFloatPoint // float�� POINT
	{
		float x, y;
		tagFloatPoint(float x = 0.0f, float y = 0.0f)
			: x(x), y(y)
		{}
	}FloatPoint, fPOINT;
	typedef struct tagFloatRect // float�� RECT
	{
		float left, top, right, bottom;
		tagFloatRect(float left = 0.0f, float top = 0.0f, float right = 0.0f, float bottom = 0.0f)
			:left(left), top(top), right(right), bottom(bottom)
		{}
	}FloatRect, fRECT;
	//[fRECT, fPOINT] struct func
	fPOINT fPointMake(float x, float y);
	fPOINT PtTofPT(POINT pt);
	POINT fPtToPt(fPOINT fpt);
	fRECT RectTofRect(RECT* rc);
	RECT fRectToRect(fRECT* frc);
	
	//draw
	void RectangleMakeRect(HDC hdc, const RECT* rc);	// RECT����ü �޾Ƽ� �簢�� �׷���
	void EllipseMakeRect(HDC hdc, const RECT* rc);		// RECT����ü �޾Ƽ� �� �׷���
	void LineMakeRect(HDC hdc, const RECT* rc);		// RECT����ü �޾Ƽ� �簢��(��) �׷���
	void LineMakeRect(HDC hdc, int left, int top, int right, int bottom); // �簢��(��) �׷���
	void RapidStretchBlt(HDC destDC, int destX, int destY, int destW, int destH,
		HDC sourDC, int sourX, int sourY, int sourW, int sourH); // ���� StretchBlt
	void ExactStretchBlt(HDC destDC, int destX, int destY, int destW, int destH,
		HDC sourDC, int sourX, int sourY, int sourW, int sourH); // ������ StretchBlt
	void ExtendBlt(HDC destDC, int destX, int destY, int destW, int destH,
		HDC sourDC, int sourX, int sourY, int sourW, int sourH,
		bool isTrans = false, COLORREF transColor = RGB(255, 0, 255)); // ������ �� �ִ� TransparentBlt
	//degree
	float DegToRad(float degree); // degree�� radian���� ��ȯ����
	float RadToDeg(float radian); // radian�� degree�� ��ȯ����
	int SetRotateImageFrame(float startAngle, int nFrame, bool isClockWise, float currentAngle); // �ޱ��� ���������� ��ȯ
}


