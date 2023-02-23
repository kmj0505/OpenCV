#pragma once
#include "common.h"

static string arr_subject[] = {"����", "����", "����", "�̼�", "����", "����"}; //�� ������ �� �迭 arr_subject[] ����

struct _stStudentInfo
{
	string name; 
	int score[6]; //�迭�� ũ�Ⱑ 6�� score[] ����
	int sum, min, max;
	float avg;
};
class StudentScore
{
public:
	StudentScore();
	~StudentScore();
	int SetStudentName(string name); //�л� �̸�
	int SetSubjectScore(string subject, int score); //����, �����Է�(���񸶴�)
	int DoCalc();  //ȣ���� �Լ�

private:
	_stStudentInfo stStudentInfo;
	int GetSum(int score[], int scoreCnt); //���� ����
	int GetAvg(int score[], int scoreCnt); //���� ���
	int GetMin(int score[], int scoreCnt); //���� �ּ�
	int GetMax(int score[], int scoreCnt); //���� �ִ�
};



