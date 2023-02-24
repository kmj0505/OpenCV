#pragma once
#pragma once
#include "common.h"

class StudentScore3
{
public:
	StudentScore3();
	~StudentScore3();

	//기능
	//입력 학생 이름
	void SetStudentName(string name);
	//과목, 성적입력
	void SetSubjectScore(string subject, int score);
	//결과 산출, sum, avg, min, max
	void DoCalc();

private:
	int GetSum();
	float GetAvg();
	int GetMin();
	int GetMax();

	struct StudentInfo
	{
		string name;
		//int eng, kor, math; //각 과목 성적
		int sum, min, max;
		float avg;
		std::map<string, int> mTable; //map<subject, score>
	};
	StudentInfo stStudentInfo;
	//std::map<string, StudentInfo >mTable;
};
//std::map<string, StudentScore3 >mTable;


