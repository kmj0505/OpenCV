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
	stStudentInfo.mTable.clear(); //사람이 바뀌면 가지고있는 과목, 점수 테이블을 초기화한다
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
	//이름없는 함수 : lambda
	//[](uchar c) //?? [함수 이름??](uchar c)
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

	stStudentInfo.mTable.insert({ subject, score }); //map<subject, score> 저장
}

void StudentScore3::DoCalc()
{
	/*
	홍길동 = 국어:90, 영어:90, 수학:98, 미술:88, 음악:94, 역사 99 / 총합 = ??, 평균 = ??, 최소 = ??, 최대 = ??*/
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
	
		//<< "국어 : " << studentinfo.kor << "\t"
		//<< "영어 : " << studentinfo.eng << "\t"
		//<< "수학 : " << studentinfo.math << "\t"
		<< "총합 : " << GetSum() << "\t"
		<< "평균 : " << GetAvg() << "\t"
		<< "최소 : " << GetMin() << "\t"
		<< "최대 : " << GetMax() << endl;
}

int StudentScore3::GetSum()
{
	//return (studentinfo.kor + studentinfo.eng + studentinfo.math);
	int sum = 0;
	//using map {key, value}
	//values
	vector<int> vScores; //int형 벡터 vScores 생성
	for (auto iter = stStudentInfo.mTable.begin(); //stStudentInfo.mTable 시작점의 주소 값 반환
		iter != stStudentInfo.mTable.end(); iter++) //stStudentInfo.mTable(끝부분 + 1) 주소값 반환
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
	////오름차순[0, 작은수].....[N-1, 큰 수]
	//std::sort(score, score + 3); //score.begin(), score.end()

	//return score[0]; //값 반환

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
	std::sort(          //vScores 배열 begin~end 까지 오름차순 정렬
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
