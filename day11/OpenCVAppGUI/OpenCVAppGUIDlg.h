﻿
// OpenCVAppGUIDlg.h: 헤더 파일
//

#pragma once

#include <iostream>
#include <map>

#define OPENCV_470

#include <opencv2/opencv.hpp>
#ifdef OPENCV_470
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/types_c.h>
#endif // OPENCV_470

#ifdef _DEBUG
#pragma comment(lib,"opencv_world470d.lib")
#else	//RELEASE
#pragma comment(lib,"opencv_world470.lib")
#endif
using namespace std;
using namespace cv;

enum { eImgSrcColor = 0, eImgSrcGray, eImgDebugGray, eImgDebugColor, eImgDrawColor, eImgResultColor, eImgBufferMax};

// COpenCVAppGUIDlg 대화 상자
class COpenCVAppGUIDlg : public CDialogEx
{
// 생성입니다.
public:
	COpenCVAppGUIDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCVAPPGUI_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private : 
	std::map<int, cv::Mat> _mMatBuff;// { {"src", 10}, { "GPU", 15 }, { "RAM", 20 } };
	std::map<int, CRect> _mWndImageView;// { {1016, (10,10,300,400)}, { 2, (301,10,300,400) }, { "RAM", 20 } };

	CRect _rtImageView;//image view area
	cv::Mat _SourceImage, _DrawImage; // 이미지 정보를 담고 있는 객체.
	//_Draw ... display ... original+draw rect/line/circle ...
	//_Frame/_SourceBuffer  ... original
	//agorithm...function (input, params)...input-constant, params-variables
	//_ProcessImage ... 중간/결과 이미지 buffer

	vector<cv::Point> _vLinePoints;
	cv::Point _pt1, _pt2;

	bool _bShowDebug = false;
	bool _bShowResult = false;

	double _dSrcScale = 1.0, _dNewScale = 1.0;

public:
	void UpdateDispSrc();

private:
	int OnAllocateBuffer(int cols, int rows);
	void OnReleaseBuffer();


	int OnInspection(InputArray src, OutputArray dst);
	int OnInspection(Mat src, Mat dst);
	int OnInspection(uchar* pSrc, size_t cols, size_t rows, uchar* pDst);

	int detectLine(uchar* pSrc, size_t cols, size_t rows, uchar* pDst);

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnInspection();
	afx_msg void OnStnClickedPictureDebug();
	afx_msg void OnStnClickedPictureResult();
};
