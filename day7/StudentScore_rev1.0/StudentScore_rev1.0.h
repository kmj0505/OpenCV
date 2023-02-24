#pragma once
#pragma once
#include "common.h"

class StudentScore3
{
public:
	StudentScore3();
	~StudentScore3();

	//���
	//�Է� �л� �̸�
	void SetStudentName(string name);
	//����, �����Է�
	void SetSubjectScore(string subject, int score);
	//��� ����, sum, avg, min, max
	void DoCalc();

private:
	int GetSum();
	float GetAvg();
	int GetMin();
	int GetMax();

	struct StudentInfo
	{
		string name;
		//int eng, kor, math; //�� ���� ����
		int sum, min, max;
		float avg;
		std::map<string, int> mTable; //map<subject, score>
	};
	StudentInfo stStudentInfo;
	//std::map<string, StudentInfo >mTable;
};
//std::map<string, StudentScore3 >mTable;


