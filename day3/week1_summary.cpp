
#include <stdio.h>
#include <iostream>   //표준 입출력 input, output 사용

//#define _CRT_SECURE_NO_WARNINGS

//istream vs ostream
//cin ">>"  cout "<<"

//#include "abc.h" user defined header file
//함수 형태
//[반환형] [함수명] [(매개변수)] {  } 
int main()
{
	//출력
	printf("Hello");
	printf("World\n");
	std::cout << "Hello, ";
	std::cout << "World\n";
	std::cout << "Hello, World\r\n" << std::endl;

	//정수
	printf("math - %d\n", 100);
	std::cout << "math - " << 100 << std::endl;
	
	//소수
	printf("pi - %lf\n", 3.14);
	std::cout << "pi - " << 3.14 << std::endl;
	
	//문자
	printf("Score - %c\n", 'A');
	std::cout << "Score - " << 'A' << std::endl;

	printf("%d %lf %c\n", 100, 3.14, 'A');

	//입력
	//C
	int i = 0;
	scanf("input-%d\n", &i);  //★★★ 입력받는 값의 자료형을 지정해줬다
	printf("%d typed\n", i);

	//C++ (원하는 자리에 >> 또는 <<로 표시해서 입력할 수 있다
	std::cout << "input - ";
	std::cin >> i; //★★★ 입력받는 값
	std::cout << i << std::endl;

	return 1; //True = -1, False = 0;
 }