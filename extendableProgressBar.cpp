#include "stdafx.h"
#include "extendableProgressBar.h"


extendableProgressBar::extendableProgressBar()
{
}


extendableProgressBar::~extendableProgressBar()
{

}

HRESULT extendableProgressBar::init(bool isLeft, bool isTrans, COLORREF transColor)
{
	_progressBarTop = IMAGEMANAGER->addImage("frontBar", "hpBarTop.bmp", 53, 5, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage("backBar", "hpBarBottom.bmp", 53, 5, true, RGB(255, 0, 255));

	_x = 0;
	_y = 0;
	_width = _progressBarBottom->getWidth();
	_height = _progressBarBottom->getHeight();
	_ratio = 1.0f;

	_isZeroLeft = isLeft;
	_isTrans = isTrans;
	_transColor = transColor;

	return S_OK;
}

HRESULT extendableProgressBar::init(const char* frontImageName, const char* backImageName, bool isLeft, bool isTrans, COLORREF transColor)
{
	_progressBarTop = IMAGEMANAGER->findImage(frontImageName);
	_progressBarBottom = IMAGEMANAGER->findImage(backImageName);

	_x = 0;
	_y = 0;
	_width = _progressBarBottom->getWidth();
	_height = _progressBarBottom->getHeight();
	_ratio = 1.0f;

	_isZeroLeft = isLeft;
	_isTrans = isTrans;
	_transColor = transColor;

	return S_OK;
}

void extendableProgressBar::release()
{
	_progressBarTop = NULL;
	_progressBarBottom = NULL;

}

//void extendableProgressBar::update()
//{
//	
//}

void extendableProgressBar::update(int x, int y, float width, float height, float currentGauge, float maxGauge)
{
	setRatio(currentGauge, maxGauge);
	setGaugeArea(x, y, width, height);
}

void extendableProgressBar::render()
{
	//SetStretchBltMode(getMemDC(), COLORONCOLOR);
	ExtendBlt(getMemDC(), _x, _y, _width, _height,
		_progressBarBottom->getMemDC(),
		0, 0, _progressBarBottom->getWidth(), _progressBarBottom->getHeight(), _isTrans, _transColor);
	if (_ratio > 0)
	{
		switch (_isZeroLeft)
		{
		case true: // 0이 왼쪽일 때
			ExtendBlt(getMemDC(), _x, _y, _width*_ratio, _height,
				_progressBarTop->getMemDC(),
				0, 0, _progressBarTop->getWidth()*_ratio, _progressBarTop->getHeight(), _isTrans, _transColor);
			break;
		case false: // 0이 오른쪽일 때
			ExtendBlt(getMemDC(), _x + _width, _y, -(_width + 1)*_ratio, _height,
				_progressBarTop->getMemDC(),
				0, 0, _progressBarTop->getWidth()*_ratio, _progressBarTop->getHeight(), _isTrans, _transColor);
			break;
		}
	}
}

void extendableProgressBar::render(int x, int y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	//SetStretchBltMode(getMemDC(), COLORONCOLOR);
	ExtendBlt(getMemDC(), _x, _y, _width, _height,
		_progressBarBottom->getMemDC(),
		0, 0, _progressBarBottom->getWidth(), _progressBarBottom->getHeight(), _isTrans, _transColor);
	if (_ratio > 0)
	{
		switch (_isZeroLeft)
		{
		case true: // 0이 왼쪽일 때
			ExtendBlt(getMemDC(), _x, _y, _width*_ratio, _height,
				_progressBarTop->getMemDC(),
				0, 0, _progressBarTop->getWidth()*_ratio, _progressBarTop->getHeight(), _isTrans, _transColor);
			break;
		case false: // 0이 오른쪽일 때
			ExtendBlt(getMemDC(), _x + _width, _y, -(_width + 1)*_ratio, _height,
				_progressBarTop->getMemDC(),
				0, 0, _progressBarTop->getWidth()*_ratio, _progressBarTop->getHeight(), _isTrans, _transColor);
			break;
		}
	}
}


void extendableProgressBar::setRatio(float currentGauge, float maxGauge)
{
	_ratio = currentGauge / maxGauge;
}

void extendableProgressBar::setGaugeArea(int x, int y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

void extendableProgressBar::ExtendBlt(HDC destDC, int destX, int destY, int destW, int destH, HDC sourDC, int sourX, int sourY, int sourW, int sourH, bool isTrans, COLORREF transColor)
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


