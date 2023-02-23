#include "StudentScore.h"

int main()
{
	StudentScore* studentscore = new StudentScore(); //동적으로 선언
	string name;  //name변수에 입력받은 값 저장
	cin >> name;
	
	studentscore->SetStudentName(name); 
	
	int subjectCnt = 6;
	int scores = 0;
	for (int i = 0; i < subjectCnt; i++)  //arr_subject의 과목에 입력받은 score 점수 저장
	{
		cout << arr_subject[i] << ":";
		cin >> scores;
		studentscore->SetSubjectScore(arr_subject[i], scores);
	}
	

	studentscore->DoCalc();  // 함수 출력

	if (studentscore != nullptr)  //동적 선언한 것 없애줌
	{
		delete studentscore;
		studentscore = nullptr;
	}

	return 1;
}