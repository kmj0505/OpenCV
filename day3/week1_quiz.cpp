#include <iostream>

//Quiz
//namespace�� �̿��Ͽ� ��Ģ���� ���⸦ ����� ���ϴ�.
//�� �� a, b �Է��� �޽��ϴ�.
//����� ��ȣ +, -, /, * �Է��� �޽��ϴ�.
//namespace Calc{} �����մϴ�.
//Calc namespace���� add(+), sub(-), mul(*), div(/) �Լ��� ����ϴ�.
//main�� �Լ�
//�Է°� ����� cin, cout�� ����մϴ�.
//namespace
//���α׷��� �����ϴ� ��ҵ��� �������� ���� �� �ֵ���
//���ӽ����̽� ��� ����� ����

//���� ����
/*
Calc Program Started
input 1 - 10
input 2 - 20
input symbol - *
result 10 * 20 = 200
*/

namespace Calc
{
	int a, b, resVal;  //int a = 0, b = 0, resVal = 0;
	char symbol = ' ';


	int add(int a, int b) { return a + b; }//temp_obj = a+b;
	int sub(int a, int b) { return a - b; }
	int mul(int a, int b) { return a * b; }
	int div(int a, int b) { return a / b; }

	int result()
	{
		if (symbol == '+') resVal = add(a, b);
		else if (symbol == '-') resVal = sub(a, b);
		else if (symbol == '*') resVal = mul(a, b);
		else if (symbol == '/') resVal = div(a, b);

		return resVal;
	}
}
//using namespace Calc;

int main() {

	std::cout << "Calc Program Started" << std::endl;
	std::cout << "input1 - ";
	std::cin >> Calc::a;
	std::cout << "input2 - ";
	std::cin >> Calc::b;
	std::cout << "input symbol - ";
	std::cin >> Calc::symbol;
	std::cout << "result ";
	std::cout << Calc::a;
	std::cout << Calc::symbol;
	std::cout << Calc::b;
	std::cout << " = ";
	std::cout << Calc::result();


}