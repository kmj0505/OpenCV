#include "StudentScore.h"


StudentScore::StudentScore()
{
	cout << "StudentScore::Ctor" << endl;
}

StudentScore::~StudentScore()
{
	cout << "StudentScore::Dtor" << endl;
}

int StudentScore::SetStudentName(string name)
{
	stStudentInfo.name = name;

	return 0;
}

int StudentScore::SetSubjectScore(string subject, int score)
{
	for (int i = 0; i < 6; i++)
	{
		if (arr_subject[i] == subject) 
		{
			stStudentInfo.score[i] = score;  //score �� ����ü�� ����
			break;
		}
	}
	return 0;
}

int StudentScore::DoCalc()
{
	cout << "��: " << GetSum(stStudentInfo.score, 6)<< endl;    //GetSum�Լ����� ���� �հ� ���
	cout << "���: " << GetAvg(stStudentInfo.score, 6) << endl; //GetAvg�Լ����� ���� ��� ���
	cout << "�ּ�: " << GetMin(stStudentInfo.score, 6) << endl; //GetMin�Լ����� ���� �ּҰ� ���
	cout << "�ִ�: " << GetMax(stStudentInfo.score, 6) << endl; //GetMax�Լ����� ���� �ִ밪 ���

	return 0;
}

int StudentScore::GetSum(int score[], int scoreCnt)  //�� ���ϱ�
{
	int sum = 0;
	for (size_t i = 0; i < scoreCnt; i++)
	{
		sum += stStudentInfo.score[i];
	}
	stStudentInfo.sum = sum;
	return stStudentInfo.sum;
}

int StudentScore::GetAvg(int score[], int scoreCnt)  //��� ���ϱ�
{
	int sum = 0;
	float avg = 0;
	for (size_t i = 0; i < scoreCnt; i++)
	{
		sum += stStudentInfo.score[i];
		avg = (float)sum / scoreCnt;
	}
	stStudentInfo.avg = avg;
	return stStudentInfo.avg;
}

int StudentScore::GetMin(int score[], int scoreCnt)  //�ּҰ� ���ϱ�
{
	int min = stStudentInfo.score[0];
	for (size_t i = 0; i < scoreCnt; i++)
	{
		if (min > stStudentInfo.score[i])
		{
			min = stStudentInfo.score[i];
		}
	}
	stStudentInfo.min = min;
	return stStudentInfo.min;
}

int StudentScore::GetMax(int score[], int scoreCnt)  //�ִ밪 ���ϱ�
{
	int max = stStudentInfo.score[0];
	for (size_t i = 0; i < scoreCnt; i++)
	{
		if (max < stStudentInfo.score[i])
		{
			max = stStudentInfo.score[i];
		}
	}
	stStudentInfo.max = max;
	return stStudentInfo.max;
}
