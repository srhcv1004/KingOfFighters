#include "stdafx.h"
#include "digManager.h"

digManager::digManager(){}
digManager::~digManager(){}

HRESULT digManager::init(){ _count = 0; _isInProcess = false; return S_OK; }
void digManager::release(){ _count = 0; _isInProcess = false; }

bool digManager::digCircle(HDC destDC, int x, int y, float radius, COLORREF transColor, unsigned int time)
{
	if (!_isInProcess)
	{
		_isInProcess = true;
		_count = 0;
		_x[0] = x;
		_y[0] = y;
		_radiusMax = radius;
		_transColor = transColor;
		_countMax = time;
	}
	++_count;
	
	_hBrushTrans = CreateSolidBrush(_transColor);
	_hPenTrans = CreatePen(PS_SOLID, 0, _transColor);
	_hBrushOld = (HBRUSH)SelectObject(destDC, _hBrushTrans);
	_hPenOld = (HPEN)SelectObject(destDC, _hPenTrans);

	_radius[0] = _radiusMax / _countMax * _count;
	Ellipse(destDC, _x[0] - _radius[0], _y[0] - _radius[0], _x[0] + _radius[0], _y[0] + _radius[0]);

	SelectObject(destDC, _hBrushOld);
	SelectObject(destDC, _hPenOld);
	DeleteObject(_hBrushTrans);
	DeleteObject(_hPenTrans);

	if (_count >= _countMax) _isInProcess = false;

	return _isInProcess;
}
bool digManager::digNapalm(HDC destDC, int x, int y, float range, float radius, int bulletMount, COLORREF transColor, unsigned time)
{
	if (!_isInProcess)
	{
		_isInProcess = true;
		_count = 0;
		_bulletMount = bulletMount;
		_radiusMax = radius;
		_transColor = transColor;
		_countMax = time;
		_range = range;

		for (int i = 0; i < _bulletMount; i++)
		{
			
			_radius[i] = _radiusMax;
			_x[i] = x - (range - 2 * radius) / 2 + i*(range - 2 * radius) / _bulletMount;
			//_y[i] = y;
			for (int j = y - 30; j < y + 1000; ++j)
			{
				COLORREF color = GetPixel(destDC, _x[i], j);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if (!(r == 255 && g == 0 && b == 255))
				{
					if (j == y - 30)
					{
						COLORREF color2 = GetPixel(destDC, _x[i], j - 1);
						int r2 = GetRValue(color2);
						int g2 = GetGValue(color2);
						int b2 = GetBValue(color2);
						if (!(r2 == 255 && g2 == 0 && b2 == 255))
						{
							_rememberLine[i] = false;
							break;
						}
					}
					_y[i] = j;
					_rememberLine[i] = true;
					break;
				}
				else _rememberLine[i] = false;
			}
		}
	}
	++_count;
	_hBrushTrans = CreateSolidBrush(_transColor);
	_hPenTrans = CreatePen(PS_SOLID, 0, _transColor);
	_hBrushOld = (HBRUSH)SelectObject(destDC, _hBrushTrans);
	_hPenOld = (HPEN)SelectObject(destDC, _hPenTrans);

	for (int i = 0; i < _bulletMount; ++i)
	{
		if (!_rememberLine[i]) continue;
		/*SetPixel(IMAGEMANAGER->findImage("¾ð´ö")->getMemDC(),
		x - 50 + j, y + i, RGB(255, 0, 255));*/
		EllipseMakeCenter(destDC, _x[i], _y[i], _radius[i]*2, _radius[i]*2);
		_y[i] += _radius[i];
		if (RND->getFromIntTo(1, 100) < 75)
		{
			_radius[i] = sqrt(_radius[i]);
		}
		else
		{
			_radius[i] -= 1;
		}
		if (_radius[i] <= 1.1f)
		{
			_rememberLine[i] = false;
		}
	}

	SelectObject(destDC, _hBrushOld);
	SelectObject(destDC, _hPenOld);
	DeleteObject(_hBrushTrans);
	DeleteObject(_hPenTrans);

	if (_count >= _countMax) _isInProcess = false;

	return _isInProcess;
}