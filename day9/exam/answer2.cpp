#include <iostream>
#include <string>

using namespace std;
double sum(const double* const pData, int length)
{
	double _sum = 0.0;
	for (size_t i = 0; i < length; i++)
	{
		_sum += pData[i];
	}
	return _sum;
}
int main()
{
	double* pData = new double[20]();
	//{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	for (int i = 0; i < 20; i++)
	{
		pData[i] = i + 1;
	}
	cout << "¹è¿­ÀÇ ÃÑÇÕ : " << sum(pData, 20);
	if (pData != nullptr)
	{
		delete [] pData;
		pData = nullptr;
	}
	return 1;
}