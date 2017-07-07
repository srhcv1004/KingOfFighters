#include "stdafx.h"
#include "additionalUtils.h"


//CPP 구현부 (실제 사용시 이 아래는 .cpp파일로 분리할 것)
namespace THETA_UTIL
{
	fPOINT fPointMake(float x, float y)
	{
		fPOINT fpt;
		ZeroMemory(&fpt, sizeof(fpt));
		fpt.x = x;
		fpt.y = y;
		return fpt;
	}
	fPOINT PtTofPT(POINT pt)
	{
		fPOINT fpt;
		fpt.x = (float)pt.x;
		fpt.y = (float)pt.y;
		return fpt;
	}
	POINT fPtToPt(fPOINT fpt)
	{
		POINT pt;
		pt = { (LONG)fpt.x, (LONG)fpt.y };
		return pt;
	}
	fRECT RectTofRect(RECT* rc)
	{
		fRECT frc;
		frc.left = rc->left;
		frc.top = rc->top;
		frc.right = rc->right;
		frc.bottom = rc->bottom;
		return frc;
	}
	RECT fRectToRect(fRECT* frc)
	{
		RECT rc;
		rc.left = frc->left;
		rc.top = frc->top;
		rc.right = frc->right;
		rc.bottom = frc->bottom;
		return rc;
	}

	void RectangleMakeRect(HDC hdc, const RECT* rc)
	{
		if (rc != NULL)
		{
			Rectangle(hdc, rc->left, rc->top, rc->right, rc->bottom);
		}
	}
	void EllipseMakeRect(HDC hdc, const RECT* rc)
	{
		if (rc != NULL)
		{
			Ellipse(hdc, rc->left, rc->top, rc->right, rc->bottom);
		}
	}
	void LineMakeRect(HDC hdc, const RECT* rc)
	{
		if (rc != NULL)
		{
			MoveToEx(hdc, rc->left, rc->top, NULL);
			LineTo(hdc, rc->right, rc->top);
			MoveToEx(hdc, rc->right, rc->top, NULL);
			LineTo(hdc, rc->right, rc->bottom);
			MoveToEx(hdc, rc->right, rc->bottom, NULL);
			LineTo(hdc, rc->left, rc->bottom);
			MoveToEx(hdc, rc->left, rc->bottom, NULL);
			LineTo(hdc, rc->left, rc->top);
		}
	}
	void LineMakeRect(HDC hdc, int left, int top, int right, int bottom)
	{
		MoveToEx(hdc, left, top, NULL);
		LineTo(hdc, right, top);
		MoveToEx(hdc, right, top, NULL);
		LineTo(hdc, right, bottom);
		MoveToEx(hdc, right, bottom, NULL);
		LineTo(hdc, left, bottom);
		MoveToEx(hdc, left, bottom, NULL);
		LineTo(hdc, left, top);
	}
	void RapidStretchBlt(HDC destDC, int destX, int destY, int destW, int destH,
		HDC sourDC, int sourX, int sourY, int sourW, int sourH)
	{
		int old = SetStretchBltMode(destDC, COLORONCOLOR);
		StretchBlt(destDC, destX, destY, destW, destH, sourDC, sourX, sourY, sourW, sourH, SRCCOPY);
		SetStretchBltMode(destDC, old);
	}
	void ExactStretchBlt(HDC destDC, int destX, int destY, int destW, int destH,
		HDC sourDC, int sourX, int sourY, int sourW, int sourH)
	{
		int old = SetStretchBltMode(destDC, HALFTONE);
		StretchBlt(destDC, destX, destY, destW, destH, sourDC, sourX, sourY, sourW, sourH, SRCCOPY);
		SetStretchBltMode(destDC, old);
	}
	void ExtendBlt(HDC destDC, int destX, int destY, int destW, int destH,
		HDC sourDC, int sourX, int sourY, int sourW, int sourH,
		bool isTrans, COLORREF transColor)
	{
		if (isTrans)
		{
			HDC hdcTemp = GetDC(_hWnd);
			HDC hdcReverse;
			HBITMAP hbitTemp;
			short diWidth = 1;
			short diHeight = 1;
			if (destW < 0) diWidth = -1;
			if (destH < 0) diHeight = -1;
			hdcReverse = CreateCompatibleDC(hdcTemp);
			hbitTemp = CreateCompatibleBitmap(hdcTemp, sourW, sourH);
			SelectObject(hdcReverse, hbitTemp);
			//_imageInfo->hMemDC
			SetStretchBltMode(hdcReverse, COLORONCOLOR);
			switch (diWidth)
			{
			case 1:
				switch (diHeight)
				{
				case 1:
					PatBlt(hdcReverse, 0, 0, sourW, sourH, WHITENESS);
					StretchBlt(hdcReverse, 0, 0, sourW, sourH,
						sourDC, sourX, sourY, sourW, sourH, SRCCOPY);
					GdiTransparentBlt(destDC,
						destX,
						destY,
						diWidth*destW,
						diHeight*destH,
						hdcReverse,
						0, 0,
						sourW,
						sourH,
						transColor);
					break;
				case -1:
					PatBlt(hdcReverse, 0, 0, sourW, sourH, WHITENESS);
					StretchBlt(hdcReverse, 0, sourH, sourW, -sourH - 1,
						sourDC, sourX, sourY, sourW, sourH, SRCCOPY);
					GdiTransparentBlt(destDC,
						destX,
						destY - diHeight*destH,
						diWidth*destW,
						diHeight*destH,
						hdcReverse,
						0, 0,
						sourW,
						sourH,
						transColor);
					break;
				}
				break;
			case -1:
				switch (diHeight)
				{
				case 1:
					PatBlt(hdcReverse, 0, 0, sourW, sourH, WHITENESS);
					StretchBlt(hdcReverse, sourW, 0, -sourW - 1, sourH,
						sourDC, sourX, sourY, sourW, sourH, SRCCOPY);
					GdiTransparentBlt(destDC,
						destX - diWidth*destW,
						destY,
						diWidth*destW,
						diHeight*destH,
						hdcReverse,
						0, 0,
						sourW,
						sourH,
						transColor);
					break;
				case -1:
					PatBlt(hdcReverse, 0, 0, sourW, sourH, WHITENESS);
					StretchBlt(hdcReverse, sourW, sourH, -sourW - 1, -sourH - 1,
						sourDC, sourX, sourY, sourW, sourH, SRCCOPY);
					GdiTransparentBlt(destDC,
						destX - diWidth*destW,
						destY - diHeight*destH,
						diWidth*destW,
						diHeight*destH,
						hdcReverse,
						0, 0,
						sourW,
						sourH,
						transColor);
					break;
				}
				break;
			}
			ReleaseDC(_hWnd, hdcTemp);
			DeleteDC(hdcTemp);
			DeleteObject(hbitTemp);
			DeleteDC(hdcReverse);
		}
		else
		{
			//백버퍼에 있는 것을 앞으로 고속복사 해준다
			SetStretchBltMode(destDC, COLORONCOLOR);
			StretchBlt(destDC, destX, destY, destW, destH,
				sourDC, sourX, sourY, sourW, sourH, SRCCOPY);
		}
	}
	float DegToRad(float degree)
	{
		return degree / 180 * PI;
	}
	float RadToDeg(float radian)
	{
		return radian / PI * 180;
	}
	int SetRotateImageFrame(float startAngle, int nFrame, bool isClockWise, float currentAngle)
	{
		float tempSAngle = startAngle;
		float tempCAngle = currentAngle;
		while (tempSAngle < -PI || tempSAngle > PI) // 각보정
		{
			if (tempSAngle < -PI)
			{
				tempSAngle += PI2;
			}
			else if (tempSAngle > PI)
			{
				tempSAngle -= PI2;
			}
		}
		if (isClockWise) // 시계방향
		{
			while (tempCAngle < tempSAngle - PI / nFrame
				|| tempCAngle > tempSAngle + PI2 - PI / nFrame) // 각보정
			{
				if (tempCAngle < tempSAngle - PI / nFrame)
				{
					tempCAngle += PI2;
				}
				else if (tempCAngle >= tempSAngle + PI2 - PI / nFrame)
				{
					tempCAngle -= PI2;
				}
			}
			for (int i = 0; i < nFrame; i++)
			{
				if (tempCAngle - tempSAngle >= -PI / nFrame + i*PI2 / nFrame
					&& tempCAngle - tempSAngle <= -PI / nFrame + (i + 1)*PI2 / nFrame)
					return i;
			}
		}
		else // 반시계방향
		{
			while (tempCAngle < tempSAngle - PI2 + PI / nFrame 
				|| tempCAngle > tempSAngle + PI / nFrame) // 각보정
			{
				if (tempCAngle < tempSAngle - PI2 + PI / nFrame)
				{
					tempCAngle += PI2;
				}
				else if (tempCAngle >= tempSAngle + PI / nFrame)
				{
					tempCAngle -= PI2;
				}
				for (int i = 0; i < nFrame; i++)
				{
					if (tempCAngle - tempSAngle <= +PI / nFrame - i*PI2 / nFrame
						&& tempCAngle - tempSAngle >= +PI / nFrame - (i + 1)*PI2 / nFrame)
						return i;
				}
			}
		}
		return 0; // 예외처리
	}
}