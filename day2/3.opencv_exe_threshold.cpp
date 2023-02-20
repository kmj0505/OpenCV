#include <iostream>
#include <opencv2/opencv.hpp>
#include "2.opencv_exe.h"
#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else     //RELEASE
#pragma comment(lib, "opencv_world470.lib")
#endif

#include <iostream>
#include <string>
#include <vector>
using namespace std;   //namespace를 선언하면 main의 string타입에 "std::"를 안붙여도 된다
using namespace cv;

int main()
{
	cout << "Hello OpenCV World!\n";
	std::string fileName = "jetson.bmp";
	Mat img = cv::imread(fileName, IMREAD_GRAYSCALE);
	int width = img.cols;
	int height = img.rows;
	unsigned char* pData = img.data;
	int threshold = 100;

	Mat thrImg;
	cv::threshold(img, thrImg, threshold, 255, THRESH_BINARY) ;   //(입력, 출력, 기준값, 맥스값)
	//threshold processing
	
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int index = row * width + col;
			(pData[index] >= threshold) ? pData[index] = 255 : pData[index] = 0;
			/*
			
			if (threshold < pData[index])//threshold보다 크면 pData를 255로 대입한다.
			{
				pData[index] = 255;
			}
			else if (90 < pData[index]) //90보다 크면 pData를 100으로 대입한다.
			{
				pData[index] = 100; 
			}
			else    //threshold보다 작으면 pData를 0으로 대입한다.
			{
				pData[index] = 0;
				
			}
		*/
		}
	}
	return 0;
}





