#pragma once
#include "animation.h"
//================================================
// ## 2017.05.16 ## Image Class ## ����ض� ##
//================================================


class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//From Resource
		LOAD_FILE,			//From File
		LOAD_EMPTY,			//Make Empty BMP file
		LOAD_END		
	};

	typedef struct tagImageInfo
	{
		//DWORD�� ȣȯ�� �ƿ� �Ұ����ϴ� 4Byte �� �� �̻� �� ���ϵ� �ƴ�
		//Long�� 32��Ʈ������ ȣȯ�� ������ 4Byte��
		//int�� 64��Ʈ���� ȣȯ�� ������ 4Byte��
		//�翬�ϰ����� ȣȯ�� �����ϴٸ� �Ҿ��ϱ� ������ ��ǻ�ʹ�
		//ȣȯ�� ���� �ʴ� DWORD�� �����Ѵ�

		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;
		float		y;
		int			width;
		int			height;
		int			currentFrameX;		//������ �̹��� ��ȣ(����)
		int			currentFrameY;		//������ �̹��� ��ȣ(����)
		int			maxFrameX;			//������ �ִ� ����(����)
		int			maxFrameY;			//������ �ִ� ����(����)
		int			frameWidth;			//������ �̹��� ���� ����ũ��
		int			frameHeight;		//������ �̹��� ���� ����ũ��
		BYTE		loadType;

		tagImageInfo()
		{
			resID				= 0;
			hMemDC				= NULL;
			hBit				= NULL;
			hOBit				= NULL;
			x					= 0;
			y					= 0;
			width				= 0;
			height				= 0;
			currentFrameX		= 0;
			currentFrameY		= 0;
			maxFrameX			= 0;
			maxFrameY			= 0;
			frameWidth			= 0;
			frameHeight			= 0;
			loadType = LOAD_RESOURCE;
		}
		//*LPIMAGE_INFO�� �س��� ������ �̹����� ���� ���� �Ҵ��� ���ְ�
		//�ϱ� ����(���ٿ���)
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ���� ����ü
	CHAR*			_fileName;		//�����̸�
	BOOL			_trans;			//Ư��Į�� �������� ����
	COLORREF		_transColor;	//Ư��Į�� ���۷���

	PBLENDFUNCTION	_blendFunc;		//���ĺ��� �Լ�
	LPIMAGE_INFO	_blendImage;	//���ĺ��� �̹���

private:
	// Ŭ���� ���ο� �Լ�
	void ExtendBlt(HDC destDC, int destX, int destY, int destW, int destH, HDC sourDC, int sourX, int sourY, int sourW, int sourH, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

public:
	image();
	~image();

	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT init(int width, int height);
	//���� ��Ʈ�� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	//�̹��� ������
	void release(void);

	//Ư�� Į�� �����ٲ��� ����
	void setTransColor(BOOL trans, COLORREF transColor);

	//���ĺ��带 �Ҳ��� ����
	void setAlphaBlend();
	void releaseAlphaBlend();
	bool isAlpha();

	//���� 
	void render(HDC hdc, int destX, int destY);

	//����               �ѷ��� ��X �ѷ��� ��Y   �ѷ��� ��X �ѷ��� ��Y  sourX,Y�κ��� ũ��(����, ����)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void stretchRender(HDC hdc, int destX, int destY, int destW, int destH, int sourX, int sourY, int sourW, int sourH);

	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void stretchAlphaRender(HDC hdc, int destX, int destY, int destW, int destH, int sourX, int sourY, int sourW, int sourH, BYTE alpha);

	void frameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	


	//DC������ �޸� ������
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//========================================================
	// �̹��� ������ �����ϰ� ���� ����,������
	//========================================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX(void) { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY(void) { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (_imageInfo->maxFrameX < frameX) _imageInfo->maxFrameX = frameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (_imageInfo->maxFrameY < frameY) _imageInfo->maxFrameY = frameY;
	}

	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void){ return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

};

