#include "singletonBase.h"
#include <time.h>

//==================================
// ## 17.04.28 ## randomFunction ##
//==================================

//template <typename T> singletonBase<T>
class randomFunction : public singletonBase <randomFunction>
{
public:
	randomFunction(void)
	{
		srand(GetTickCount());
	}
	~randomFunction(void) {}

	//0 ~ �����Ѽ���(num) ���̿� ���� �����ϰ� �޾ƿ´�
	inline int getInt(int num) { return rand() % num; }
	//���� ������ ������ ���� �̾Ƴ��� �Լ�(ex 50, 100) 50���� 100����
	inline int getFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }


	//RAND_MAX��� ���� ������ �߻��� �� �ִ� �ִ� ��
	inline float getFloat() { return (float)rand() / (float)RAND_MAX; }
	inline float getFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	inline float getFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}

};