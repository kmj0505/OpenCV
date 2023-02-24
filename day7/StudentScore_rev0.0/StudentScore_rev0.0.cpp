#include "StudentScore_rev0.0.h"

StudentScore2::StudentScore2()
{
	cout << "StudentScore2::Ctor" << endl;
}

StudentScore2::~StudentScore2()
{
	cout << "StudentScore2::Dtor" << endl;
}

int StudentScore2::SetStudentName(string name)
{
	studentinfo.name = name;
	return 0;
}

int StudentScore2::SetSubjectScore(string subject, int score)
{
	string str = subject;
	//kor, KOR, Kor, kOr, koR
	//str -> lower -> upper
	//string {'a', 'b', 'c', 'd', 'e', 'f'} => "abcdef"
	//lower -> upper
	//str[0] 'a' --> 'A'					=> "Abcdef"
	//str[1] 'b' --> 'B'					=> "ABcdef"

	/*-----------------------------------------------------*/
	//C-style
	for (size_t i = 0; i < str.size(); i++)
	{
		str[i] = std::toupper(str[i]);
	}

	//C++ style :: lambda expresstion
	std::transform(str.begin(),
		str.end(),
		str.begin(), [](uchar c) {return toupper(c); });


	//이름없는 함수 : lambda
	//[](uchar c) //?? [함수 이름??](uchar c)
	//{
	//	return toupper(c);
	//}

	/*-----------------------------------------------------*/
	if (str == "KOR")
	{
		studentinfo.kor = score;
	}
	else if (str == "ENG")
	{
		studentinfo.eng = score;
	}
	else if (str == "MATH")
	{
		studentinfo.math = score;
	}
	else
	{
		cout << "Subject {Kor, Eng, Math} Only" << endl;
	}
	return 0;
}

int StudentScore2::DoCalc()
{
	/*
	홍길동 = 국어:90, 영어:90, 수학:98, 미술:88, 음악:94, 역사 99 / 총합 = ??, 평균 = ??, 최소 = ??, 최대 = ??*/

	cout << studentinfo.name << "="
		<< "국어 : " << studentinfo.kor << " | "
		<< "영어 : " << studentinfo.eng << " | "
		<< "수학 : " << studentinfo.math << " | "
		<< "총합 : " << GetSum() << " | "
		<< "평균 : " << GetAvg() << " | "
		<< "최소 : " << GetMin() << " | "
		<< "최대 : " << GetMax() << endl;

 	return 0;
}

int StudentScore2::GetSum()
{
	return (studentinfo.kor + studentinfo.eng + studentinfo.math);
}

float StudentScore2::GetAvg()
{
	return GetSum()/3.0;
}

int StudentScore2::GetMin()
{
	int score[3] = { studentinfo.kor, studentinfo.eng, studentinfo.math };
	int min = score[0];
	for (size_t i = 0; i < 3; i++)
	{
		if (min > score[i])
		{
			min = score[i];
		}
	}

	//sort
	//오름차순[0, 작은수].....[N-1, 큰 수]
	std::sort(score, score + 3); //score.begin(), score.end()

	return score[0]; //값 반환
}

int StudentScore2::GetMax()
{
	int score[3] = { studentinfo.kor, studentinfo.eng, studentinfo.math };
	int max = score[0];
	for (size_t i = 0; i < 3; i++)
	{
		if (max > score[i])
		{
			max = score[i];
		}
	}

	//sort
	//오름차순[0, 작은수].....[N-1, 큰 수]
	std::sort(score, score + 3); //score.begin(), score.end()

	return score[3-1]; //값 반환
}
