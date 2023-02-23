#include "Kphone.h"


Kphone::Kphone()
	:strNumber("000-0000-0000")  //private 초기값 설정
	, isConnected(false)
{
	cout << "Kphone::Ctor" << endl;
}

Kphone::~Kphone() //소멸자
{
	cout << "Kphone::Dtor" << endl;
}

int Kphone::Send()
{
	//전화번호가 있는지 check
	if (strNumber != "000-0000-0000")
	{
		cout << "Wrong Number" << endl;
		return -1;
	}

	//check on the phone
	if (isConnected == true)
	{
		cout << "on the phone" << endl;
		return -1;
	}

	cout << "calling" << endl;
	cout << "linked" << endl;

	isConnected = true;

	cout << "Communication start" << endl;
	

	return 0;
}

int Kphone::Cancel()
{
	cout << "Cancel button activated" << endl;
	//Cancel
	cout << "Communication finish" << endl;
	isConnected = false;
	return 0;
}

int Kphone::Receive()
{
	//통화중인지 check - 통화중이면 받을 수 없다
	//통화중 - 1, 통화중x - 0
	if (isConnected == true)
	{
		cout << "on the phone" << endl;
		return -1;
	}
	cout << "linked" << endl;

	isConnected = true;

	cout << "Communication start" << endl;
	cout << "Communication finish" << endl;
	isConnected = false;

	return 0;
}

int Kphone::Numbers(string _strNumbers)
{
	//전화기에 전화번호를 입력해주는 것
	strNumber = _strNumbers;
	return 0;
}

int Kphone::Numbers(int* pAudioData, int length)
{
	//pAudioData 분석
	//음성인식 알고리즘 넣는다
	string number = "010-1234-5678";//DoAnalysisAudioData(pAudioData, length);
	strNumber = number;
	//결과를 문자로 변환
	return 0;

}

