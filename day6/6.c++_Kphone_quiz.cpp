#include "Kphone.h"

int main()
{
	//��ȭ�ɱ�
	{
		//��ȭ�⸦ ���
		Kphone* pkphone = new Kphone();

		//��ȭ��ȣ �Է�
		//pkphone->Numbers("010-1234-5678");

		int* pAudio = new int[11];
		{
			0, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8;
		};
		int length = 11;
		pkphone->Numbers(pAudio, length); //revision 2.0


		//��ȭ�ɱ�
		pkphone->Send();

		pkphone->Cancel(); //revision 2.0

		//��ȭ�⸦ ������
		if (pkphone != nullptr)
		{
			delete pkphone;
			pkphone = nullptr;
		}
	}

	//��ȭ�ޱ�
	{
		//��ȭ�⸦ ���
		Kphone* pkphone = new Kphone();

		//��ȭ�ɱ�
		pkphone->Send();


		//��ȭ�⸦ ������
		if (pkphone != nullptr)
		{
			delete pkphone;
			pkphone = nullptr;
		}
	}
	


	//��ȭ�⸦ ������
	return 1;
}