#pragma once
#include "common.h"

class Kphone
{
public:
	Kphone();
	~Kphone();
	int Send();  //��ȭ�� �Ǵ�
	int Cancel(); //��ȭ ����
	int Receive(); //��ȭ�� �޴�
	int Numbers(string _strNumbers); //��ȭ��ȣ�� �Է��Ѵ�
	int Numbers(int* pAudioData, int length);


private:
	string strNumber; //��ȭ��ȣ
	bool isConnected; //��ȭ���ΰ�?
};

