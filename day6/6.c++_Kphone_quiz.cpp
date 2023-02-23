#include "Kphone.h"

int main()
{
	//전화걸기
	{
		//전화기를 든다
		Kphone* pkphone = new Kphone();

		//전화번호 입력
		//pkphone->Numbers("010-1234-5678");

		int* pAudio = new int[11];
		{
			0, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8;
		};
		int length = 11;
		pkphone->Numbers(pAudio, length); //revision 2.0


		//전화걸기
		pkphone->Send();

		pkphone->Cancel(); //revision 2.0

		//전화기를 내린다
		if (pkphone != nullptr)
		{
			delete pkphone;
			pkphone = nullptr;
		}
	}

	//전화받기
	{
		//전화기를 든다
		Kphone* pkphone = new Kphone();

		//전화걸기
		pkphone->Send();


		//전화기를 내린다
		if (pkphone != nullptr)
		{
			delete pkphone;
			pkphone = nullptr;
		}
	}
	


	//전화기를 내린다
	return 1;
}