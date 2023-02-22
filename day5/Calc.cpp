#include "Calc.h"

//Calc::Calc()
//	:number1(0) //member inintilizer
//	,number2(0)
//	,symbol(' ')
//	,result(0)
//{
//	cout << "Calc::Ctor" << endl;
//}

Calc::Calc()
	: Calc(1, 1, ' ') // 위임생성자
{
	cout << "Calc::Ctor1" << endl;
}

Calc::Calc(int a, int b, char sym)
	:number1(0) //member inintilizer
	,number2(0)
	,symbol(' ')
	,result(0)
{
	cout << "Calc::Ctor" << endl;
}

Calc::~Calc()
{
	cout << "Calc::Dtor" << endl;
}

void Calc::Clear()
{
	number1 = 0; //member inintilizer
	number2 = 0;
	symbol = ' ';
	result = 0;
}

void Calc::SetValue(int num1, int num2, char sym)
{
	number1 = num1;
	number2 = num2;
	symbol = sym;
}

int Calc::DoSum()
{
	result = number1 + number2;
	return result;
}

int Calc::DoMul()
{
	result = number1 * number2;
	return result;
}

int Calc::DoSub()
{
	result = number1 - number2;
	return result;
}

int Calc::DoDiv()
{
	result = number1 / number2;
	return result;
}

int Calc::GetResult()
{
	return result;
}
int Calc::sum(const int* const scores, int length)
{
	int sum = 0;
	for (size_t i = 0; i < length; i++)
	{
		sum += scores[i];
	}
	result = sum;
	return result;
}

float Calc::avg(const int* const scores, int length)
{
	int sum = 0;
	float avg = 0;
	for (size_t i = 0; i < length; i++)
	{
		sum += scores[i];
		avg = (float)sum / length;
	}
	result = avg;
	return result;
}

int Calc::min(const int* const scores, int length)
{
	int min = scores[0];
	for (size_t i = 0; i < length; i++)
	{
		if (min > scores[i])
		{
			min = scores[i];
		}
	}
	result = min;
	return result;
}

int Calc::max(const int* const scores, int length)
{
	int max = scores[0];
	for (size_t i = 0; i < length; i++)
	{
		if (max < scores[i])
		{
			max = scores[i];
		}
	}
	result = max;
	return result;
}