#pragma once
#include "gameNode.h"

class extendableProgressBar : public gameNode
{
private:
	int _x, _y;
	float _width;
	float _height;
	float _ratio;
	bool _isZeroLeft;
	bool _isTrans;
	COLORREF _transColor;

	image* _progressBarTop;
	image* _progressBarBottom;

public:
	HRESULT init(bool isZeroLeft = true, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* frontImageName, const char* backImageName, bool isLeft = true, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	void release();
	//void update();
	void update(int x, int y, float width, float height, float currentGauge, float maxGauge);
	void render();
	void render(int x, int y, float width, float height);

	void setRatio(float currentGauge, float maxGauge);
	void setGaugeArea(int x, int y, float width, float height);
	inline void setZero(bool isLeft){ _isZeroLeft = isLeft; }
	inline void setZeroLeft(){ _isZeroLeft = true; }
	inline void setZeroRight(){ _isZeroLeft = false; }

	void ExtendBlt(HDC destDC, int destX, int destY, int destW, int destH, HDC sourDC, int sourX, int sourY, int sourW, int sourH, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	extendableProgressBar();
	~extendableProgressBar();
};


