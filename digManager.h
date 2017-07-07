#pragma once
#include "singletonBase.h"

class digManager : public singletonBase < digManager >
{
private:
	COLORREF _transColor;
	
	HBRUSH _hBrushTrans, _hBrushOld;
	HPEN _hPenTrans, _hPenOld;

	int _x[500];
	int _y[500];
	bool _rememberLine[500];
	int _count;
	int _countMax;
	float _radiusMax;
	float _radius[500];
	float _range;
	int _bulletMount;
	bool _isInProcess;


public:
	digManager();
	~digManager();

	HRESULT init();
	void release();

	bool digCircle(HDC destDC, int x, int y, float radius, COLORREF transColor = RGB(255,0,255), unsigned time = 1);
	bool digNapalm(HDC destDC, int x, int y, float range, float radius, int bulletMount = 100, COLORREF transColor = RGB(255, 0, 255), unsigned int time = 20);
};