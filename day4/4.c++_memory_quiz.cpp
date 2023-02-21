//memory
//alloc, release
//pointer vs reference
//1D array and index

#include <iostream>
#include <memory>
//1)int sum(int* const pData, int size)
//2)int sum(const int* pData, int size)
//3)int sum(const int* const pData, int size)
//int sum(int* pData, int size)

using namespace std;

int sum(const int* const pData, int length)
{
	int sum = 0;
	for (size_t i = 0; i < length; i++)
	{
		sum += pData[i];
	}
	return sum;
}



//partial_sum 함수 start_index = 5, finish_index = 23
int sum(const int* const pData, int length, int start_index, int finish_index)
{
	int sum = 0;

	for (size_t i = start_index; i <= finish_index; i++)
	{
		sum += pData[i];
	}
	return sum;
}


//partial_sum 함수 start_row, start_col (1,1), finish_row, finish_col(3,3)
int sum(const int* const pData, int width, int height, int start_row, int start_col, int finish_row, int finish_col)
{
	int sum = 0;

	for (size_t row = start_row; row <= finish_row; row++)
	{
		for (size_t col = start_col; col <= finish_col; col++)
		{
			int index = (row) * width + (col);
			sum += pData[index];
		}
	}

	return sum;
}


int main()
{
	int width = 5;
	int height = 5;
	int* pImg = new int[width * height] {
		//-> col[0]...[4]
		3, 6, 7, 2, 5,//row[0]
		6, 5, 4, 3, 5,
		7, 5, 4, 5, 2,
		3, 4, 6, 8, 4,
		2, 6, 3, 7, 4,//row[4]
	};
	//partial data 추출
	cout << "image data sum1 = " << sum(pImg, width * height) << endl;

	//partial_sum 함수 start_index = 5, finish_index = 23
	int start_index = 5, finish_index = 23;
	cout << "image data sum2 = " << sum(pImg, width * height, start_index, finish_index) << endl;

	//partial_sum 함수 start_row, start_col (1,1), finish_row, finish_col(3,3)
	cout << "image data sum3 = " << sum(pImg, width, height, 1,1,3,3) << endl;
	
	if (pImg != nullptr)delete[] pImg;

	return 0;
}

