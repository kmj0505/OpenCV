#pragma once
#include "common.h"

class StudentScore2
{
public:
	StudentScore2();
	~StudentScore2();

//���
//�Է� �л� �̸�
	int SetStudentName(string name);
//����, �����Է�
	int SetSubjectScore(string subject, int score);
//��� ����, sum, avg, min, max
	int DoCalc();

private:
	int GetSum();
	float GetAvg();
	int GetMin();
	int GetMax();

	struct StudentInfo 
	{
		string name;
		int eng, kor, math; //�� ���� ����
		int sum, min, max;
		float avg;
	};
	StudentInfo studentinfo;
};

