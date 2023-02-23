#pragma once
#include "common.h"

static string arr_subject[] = {"국어", "영어", "수학", "미술", "음악", "역사"}; //각 과목이 들어간 배열 arr_subject[] 선언

struct _stStudentInfo
{
	string name; 
	int score[6]; //배열의 크기가 6인 score[] 선언
	int sum, min, max;
	float avg;
};
class StudentScore
{
public:
	StudentScore();
	~StudentScore();
	int SetStudentName(string name); //학생 이름
	int SetSubjectScore(string subject, int score); //과목, 성적입력(과목마다)
	int DoCalc();  //호출할 함수

private:
	_stStudentInfo stStudentInfo;
	int GetSum(int score[], int scoreCnt); //과목 총합
	int GetAvg(int score[], int scoreCnt); //과목 평균
	int GetMin(int score[], int scoreCnt); //과목 최소
	int GetMax(int score[], int scoreCnt); //과목 최대
};



