#include "StudentScore_rev1.0.h"

int main() 
{
	vector< StudentScore3> vStudent;
	string strName, strSubjectName;
	while (true)
	{
		StudentScore3 ss;

		int score;
		cout << "Input Student Name : ";
		cin >> strName;
		if (strName == "Q" || strName == "q")
		{
			break;
		}
		ss.SetStudentName(strName);
		while (true)
		{
			cout << "Input Subject name : ";
			cin >> strSubjectName;

			if (strSubjectName == "Q" || strSubjectName == "q")
			{
				ss.DoCalc();
				break;
			}
			cout << "Input Subject score : ";
			cin >> score;

			ss.SetSubjectScore(strSubjectName, score);

		}

		vStudent.push_back(ss); //한 사람 등록완료
	}

	for (size_t i = 0; i < vStudent.size(); i++)
	{
		vStudent[i].DoCalc();
	}



	
	return 1;
}