#include "StudentScore.h"

int main()
{
	StudentScore* studentscore = new StudentScore(); //�������� ����
	string name;  //name������ �Է¹��� �� ����
	cin >> name;
	
	studentscore->SetStudentName(name); 
	
	int subjectCnt = 6;
	int scores = 0;
	for (int i = 0; i < subjectCnt; i++)  //arr_subject�� ���� �Է¹��� score ���� ����
	{
		cout << arr_subject[i] << ":";
		cin >> scores;
		studentscore->SetSubjectScore(arr_subject[i], scores);
	}
	

	studentscore->DoCalc();  // �Լ� ���

	if (studentscore != nullptr)  //���� ������ �� ������
	{
		delete studentscore;
		studentscore = nullptr;
	}

	return 1;
}