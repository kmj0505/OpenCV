#include<iostream>
#include<stdio.h>
#include<string>

using namespace std;

enum
{
	eEnglish, //0 
	eMath,  //eMath = 5, 1 -> 5
	eKorean,  //2 -> 6 
	eClassMax  //6 -> 7
} ECLASS;

struct _stStudentInfo
{
	std::string name;
	//int eng, math, kor;
	int scores[eClassMax];
	int sum, min, max;
	float average;
};

int sum(const int* const scores, int length)
{
	int sum = 0;
	for (size_t i = 0; i < length; i++)
	{
		sum += scores[i];
	}
	return sum;
}

float avg(const int* const scores, int length)
{
	int sum = 0;
	float avg = 0;
	for (size_t i = 0; i < length; i++)
	{
		sum += scores[i];
		avg = (float)sum / length;
	}
	return avg;
}

int min(const int* const scores, int length)
{
	int min = scores[eEnglish];
	for (size_t i = 0; i < length; i++)
	{
		if (min > scores[i])
		{
			min = scores[i];
		}
	}
	return min;
}

int max(const int* const scores, int length)
{
	int max = scores[eEnglish];
	for (size_t i = 0; i < length; i++)
	{
		if (max < scores[i])
		{
			max = scores[i];
		}
	}
	return max;
}

int main()
{
	_stStudentInfo student;
	student.name = "ȫ�浿";
	student.scores[eEnglish] = 90;
	student.scores[eMath] = 95;
	student.scores[eKorean] = 92;

	//1��
	//�Լ� sum, average, min, max
	//input scores[], length
	//return sum(int), average(float), min/max(int)

	//display
	//[�̸�]
	//english - ??
	//math - ??
	//korean - ??
	//sum - ??, average - ??, min - ??, max -??
	cout << "name : " << student.name << endl;
	cout << "English : " << student.scores[eEnglish] << endl;
	cout << "Math : " << student.scores[eMath] << endl;
	cout << "Korean : " << student.scores[eKorean] << endl;
	cout << "data sum = " << sum(student.scores, eClassMax) << endl;
	cout << "data avg = " << avg(student.scores, eClassMax) << endl;
	cout << "data min = " << min(student.scores, eClassMax) << endl;
	cout << "data max = " << max(student.scores, eClassMax) << endl;


	//2�� - �ڵ����� �Է� �� ���� ���� ���
	//����ڷκ��� �Է��� �޽��ϴ�.
	//struct�� string name�� �Է¹޴´�
	//�� eng, math, kor ������ �Է¹޴´�
	//�� display�� ����Ѵ�
	//Q�Է��� ������ �� �̻� �Է��� ���� �ʴ´�.
	while (true)
	{
		cin >> student.name;
		if (student.name == "Q")
		{
			cout << "quit";
			break;
		}
		cin >> student.scores[eEnglish];
		cin >> student.scores[eMath];
		cin >> student.scores[eKorean];
		cout << "name : " << student.name << endl;
		cout << "English : " << student.scores[eEnglish] << endl;
		cout << "Math : " << student.scores[eMath] << endl;
		cout << "Korean : " << student.scores[eKorean] << endl;
		cout << "data sum = " << sum(student.scores, eClassMax) << endl;
		cout << "data avg = " << avg(student.scores, eClassMax) << endl;
		cout << "data min = " << min(student.scores, eClassMax) << endl;
		cout << "data max = " << max(student.scores, eClassMax) << endl;
	}
}