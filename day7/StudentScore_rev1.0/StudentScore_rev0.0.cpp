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


	//�̸����� �Լ� : lambda
	//[](uchar c) //?? [�Լ� �̸�??](uchar c)
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
	ȫ�浿 = ����:90, ����:90, ����:98, �̼�:88, ����:94, ���� 99 / ���� = ??, ��� = ??, �ּ� = ??, �ִ� = ??*/

	cout << studentinfo.name << "="
		<< "���� : " << studentinfo.kor << " | "
		<< "���� : " << studentinfo.eng << " | "
		<< "���� : " << studentinfo.math << " | "
		<< "���� : " << GetSum() << " | "
		<< "��� : " << GetAvg() << " | "
		<< "�ּ� : " << GetMin() << " | "
		<< "�ִ� : " << GetMax() << endl;

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
	//��������[0, ������].....[N-1, ū ��]
	std::sort(score, score + 3); //score.begin(), score.end()

	return score[0]; //�� ��ȯ
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
	//��������[0, ������].....[N-1, ū ��]
	std::sort(score, score + 3); //score.begin(), score.end()

	return score[3-1]; //�� ��ȯ
}
