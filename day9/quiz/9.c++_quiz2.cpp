//Quiz 2. 동적메모리 할당(int* ), 크기(int, 10), 
	//		원소값({1,2,3,4,5,6,7,8,9,10})인 배열의
	//		합/최소/최대를 출력하시오.
	//		합 : ?
	//		최소 : ?
	//		최대 : ?

#include <iostream>
#include <string>

using namespace std;
int sum(int* pData, int length)
{
	int _sum = 0;
	for (size_t i = 0; i < length; i++)
	{
		_sum += pData[i];
	}
	return _sum;
}

int min(int* pData, int length)
{
	int _min = pData[0];
	for (size_t i = 0; i < length; i++)
	{
		if (_min > pData[i])
		{
			_min = pData[i];
		}
	}
	return _min;
}

int max(int* pData, int length)
{
	int _max = pData[0];
	for (size_t i = 0; i < length; i++)
	{
		if (_max < pData[i])
		{
			_max = pData[i];
		}
	}
	return _max;
}

int main()
{
	int* pData = new int[10] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int length = 10;
	cout << "합 : " << sum(pData, length) << endl;
	cout << "최소 : " << min(pData, length) << endl;
	cout << "최대 : " << max(pData, length) << endl;

	return 0;
}