#pragma once
#include "common.h"

class Calc
{
public:
	//������
	Calc(); //Ctor.. default Ctor
	//Calc(int a=1, int b=2, char sym=' ');
	Calc(int a, int b, char sym);
	//�Ҹ���
	~Calc(); //Dtor
	void Clear();
	void SetValue(int num1, int num2, char sym);
	int DoSum();
	int DoMul();
	int DoSub();
	int DoDiv();
	int GetResult();

	int sum(const int* const scores, int length);
	float avg(const int* const scores, int length);
	int min(const int* const scores, int length);
	int max(const int* const scores, int length);

	int number1 = 0;

private:
	int* pData = nullptr;

	//int number1 = 0;
	int number2 = 0;
	char symbol;
	int result;
};


/*usage*/

/*
#include "Cal.h"
int main()
{
	Calc calc;
	calc.SetValue(1,2,'+');
	calc.DoSum();
	cout << "�� ���� ����" << calc.GetResult() << endl;
}
*/
