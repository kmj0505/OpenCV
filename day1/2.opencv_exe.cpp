
#include <iostream>
#include <opencv2/opencv.hpp>
#include "2.opencv_exe.h"
#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else     //RELEASE
#pragma comment(lib, "opencv_world470.lib")
#endif

using namespace std;
using namespace cv;

int main()
{
	/*
	std::cout << "Hello OpenCVWorld!\n";
	std::string fileName = "jetson.bmp";
	cv::Mat img = cv::imread(fileName, IMREAD_GRAYSCALE);
	int width = img.cols;
	int height = img.rows;
	unsigned char* pData = img.data;
	//mask processing
	int mask_width = 3; int mask_height = 3;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int index = row * width + col;
			if (row >= 0 && row < mask_height)
			{
				if (col >= 0 && col < mask_width)
				{
					pData[index] = 255;
				}
			}

			if (row >= height-mask_height && row > mask_height)
			{
				if (col >= 0 && col < mask_width)
				{
					pData[index] = 255;
				}
			}

			if (row >= height-mask_height && row > mask_height)
			{
				if(col>=width-mask_width && col>mask_width)
					{
						pData[index] = 255;
					}
			}

			if (row >= 0 && row < mask_height)
			{
				if (col >= width-mask_width && col > mask_width)
				{
					pData[index] = 255;
				}
			}
		}

	}
	*/

	std::cout << "Hello OpenCVWorld!\n";
	std::string fileName = "jetson.bmp";
	cv::Mat img = cv::imread(fileName, IMREAD_COLOR);
	int width = img.cols;
	int height = img.rows;
	unsigned char* pData = img.data;
	//mask processing
	int mask_width = 3; int mask_height = 3;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int index = (row * width + col)*3;
			if (row >= 0 && row < mask_height)
			{
				if (col >= 0 && col < mask_width)
				{
					for (int i = 0; i < 3; i++)
					{
						pData[index+i] = 255;
					}
				}
			}

			if (row >= height - mask_height && row > mask_height)
			{
				if (col >= 0 && col < mask_width)
				{
					for (int i = 0; i < 3; i++)
					{
						pData[index + i] = 255;
					}
				}
			}

			if (row >= height - mask_height && row > mask_height)
			{
				if (col >= width - mask_width && col > mask_width)
				{
					for (int i = 0; i < 3; i++)
					{
						pData[index + i] = 255;
					}
				}
			}

			if (row >= 0 && row < mask_height)
			{
				if (col >= width - mask_width && col > mask_width)
				{
					for (int i = 0; i < 3; i++)
					{
						pData[index + i] = 255;
					}
				}
			}
		}

	}

	return 0;
}
	