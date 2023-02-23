#include "Kphone.h"


Kphone::Kphone()
	:strNumber("000-0000-0000")  //private �ʱⰪ ����
	, isConnected(false)
{
	cout << "Kphone::Ctor" << endl;
}

Kphone::~Kphone() //�Ҹ���
{
	cout << "Kphone::Dtor" << endl;
}

int Kphone::Send()
{
	//��ȭ��ȣ�� �ִ��� check
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
	//��ȭ������ check - ��ȭ���̸� ���� �� ����
	//��ȭ�� - 1, ��ȭ��x - 0
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
	//��ȭ�⿡ ��ȭ��ȣ�� �Է����ִ� ��
	strNumber = _strNumbers;
	return 0;
}

int Kphone::Numbers(int* pAudioData, int length)
{
	//pAudioData �м�
	//�����ν� �˰��� �ִ´�
	string number = "010-1234-5678";//DoAnalysisAudioData(pAudioData, length);
	strNumber = number;
	//����� ���ڷ� ��ȯ
	return 0;

}

