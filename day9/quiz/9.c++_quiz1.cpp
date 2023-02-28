//Quiz 1. 사용자 이름(string), 나이(int), 주소(string) -> 입력
			//이름 : 이순신
			//나이 : 100
			//주소 : 서울시 ... 12-123

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string name, address;
	int age;

	cout << "이름을 작성하세요 : ";
	cin >> name;
	cout << "나이를 작성하세요 : ";
	cin >> age;
	cout << "주소를 작성하세요 : ";
	cin >> address;
	
	return 0;
}