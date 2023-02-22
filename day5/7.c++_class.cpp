#include "Calc.h"


int main()
{
	
	/*calc.SetValue(1, 2, '+');
	calc.DoSum();
	cout << "두 수의 합은" << calc.GetResult() << endl;
	calc.DoMul();
	cout << "두 수의 곱은" << calc.GetResult() << endl;
	calc.DoSub();
	cout << "두 수의 뺄셈은" << calc.GetResult() << endl;
	calc.DoDiv();
	cout << "두 수의 나눗셈은" << calc.GetResult() << endl;*/
	if(true)
	{
		Calc calc;
		calc.Clear();
		int data[3] = { 1, 2, 3 };
		calc.sum(data, 3);
		cout << "data 합은" << calc.GetResult() << endl;
		calc.Clear();
		calc.SetValue(1, 2, '+');
		calc.DoSum();
		cout << "합은 " << calc.GetResult() << endl;

	}
	
	if(false)
	{
		Calc* pCalc = new Calc();
		int data[3] = { 1, 2, 3 };
		pCalc->sum(data, 3);
		cout << "data 합은" << pCalc->GetResult() << endl;
		pCalc->Clear();
		pCalc->SetValue(1, 2, '+');
		pCalc->DoSum();
		cout << "합은 " << pCalc->GetResult() << endl;

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
		cout << "data 합은" << pCalc->GetResult() << endl;
		pCalc->Clear();
		pCalc->SetValue(1, 2, '+');
		pCalc->DoSum();
		cout << "합은 " << pCalc->GetResult() << endl;

	}
		return 1;
}