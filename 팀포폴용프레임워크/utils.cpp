#include "stdafx.h"
#include "utils.h"


//���ӽ����̽��� �����صθ� �������� ���ϰ� �����ִ�
namespace THETA_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf((x * x) + (y * y));

		float angle = acosf(x / distance);

		//Y���� ������ �ʿ��ϴ�
		if (y2 > y1)
		{
			angle = PI * 2 - angle;
			if (angle >= PI * 2) angle -= PI * 2;
		}

		return angle;
	}
}