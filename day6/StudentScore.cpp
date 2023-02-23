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
			stStudentInfo.score[i] = score;  //score 값 구조체에 저장
			break;
		}
	}
	return 0;
}

int StudentScore::DoCalc()
{
	cout << "합: " << GetSum(stStudentInfo.score, 6)<< endl;    //GetSum함수에서 구한 합계 출력
	cout << "평균: " << GetAvg(stStudentInfo.score, 6) << endl; //GetAvg함수에서 구한 평균 출력
	cout << "최소: " << GetMin(stStudentInfo.score, 6) << endl; //GetMin함수에서 구한 최소값 출력
	cout << "최대: " << GetMax(stStudentInfo.score, 6) << endl; //GetMax함수에서 구한 최대값 출력

	return 0;
}

int StudentScore::GetSum(int score[], int scoreCnt)  //합 구하기
{
	int sum = 0;
	for (size_t i = 0; i < scoreCnt; i++)
	{
		sum += stStudentInfo.score[i];
	}
	stStudentInfo.sum = sum;
	return stStudentInfo.sum;
}

int StudentScore::GetAvg(int score[], int scoreCnt)  //평균 구하기
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

int StudentScore::GetMin(int score[], int scoreCnt)  //최소값 구하기
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

int StudentScore::GetMax(int score[], int scoreCnt)  //최대값 구하기
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
