#include <iostream>

//Histogram을 출력하세요
	//0-4개
	//1-?개
	//..
	//5-1개

int main()
{
	const int maxLength = 25;
	int data[maxLength] = {
		1,2,3,4,5,
		1,0,2,0,4,
		2,3,0,2,3,
		3,1,2,3,2,
		1,2,3,0,2 };


	const int histo_max = 6; //from data[]:0~5
	int histo[histo_max] = { 0, };  // 초기화시킴 ex) histo[0,1,2,3,4,5] = 0;
	//0, 1, 2, 3, 4, 5 => 6
	//histo[0] = 0,0,0,0;   //4개     //from data[?] = 0
	//histo[0]++; -> 4

	//histo[1] = 4
	//histo[5] = 1

	for (int i = 0; i < maxLength; i++)
	{
		histo[data[i]]++;     //ex) histo[0] = data[?] = 0
	}
	for (int row = 0; row < histo_max; row++)
	{
		std::cout << row << "|";
		for (int col = 0; col < histo[row]; col++)   //histo[0]~[6] 각 개수별로 "=" 출력
		{
			std::cout << "=";
		}
		std::cout << std::endl;    //줄바꿈
	}

}

	
