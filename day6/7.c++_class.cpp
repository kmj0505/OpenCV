#include "Calc.h"

//���嵥���� Ÿ��
//int
//array[]
//struct
Calc calc_global; //����, global //���α׷� ����/���� �� Calc ����/�Ҹ�
//����
int main()
{
	{
		Calc calc_local; //����, local
		//�Լ�/Logic �� ����{} ����/���� �� Calc ����/�Ҹ�
		//���嵥����Ÿ��
		//int
		//array[]
		//struct
		//����
	}

	{
		Calc* pCalc = new Calc(); //����, dynamic memory allocation
		//int* pData = new int[100]
		//new ����
		
		//logic
		//exception
		//return;
		try
		{

		}
		catch (const std::exception&)
		{

		}

		if (pCalc != nullptr)
		{
			delete pCalc;
			pCalc = nullptr;
		}
		//if(pData != nullptr)
		//{delete[] pData; pData = nullptr};
	}

	/*calc.SetValue(1, 2, '+');
	calc.DoSum();
	cout << "�� ���� ����" << calc.GetResult() << endl;
	calc.DoMul();
	cout << "�� ���� ����" << calc.GetResult() << endl;
	calc.DoSub();
	cout << "�� ���� ������" << calc.GetResult() << endl;
	calc.DoDiv();
	cout << "�� ���� ��������" << calc.GetResult() << endl;*/
	if(true)
	{
		Calc calc;
		calc.Clear();
		int data[3] = { 1, 2, 3 };
		calc.sum(data, 3);
		cout << "data ����" << calc.GetResult() << endl;
		calc.Clear();
		calc.SetValue(1, 2, '+');
		calc.DoSum();
		cout << "���� " << calc.GetResult() << endl;

	}
	
	if(false)
	{
		Calc* pCalc = new Calc();
		int data[3] = { 1, 2, 3 };
		pCalc->sum(data, 3);
		cout << "data ����" << pCalc->GetResult() << endl;
		pCalc->Clear();
		pCalc->SetValue(1, 2, '+');
		pCalc->DoSum();
		cout << "���� " << pCalc->GetResult() << endl;

		if (pCalc != nullptr)
		{
			delete pCalc;
			pCalc = nullptr;
		}
	}
	
	{
		//smart pointer
		//Calc* pCalc = new Calc();
		std::shared_ptr<Calc> pCalc = std::make_shared<Calc>(1, 1, '+');
		int data[3] = { 1, 2, 3 };
		pCalc->sum(data, 3);
		cout << "data ����" << pCalc->GetResult() << endl;
		pCalc->Clear();
		pCalc->SetValue(1, 2, '+');
		pCalc->DoSum();
		cout << "���� " << pCalc->GetResult() << endl;

	}
		return 1;
}