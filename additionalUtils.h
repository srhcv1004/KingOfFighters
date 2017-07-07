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
#define DEGREE /180*PI  // 삼각함수 사용 시 각도 뒤에 붙여서 사용. ex) 180 DEGREE 라고 하면 PI가 됨.
#endif
#ifndef BOOL
typedef int BOOL;
#endif


//헤더 선언부
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
	}DI_8; // 8방향
	typedef enum DIRECTION_4
	{
		DI4_LEFT,	// left
		DI4_RIGHT,	// right
		DI4_TOP,		// top
		DI4_BOTTOM,	// bottom
		DI4_END
	}DI_4; // 4방향
	//struct
	typedef struct tagFloatPoint // float형 POINT
	{
		float x, y;
		tagFloatPoint(float x = 0.0f, float y = 0.0f)
			: x(x), y(y)
		{}
	}FloatPoint, fPOINT;
	typedef struct tagFloatRect // float형 RECT
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
	void RectangleMakeRect(HDC hdc, const RECT* rc);	// RECT구조체 받아서 사각형 그려줌
	void EllipseMakeRect(HDC hdc, const RECT* rc);		// RECT구조체 받아서 원 그려줌
	void LineMakeRect(HDC hdc, const RECT* rc);		// RECT구조체 받아서 사각형(선) 그려줌
	void LineMakeRect(HDC hdc, int left, int top, int right, int bottom); // 사각형(선) 그려줌
	void RapidStretchBlt(HDC destDC, int destX, int destY, int destW, int destH,
		HDC sourDC, int sourX, int sourY, int sourW, int sourH); // 빠른 StretchBlt
	void ExactStretchBlt(HDC destDC, int destX, int destY, int destW, int destH,
		HDC sourDC, int sourX, int sourY, int sourW, int sourH); // 정교한 StretchBlt
	void ExtendBlt(HDC destDC, int destX, int destY, int destW, int destH,
		HDC sourDC, int sourX, int sourY, int sourW, int sourH,
		bool isTrans = false, COLORREF transColor = RGB(255, 0, 255)); // 뒤집을 수 있는 TransparentBlt
	//degree
	float DegToRad(float degree); // degree를 radian으로 변환해줌
	float RadToDeg(float radian); // radian을 degree로 변환해줌
	int SetRotateImageFrame(float startAngle, int nFrame, bool isClockWise, float currentAngle); // 앵글을 프레임으로 변환
}


