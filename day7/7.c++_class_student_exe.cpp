#include "StudentScore_rev0.0.h"

int main()
{
	//name, scorekor, eng, math
	string strName;
	int scoreKor, scoreEng, scoreMath;

	cout << "Input Student Name :";
	cin >> strName;

	cout << "Input StudentSubject {Kor, Eng, Math} Score : ";
	cin >> scoreKor >> scoreEng >> scoreMath;

	StudentScore2 ss;
	ss.SetStudentName(strName);
	ss.SetSubjectScore("Kor", scoreKor);
	ss.SetSubjectScore("ENG", scoreEng);
	ss.SetSubjectScore("Math", scoreMath);
	ss.DoCalc();

	return 1;
}