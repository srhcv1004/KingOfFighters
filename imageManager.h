#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
private:
	//          first  second
	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:
	HRESULT init();
	void release();

	//빈 비트맵 이미지
	image* addImage(string strKey, int width, int height);

	//파일 이미지
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);

	//프레임 이미지
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	image* findImage(string strKey);

	BOOL deleteImage(string strKey);

	BOOL deleteAll(void);

	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);


	imageManager();
	~imageManager();
};

