
// OpenCVAppGUIDlg.h: 헤더 파일
//

#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else     //RELEASE
#pragma comment(lib, "opencv_world470.lib")
#endif

using namespace std;
using namespace cv;


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

	CRect _rtImageView; //image view area
	CImage _imageView; //image control object
	CRect _rtImageView2; //image view area
	CImage _imageView2; //image control object

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
	afx_msg void OnBnClickedBtnLoad1();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnStnClickedPicture();
	afx_msg void OnBnClickedBtnResult();
	afx_msg void OnStnClickedViewpicture();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedCheckBtn();
	afx_msg void OnBnClickedCancelBtn();
};
