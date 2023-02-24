#include "StudentScore_rev1.0.h"

StudentScore3::StudentScore3()
{
	cout << "StudentScore3::Ctor" << endl;
}

StudentScore3::~StudentScore3()
{
	cout << "StudentScore3::Dtor" << endl;
}

void StudentScore3::SetStudentName(string name)
{
	stStudentInfo.name = name;
	stStudentInfo.mTable.clear(); //����� �ٲ�� �������ִ� ����, ���� ���̺��� �ʱ�ȭ�Ѵ�
}

void StudentScore3::SetSubjectScore(string subject, int score)
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
	//for (size_t i = 0; i < str.size(); i++)
	//{
	//	str[i] = std::toupper(str[i]);
	//}

	////C++ style :: lambda expresstion
	//std::transform(str.begin(),str.end(),str.begin(), 
	//	[](unsigned char c) {return toupper(c); });
	//�̸����� �Լ� : lambda
	//[](uchar c) //?? [�Լ� �̸�??](uchar c)
	//{
	//	return toupper(c);
	//}

	/*-----------------------------------------------------*/
	/*if (str == "KOR")
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
	}*/

	if (stStudentInfo.mTable.find(subject) != stStudentInfo.mTable.end())
	{
		cout << "same subject found" << endl;
		return;
	}

	stStudentInfo.mTable.insert({ subject, score }); //map<subject, score> ����
}

void StudentScore3::DoCalc()
{
	/*
	ȫ�浿 = ����:90, ����:90, ����:98, �̼�:88, ����:94, ���� 99 / ���� = ??, ��� = ??, �ּ� = ??, �ִ� = ??*/
	cout << stStudentInfo.name << " = ";
	string strSubjectReport;
	for (auto iter = stStudentInfo.mTable.begin();
		iter != stStudentInfo.mTable.end();
		iter++)
	{
		strSubjectReport += iter->first;
		strSubjectReport += " : ";
		strSubjectReport += std::to_string(iter->second);
		strSubjectReport += "\t";
	}
	cout << strSubjectReport
	
		//<< "���� : " << studentinfo.kor << "\t"
		//<< "���� : " << studentinfo.eng << "\t"
		//<< "���� : " << studentinfo.math << "\t"
		<< "���� : " << GetSum() << "\t"
		<< "��� : " << GetAvg() << "\t"
		<< "�ּ� : " << GetMin() << "\t"
		<< "�ִ� : " << GetMax() << endl;
}

int StudentScore3::GetSum()
{
	//return (studentinfo.kor + studentinfo.eng + studentinfo.math);
	int sum = 0;
	//using map {key, value}
	//values
	vector<int> vScores; //int�� ���� vScores ����
	for (auto iter = stStudentInfo.mTable.begin(); //stStudentInfo.mTable �������� �ּ� �� ��ȯ
		iter != stStudentInfo.mTable.end(); iter++) //stStudentInfo.mTable(���κ� + 1) �ּҰ� ��ȯ
	{
		iter->first; //key:string (stStudentInfo.mTable.begin())
		iter->second; //value:int (stStudentInfo.mTable.begin())
		//sum = sum + iter->second;
		vScores.push_back(iter->second);
	}
	//*(address++)
	//address[i++]
	//int a = 10;		auto b = 10; //int
	//auto c = "abc";

	for (auto iter = vScores.begin(); iter != vScores.end(); iter++)
	{
		sum += (*iter); //value, iter::pointer address
	}

	return sum;
}

float StudentScore3::GetAvg()
{
	//return GetSum() / 3.0;
	return GetSum() / stStudentInfo.mTable.size();
}
  
int StudentScore3::GetMin()
{
	//int score[3] = { studentinfo.kor, studentinfo.eng, studentinfo.math };
	//int min = score[0];
	//for (size_t i = 0; i < 3; i++)
	//{
	//	if (min > score[i])
	//	{
	//		min = score[i];
	//	}
	//}

	////sort
	////��������[0, ������].....[N-1, ū ��]
	//std::sort(score, score + 3); //score.begin(), score.end()

	//return score[0]; //�� ��ȯ

	vector<int> vScores;
	for (auto iter = stStudentInfo.mTable.begin(); iter != stStudentInfo.mTable.end(); iter++)
	{
		iter->first; //key:string
		iter->second; //value:int
		//sum = sum + iter->second;
		vScores.push_back(iter->second);
	}

	//int a[10];
	//a...array start addfress
	//int* pA = &a[0] = a;
	std::sort(          //vScores �迭 begin~end ���� �������� ����
		vScores.begin(),
		vScores.end()
	);
	return vScores[0];
}

int StudentScore3::GetMax()
{
	vector<int> vScores;
	for (auto iter = stStudentInfo.mTable.begin(); iter != stStudentInfo.mTable.end(); iter++)
	{
		iter->second; //value:int
		vScores.push_back(iter->second);
	}


	std::sort(vScores.begin(), vScores.end());
	return vScores[vScores.size() - 1]; //<-max vs min - vScores[0];
}
