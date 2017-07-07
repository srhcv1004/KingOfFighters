#include "stdafx.h"
#include "image.h"

//�����ߴ� �и���
#pragma comment(lib, "msimg32.lib")


image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0)),
	_blendFunc(NULL),
	_blendImage(NULL)
{
}


image::~image()
{
}

//�� ��Ʈ�� �ʱ�ȭ
HRESULT image::init(int width, int height)
{
	//�̹��� ������ ���� �ִٸ� �������ش�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);


	//�ʱ�ȭ�� �ȵǾ���
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);


	return S_OK;
}

//���� ��Ʈ�� �ʱ�ȭ
HRESULT image::init(const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor)
{
	//�����̸� ������ ����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ ���� �ִٸ� �������ش�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� ���̸� �˾ƿ´�(���ϰ��)
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;


	//�ʱ�ȭ�� �ȵǾ���
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);


	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor)
{
	//�����̸� ������ ����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ ���� �ִٸ� �������ش�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� ���̸� �˾ƿ´�(���ϰ��)
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;


	//�ʱ�ȭ�� �ȵǾ���
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�����̸� ������ ����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ ���� �ִٸ� �������ش�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//���� ���̸� �˾ƿ´�(���ϰ��)
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	
	//�ʱ�ȭ�� �ȵǾ���
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�����̸� ������ ����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ ���� �ִٸ� �������ش�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//���� ���̸� �˾ƿ´�(���ϰ��)
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;


	//�ʱ�ȭ�� �ȵǾ���
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//�̹��� ������
void image::release(void)
{
	//�̹��� ������ �ִٸ�
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_blendImage);
		SAFE_DELETE(_blendFunc);
	}
}

//Ư�� Į�� �����ٲ��� ����
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::setAlphaBlend()
{
	if (_blendImage == NULL)
	{
		HDC hdc = GetDC(_hWnd);

		_blendFunc = new BLENDFUNCTION;
		_blendFunc->BlendFlags = 0;
		_blendFunc->AlphaFormat = 0;
		_blendFunc->BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;

		ReleaseDC(_hWnd, hdc);
	}
}

void image::releaseAlphaBlend()
{
	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_blendImage);
		SAFE_DELETE(_blendFunc);
	}
}

bool image::isAlpha()
{
	if (_blendImage == NULL) return false;
	else return true;
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,		//����� ������ DC		== backDC
			destX,					//����� ��ǥ X(left		== backDC�� ������ ��ǥ
			destY,					//����� ��ǥ Y(top		== backDC�� ������ ��ǥ
			_imageInfo->width,		//����� ũ�� width		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->height,		//����� ũ�� height		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->hMemDC,		//������ DC				== �̹���DC
			0, 0,					//������ X, Y			== �̹���DC�� ��ǥ
			_imageInfo->width,		//������ width			== �̹���DC�� ����ũ��
			_imageInfo->height,		//������ height			== �̹���DC�� ����ũ��
			_transColor);			//���翡�� ������ ����	== �̹���DC���� �ȼ���
	}
	else
	{
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		BitBlt(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::stretchRender(HDC hdc, int destX, int destY, int destW, int destH, int sourX, int sourY, int sourW, int sourH)
{
	ExtendBlt(hdc, destX, destY, destW, destH, _imageInfo->hMemDC, sourX, sourY, sourW, sourH, _trans, _transColor);
}

//                          �ѷ��� �� X, Y, sourX,Y ������ ��
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,		//����� ������ DC		== backDC
			destX,					//����� ��ǥ X(left		== backDC�� ������ ��ǥ
			destY,					//����� ��ǥ Y(top		== backDC�� ������ ��ǥ
			sourWidth,				//����� ũ�� width		== backDC�� ������ ��ǥ�κ��� ����ũ��
			sourHeight,				//����� ũ�� height		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->hMemDC,		//������ DC				== �̹���DC
			sourX, sourY,			//������ X, Y			== �̹���DC�� ��ǥ
			sourWidth,				//������ width			== �̹���DC�� ����ũ��
			sourHeight,				//������ height			== �̹���DC�� ����ũ��
			_transColor);			//���翡�� ������ ����	== �̹���DC���� �ȼ���
	}
	else
	{
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,										//����� ������ DC		== backDC
			destX,													//����� ��ǥ X(left		== backDC�� ������ ��ǥ
			destY,													//����� ��ǥ Y(top		== backDC�� ������ ��ǥ
			_imageInfo->frameWidth,									//����� ũ�� width		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->frameHeight,								//����� ũ�� height		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->hMemDC,										//������ DC				== �̹���DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,										//������ X, Y			== �̹���DC�� ��ǥ
			_imageInfo->frameWidth,									//������ width			== �̹���DC�� ����ũ��
			_imageInfo->frameHeight,								//������ height			== �̹���DC�� ����ũ��
			_transColor);											//���翡�� ������ ����	== �̹���DC���� �ȼ���
	}
	else
	{
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth, 
			_imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY *_imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(hdc,										//����� ������ DC		== backDC
			destX,													//����� ��ǥ X(left		== backDC�� ������ ��ǥ
			destY,													//����� ��ǥ Y(top		== backDC�� ������ ��ǥ
			_imageInfo->frameWidth,									//����� ũ�� width		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->frameHeight,								//����� ũ�� height		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->hMemDC,										//������ DC				== �̹���DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,										//������ X, Y			== �̹���DC�� ��ǥ
			_imageInfo->frameWidth,									//������ width			== �̹���DC�� ����ũ��
			_imageInfo->frameHeight,								//������ height			== �̹���DC�� ����ũ��
			_transColor);											//���翡�� ������ ����	== �̹���DC���� �ȼ���
	}
	else
	{
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY *_imageInfo->frameHeight, SRCCOPY);
	}
}

//�̹��� �� ������ �������� ��������
void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	//ȭ�� ������ ������ �������ش�
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	RECT rcSour;
	int sourWidth;
	int sourHeight;

	RECT rcDest;

	//�׷��ִ� ������ ����ش�
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//Y�����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//�׷����� ������ ���̺��� Y���� ũ��
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�ѷ��ִ� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//X ��
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left,
				rcDest.top,
				rcSour.left,
				rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}


void image::alphaRender(HDC hdc, BYTE alpha)
{
	setAlphaBlend();

	_blendFunc->SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, (int)_imageInfo->x, (int)_imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, *_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, *_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	setAlphaBlend();

	_blendFunc->SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, *_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, *_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	setAlphaBlend();

	_blendFunc->SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, *_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, *_blendFunc);
	}

}

void image::stretchAlphaRender(HDC hdc, int destX, int destY, int destW, int destH, int sourX, int sourY, int sourW, int sourH, BYTE alpha)
{
	setAlphaBlend();

	_blendFunc->SourceConstantAlpha = alpha;

	BitBlt(_blendImage->hMemDC, 0, 0, destW, destH, hdc, destX, destY,SRCCOPY);
	ExtendBlt(_blendImage->hMemDC, destX, destY, destW, destH, _imageInfo->hMemDC, sourX, sourY, sourW, sourH, _trans, _transColor);
	AlphaBlend(hdc, destX, destY, destW, destH,
		_blendImage->hMemDC, 0, 0, destW, destH, *_blendFunc);
}

void image::frameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	setAlphaBlend();

	_blendFunc->SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);
		GdiTransparentBlt(_blendImage->hMemDC,										//����� ������ DC		== backDC
			0,													//����� ��ǥ X(left		== backDC�� ������ ��ǥ
			0,													//����� ��ǥ Y(top		== backDC�� ������ ��ǥ
			_imageInfo->frameWidth,									//����� ũ�� width		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->frameHeight,								//����� ũ�� height		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->hMemDC,										//������ DC				== �̹���DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,										//������ X, Y			== �̹���DC�� ��ǥ
			_imageInfo->frameWidth,									//������ width			== �̹���DC�� ����ũ��
			_imageInfo->frameHeight,								//������ height			== �̹���DC�� ����ũ��
			_transColor);											//���翡�� ������ ����	== �̹���DC���� �ȼ���

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, *_blendFunc);
	}
	else
	{
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		AlphaBlend(hdc, destX, destY, 
			_imageInfo->frameWidth, 
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY *_imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, *_blendFunc);
	}
}
void image::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{

	setAlphaBlend();

	_blendFunc->SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);
		GdiTransparentBlt(_blendImage->hMemDC,										//����� ������ DC		== backDC
			0,													//����� ��ǥ X(left		== backDC�� ������ ��ǥ
			0,													//����� ��ǥ Y(top		== backDC�� ������ ��ǥ
			_imageInfo->frameWidth,									//����� ũ�� width		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->frameHeight,								//����� ũ�� height		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->hMemDC,										//������ DC				== �̹���DC
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,										//������ X, Y			== �̹���DC�� ��ǥ
			_imageInfo->frameWidth,									//������ width			== �̹���DC�� ����ũ��
			_imageInfo->frameHeight,								//������ height			== �̹���DC�� ����ũ��
			_transColor);											//���翡�� ������ ����	== �̹���DC���� �ȼ���

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, *_blendFunc);
	}
	else
	{
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY *_imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, *_blendFunc);
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha)
{
	//ȭ�� ������ ������ �������ش�
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	RECT rcSour;
	int sourWidth;
	int sourHeight;

	RECT rcDest;

	//�׷��ִ� ������ ����ش�
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//Y�����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//�׷����� ������ ���̺��� Y���� ũ��
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�ѷ��ִ� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//X ��
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			alphaRender(hdc, rcDest.left,
				rcDest.top,
				rcSour.left,
				rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top,
				alpha);
		}
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::ExtendBlt(HDC destDC, int destX, int destY, int destW, int destH, HDC sourDC, int sourX, int sourY, int sourW, int sourH, bool isTrans, COLORREF transColor)
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
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		SetStretchBltMode(destDC, COLORONCOLOR);
		StretchBlt(destDC, destX, destY, destW, destH,
			sourDC, sourX, sourY, sourW, sourH, SRCCOPY);
	}
}
