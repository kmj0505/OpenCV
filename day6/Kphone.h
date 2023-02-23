#pragma once
#include "common.h"

class Kphone
{
public:
	Kphone();
	~Kphone();
	int Send();  //전화를 건다
	int Cancel(); //전화 끊기
	int Receive(); //전화를 받다
	int Numbers(string _strNumbers); //전화번호를 입력한다
	int Numbers(int* pAudioData, int length);


private:
	string strNumber; //전화번호
	bool isConnected; //전화중인가?
};

