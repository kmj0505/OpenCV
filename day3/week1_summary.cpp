
#include <stdio.h>
#include <iostream>   //ǥ�� ����� input, output ���

//#define _CRT_SECURE_NO_WARNINGS

//istream vs ostream
//cin ">>"  cout "<<"

//#include "abc.h" user defined header file
//�Լ� ����
//[��ȯ��] [�Լ���] [(�Ű�����)] {  } 
int main()
{
	//���
	printf("Hello");
	printf("World\n");
	std::cout << "Hello, ";
	std::cout << "World\n";
	std::cout << "Hello, World\r\n" << std::endl;

	//����
	printf("math - %d\n", 100);
	std::cout << "math - " << 100 << std::endl;
	
	//�Ҽ�
	printf("pi - %lf\n", 3.14);
	std::cout << "pi - " << 3.14 << std::endl;
	
	//����
	printf("Score - %c\n", 'A');
	std::cout << "Score - " << 'A' << std::endl;

	printf("%d %lf %c\n", 100, 3.14, 'A');

	//�Է�
	//C
	int i = 0;
	scanf("input-%d\n", &i);  //�ڡڡ� �Է¹޴� ���� �ڷ����� ���������
	printf("%d typed\n", i);

	//C++ (���ϴ� �ڸ��� >> �Ǵ� <<�� ǥ���ؼ� �Է��� �� �ִ�
	std::cout << "input - ";
	std::cin >> i; //�ڡڡ� �Է¹޴� ��
	std::cout << i << std::endl;

	return 1; //True = -1, False = 0;
 }