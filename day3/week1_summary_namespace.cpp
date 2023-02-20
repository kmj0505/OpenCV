#include <iostream>


//namespace
//프로그램을 구성하는 요소들을 논리적으로 묶을 수 있도록
//네임스페이스 라는 기능을 제공

namespace text
{
	void draw() { std::cout << "draw text" << std::endl; }
}

namespace graphic
{
	void draw() { std::cout << "draw graphic" << std::endl; }
}

using namespace std;
using namespace text;
using namespace graphic;

//using 선언
namespace calc {
	const double PI = 3.14;
	int add(int a, int b) { return a + b; }
}
using calc::PI;

int main()
{
	//cout << "PI= " << calc::PI << endl;
	cout << "PI= " << PI << endl;
	cout << "namespace example" << endl;
	//text::draw(); 
	//graphic::draw();
	//draw(); -error when using namespace text/graphic
	graphic::draw(); //ok - 명시적 범위지정 연산자 사용
	return 1;


	return 1;
}
