#include <iostream>

//Quiz
//namespace를 이용하여 사칙연산 계산기를 만들어 봅니다.
//두 수 a, b 입력을 받습니다.
//계산할 기호 +, -, /, * 입력을 받습니다.
//namespace Calc{} 선언합니다.
//Calc namespace에는 add(+), sub(-), mul(*), div(/) 함수를 만듭니다.
//main도 함수
//입력과 출력은 cin, cout을 사용합니다.
//namespace
//프로그램을 구성하는 요소들을 논리적으로 묶을 수 있도록
//네임스페이스 라는 기능을 제공

//예제 형태
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