﻿
// OpenCVAppGUIDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "OpenCVAppGUI.h"
#include "OpenCVAppGUIDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define NAME_WINDOW_SRC "srcView"
#define NAME_WINDOW_DEBUG "srcDebug"
#define NAME_WINDOW_RESULT "srcResult"
#define WM_ADD_STRING	(WM_USER + 500)

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenCVAppGUIDlg 대화 상자

COpenCVAppGUIDlg::COpenCVAppGUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENCVAPPGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenCVAppGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, _listBoxLog);
}

BEGIN_MESSAGE_MAP(COpenCVAppGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD, &COpenCVAppGUIDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_SAVE, &COpenCVAppGUIDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BUTTON_SAMPLE, &COpenCVAppGUIDlg::OnBnClickedButtonSample)
	ON_MESSAGE(WM_ADD_STRING, &COpenCVAppGUIDlg::OnAddString)
END_MESSAGE_MAP()


// COpenCVAppGUIDlg 메시지 처리기

BOOL COpenCVAppGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	//opencv -> window handle
	namedWindow(NAME_WINDOW_SRC, WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle(NAME_WINDOW_SRC);
	HWND hParent = (HWND)FindWindow(NULL, NAME_WINDOW_SRC);
	HWND hOrgParent = ::SetParent(hWnd, GetDlgItem(IDC_PICTURE)->m_hWnd);
	::ShowWindow(hOrgParent, SW_HIDE);

	namedWindow(NAME_WINDOW_DEBUG, WINDOW_AUTOSIZE);
	hWnd = (HWND)cvGetWindowHandle(NAME_WINDOW_DEBUG);
	hParent = (HWND)FindWindow(NULL, NAME_WINDOW_DEBUG);
	hOrgParent = ::SetParent(hWnd, GetDlgItem(IDC_PICTURE_DEBUG)->m_hWnd);
	::ShowWindow(hOrgParent, SW_HIDE);

	namedWindow(NAME_WINDOW_RESULT, WINDOW_AUTOSIZE);
	hWnd = (HWND)cvGetWindowHandle(NAME_WINDOW_RESULT);
	hParent = (HWND)FindWindow(NULL, NAME_WINDOW_RESULT);
	hOrgParent = ::SetParent(hWnd, GetDlgItem(IDC_PICTURE_RESULT)->m_hWnd);
	::ShowWindow(hOrgParent, SW_HIDE);

	//GetDlgItem(IDC_PICTURE)->GetWindowRect(_rtImageView);
	//ScreenToClient(_rtImageView);
	_mWndImageView.clear();
	_mWndImageView.insert(pair<int, CRect>(IDC_PICTURE, CRect(0, 0, 0, 0)));
	_mWndImageView.insert(pair<int, CRect>(IDC_PICTURE_DEBUG, CRect(0, 0, 0, 0)));
	_mWndImageView.insert(pair<int, CRect>(IDC_PICTURE_RESULT, CRect(0, 0, 0, 0)));

	for (auto iter = _mWndImageView.begin(); iter != _mWndImageView.end(); iter++) {
		int resID = (iter->first);
		CRect rtImgView;
		GetDlgItem(resID)->GetWindowRect(rtImgView);
		ScreenToClient(rtImgView);
		iter->second = rtImgView;
	}
	_mMatBuff.clear();
	_mInsps.clear();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void COpenCVAppGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void COpenCVAppGUIDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{

		//CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBrush brush(HS_DIAGCROSS, RGB(200, 200, 200));
		//dc.FillRect(CRect(rect.left + 1, rect.top + 1, rect.right, rect.bottom), &brush);

		for (auto iter = _mWndImageView.begin(); iter != _mWndImageView.end(); iter++) {
			CRect rt = iter->second;
			dc.FillRect(rt, &brush);
		}

		if (!_mMatBuff[eImgSrcColor].empty())
		{
			Mat Img = _mMatBuff[eImgSrcColor];
			Mat DrawResize;
			Size size(int(_dNewScale * Img.cols), int(_dNewScale * Img.rows));
			resize(Img, DrawResize, size);

			resizeWindow(NAME_WINDOW_SRC, size.width, size.height);
			imshow(NAME_WINDOW_SRC, DrawResize);
		}

		if (_bShowDebug)
		{
			if (!_mMatBuff[eImgDebugColor].empty())
			{
				Mat Img = _mMatBuff[eImgDebugColor];
				Mat DrawResize;
				Size size(int(_dNewScale * Img.cols), int(_dNewScale * Img.rows));
				resize(Img, DrawResize, size);

				resizeWindow(NAME_WINDOW_DEBUG, size.width, size.height);
				imshow(NAME_WINDOW_DEBUG, DrawResize);
			}
		}


		if (_bShowResult)
		{
			if (!_mMatBuff[eImgDrawColor].empty())
			{
				Mat Img = _mMatBuff[eImgDrawColor];
				Mat DrawResize;
				Size size(int(_dNewScale * Img.cols), int(_dNewScale * Img.rows));
				resize(Img, DrawResize, size);

				resizeWindow(NAME_WINDOW_RESULT, size.width, size.height);
				imshow(NAME_WINDOW_RESULT, DrawResize);
			}
		}
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR COpenCVAppGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COpenCVAppGUIDlg::UpdateDispSrc()
{
	_bShowDebug = false;
	_bShowResult = false;
	CRect rectSrc;
	::GetWindowRect(GetDlgItem(IDC_PICTURE)->m_hWnd, rectSrc);
	double dScaleX = rectSrc.Width() / (double)_SourceImage.cols;
	double dScaleY = rectSrc.Height() / (double)_SourceImage.rows;
	_dSrcScale = min(dScaleX, dScaleY);
	_dNewScale = _dSrcScale;
	//_bShowResult = FALSE;
	//防止顯示不同比例圖片時DC殘留
	CWnd* pWnd = GetDlgItem(IDC_PICTURE);
	pWnd->GetClientRect(&rectSrc);//제어 클라이언트 영역의 좌표 얻기
	pWnd->ClientToScreen(rectSrc);//제어 클라이언트 영역에서 대화 영역으로 영역 좌표 변환
	this->ScreenToClient(rectSrc); //다이얼로그 영역의 영역 좌표를 다이얼로그의 클라이언트 영역 좌표로 변환
	InvalidateRect(rectSrc);
}


void COpenCVAppGUIDlg::OnBnClickedBtnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();

		string fileName = path;
		_SourceImage = cv::imread(fileName, IMREAD_ANYCOLOR);

		OnAllocateBuffer(_SourceImage.cols, _SourceImage.rows);
		UpdateInspList();
		UpdateDispSrc();

		InvalidateRect(_rtImageView, FALSE);
		AfxMessageBox("Image Loaded");

	}
}

void COpenCVAppGUIDlg::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//string fileName = "jetson_clone.bmp";
	//_imageView.Save(fileName.c_str());

	CFileDialog dlgFileSave(FALSE, "*.*", NULL,//화일명 없음
		OFN_FILEMUSTEXIST,
		_T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"), NULL);

	//옵션 선택 부분.
	if (dlgFileSave.DoModal() == IDOK)
	{
		string str = dlgFileSave.GetPathName();
		imwrite(str, _SourceImage);
	}

	AfxMessageBox("Image Saved");
}

int COpenCVAppGUIDlg::OnAllocateBuffer(int cols, int rows)
{
	_mMatBuff.clear();

	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgSrcColor, Mat(rows, cols, CV_8UC3))); //color = 3 buffer
	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgSrcGray, Mat(rows, cols, CV_8UC1)));  //gray = 1 buffer
	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgDebugGray, Mat(rows, cols, CV_8UC1)));
	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgDebugColor, Mat(rows, cols, CV_8UC3)));
	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgDrawColor, Mat(rows, cols, CV_8UC3)));
	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgResultColor, Mat(rows, cols, CV_8UC3)));

	//source to draw of map
	if (_SourceImage.type() == CV_8UC1) //gray가 들어왔을 경우
	{
		cvtColor(_SourceImage, _mMatBuff[eImgSrcColor], COLOR_GRAY2BGR);
		_SourceImage.copyTo(_mMatBuff[eImgSrcGray]);
	}
	else  //color가 들어왔을 경우
	{
		_SourceImage.copyTo(_mMatBuff[eImgSrcColor]);
		cvtColor(_SourceImage, _mMatBuff[eImgSrcGray], COLOR_BGR2GRAY);
	}

	Mat vi = _mMatBuff[eImgSrcColor]; //형변환을 해준다



	_mMatBuff[eImgSrcColor].copyTo(_mMatBuff[eImgDrawColor]);

	//debug of map ... just create buffer as initilized value
	_mMatBuff[eImgDebugGray] = 0;

	//result of map ... just create buffer as initilized value
	_mMatBuff[eImgResultColor] = 255;

	return 0;
}


int COpenCVAppGUIDlg::UpdateInspList()
{
	_mInsps.insert(make_pair("OnInspFindShape", COpenCVAppGUIDlg::CallInspFindShape));
	_mInsps.insert(make_pair("OnInspMorpology", COpenCVAppGUIDlg::CallInspMorpology));
	_mInsps.insert(make_pair("OnInspHistogram", COpenCVAppGUIDlg::CallInspHistogram));
	_mInsps.insert(make_pair("OnInspHistoEqulization", COpenCVAppGUIDlg::CallInspHistoEqulization));

	return 1;
}

int COpenCVAppGUIDlg::OnInspection(uchar* pSrc, size_t cols, size_t rows, uchar* pDst)
{
	/*
	pSrc = pointer 2d
	cols = width
	rows = height
	pDst = result data, pointer 2d
	*/
	/* todo*/
	// 조건 pSrc = GrayScale
	// pSrc > 128 ? pDst = 255 : pDst = 0
	// 코드를 작성하세요

	for (size_t i = 0; i < cols * rows; i++)
	{
		pSrc[i] > 128 ? pDst[i] = 255 : pDst[i] = 0;
	}
	_vLinePoints_L.clear();
	_vLinePoints_R.clear();
	_vLinePoints_U.clear();
	_vLinePoints_D.clear();

	_pt1 = cv::Point(0, 0);
	_pt2 = cv::Point(0, 0);
	_pt3 = cv::Point(0, 0);
	_pt4 = cv::Point(0, 0);

	//Left -> Right
	for (size_t row = 0; row < rows; row++)
	{
		for (size_t col = 0; col < cols; col++)
		{
			int index = row * cols + col;
			if (pDst[index] > 100)
			{
				_vLinePoints_L.push_back(cv::Point(col, row));
				break;
			}
		}
	}

	//Right -> Left
	for (size_t row = 0; row < rows; row++)
	{
		for (size_t col = cols - 1; col > 0; col--)
		{
			int index = row * cols + col;
			if (pDst[index] > 100)
			{
				_vLinePoints_R.push_back(cv::Point(col, row));
				break;
			}
		}
	}

	//Top-> Down
	for (size_t col = 0; col < cols; col++)
	{
		for (size_t row = 0; row < rows; row++)
		{
			int index = row * cols + col;
			if (pDst[index] > 100)
			{
				_vLinePoints_U.push_back(cv::Point(col, row));
				break;
			}
		}
	}

	//Down -> Top
	for (size_t col = 0; col < cols; col++)
	{
		for (size_t row = rows - 1; row > 0; row--)
		{
			int index = row * cols + col;
			if (pDst[index] > 100)
			{
				_vLinePoints_D.push_back(cv::Point(col, row));
				break;
			}
		}
	}

	return 0;
}

int COpenCVAppGUIDlg::CallInspFindShape(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspFindShapes();
}

int COpenCVAppGUIDlg::CallInspMorpology(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspMorpology();
}
int COpenCVAppGUIDlg::CallInspHistogram(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspHistogram();
}
int COpenCVAppGUIDlg::CallInspHistoEqulization(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspHistoEqulization();
}

int COpenCVAppGUIDlg::OnInspFindShapes()
{
	Mat src_gray = _mMatBuff[eImgSrcGray];
	int thresh = 50;

	RNG rng(12345);

	Mat thr_img;
	threshold(src_gray, thr_img, thresh, 255, THRESH_BINARY);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(thr_img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	cvtColor(_mMatBuff[eImgDebugGray], _mMatBuff[eImgDebugColor], COLOR_GRAY2BGR);
	
	Mat drawing = _mMatBuff[eImgDebugColor];

	vector<int> circle_index, triangle_index, rectangle_index;

	for (size_t i = 0; i < contours.size(); i++)
	{
		RotatedRect rt = minAreaRect(contours[i]);
		double area = contourArea(contours[i]);
		double perimeter = arcLength(contours[i], true);
		double circularity = 4 * CV_PI * area / (perimeter * perimeter);

		ostringstream tag;
		tag << "[";
		tag << to_string(i + 1);
		tag << "]";
		putText(drawing, tag.str(), rt.boundingRect().tl(), CV_FONT_HERSHEY_TRIPLEX, 0.6, Scalar(255, 255, 255));
		ostringstream ss;
		ss << std::fixed;
		ss << "[";
		ss << to_string(i + 1);
		ss << "]";
		ss << " area = ";
		ss << std::setprecision(3) << area;
		ss << " perimeter = ";
		ss << std::setprecision(3) << perimeter;
		ss << " circularity = ";
		ss << std::setprecision(3) << circularity;
		string ssTxt = ss.str();
		AddString(ssTxt.c_str());

		if ((circularity > 0.5) && (circularity < 0.7))
		{
			triangle_index.push_back(i);
			continue;
		}
		else if ((circularity > 0.7) && (circularity < 0.8))
		{
			rectangle_index.push_back(i);
			continue;
		}
		else
		{
			circle_index.push_back(i);
			continue;
		}

	}

	for (size_t index = 0; index < rectangle_index.size(); index++)
	{
		drawContours(drawing, contours, rectangle_index[index], Scalar(0, 255, 100), CV_FILLED, 8, hierarchy);
	}
	for (size_t index = 0; index < triangle_index.size(); index++)
	{
		drawContours(drawing, contours, triangle_index[index], Scalar(255, 100, 0), CV_FILLED, 8, hierarchy);
	}
	for (size_t index = 0; index < circle_index.size(); index++)
	{
		drawContours(drawing, contours, circle_index[index], Scalar(100, 0, 255), CV_FILLED, 8, hierarchy);
	}


	//DrawColor창
	drawing = _mMatBuff[eImgDrawColor];

	for (size_t i = 0; i < contours.size(); i++)
	{
		RotatedRect rt = minAreaRect(contours[i]);
		double area = contourArea(contours[i]);
		double perimeter = arcLength(contours[i], true);
		double circularity = 4 * CV_PI * area / (perimeter * perimeter);
		ostringstream ss;
		if ((circularity > 0.5) && (circularity < 0.7))
		{
			triangle_index.push_back(i);
			continue;
		}
		else if ((circularity > 0.7) && (circularity < 0.8))
		{
			rectangle_index.push_back(i);
			continue;
		}
		else
		{
			circle_index.push_back(i);
			continue;
		}
	}

	Mat mask = _mMatBuff[eImgDrawColor].clone();
	mask = 0;

	drawing = _mMatBuff[eImgDrawColor];
	drawing = 0;

	CFileDialog dlgFileSave(FALSE, "*.*", NULL,//화일명 없음
		OFN_FILEMUSTEXIST,
		_T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"), NULL);

	for (size_t index = 0; index < rectangle_index.size(); index++)
	{
		drawContours(mask, contours, rectangle_index[index], Scalar(0, 255, 0), CV_FILLED, 8, hierarchy);
		string str = "rectangle.jpg";
		imwrite(str, mask);
		drawing += mask;
	}
	mask = 0;
	for (size_t index = 0; index < triangle_index.size(); index++)
	{
		drawContours(mask, contours, triangle_index[index], Scalar(255, 0, 0), CV_FILLED, 8, hierarchy);
		string str = "triangle.jpg";
		imwrite(str, mask);
		drawing += mask;
	}
	mask = 0;
	for (size_t index = 0; index < circle_index.size(); index++)
	{
		drawContours(mask, contours, circle_index[index], Scalar(0, 0, 255), CV_FILLED, 8, hierarchy);
		string str = "circle.jpg";
		imwrite(str, mask);
		drawing += mask;
	}
	mask = 0;
	
	_bShowDebug = true;
	_bShowResult = true;
	Invalidate(FALSE);

	return 0;
}


int COpenCVAppGUIDlg::OnInspMorpology()
{
	Mat src_gray = _mMatBuff[eImgSrcGray];
	threshold(src_gray, src_gray, 128, 255, ThresholdTypes::THRESH_BINARY_INV);

	//Erosion...침식
	int kernel_type = MORPH_RECT;// MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE
	//   0 0 0     0            0 0
	//   0 0 0   0 0 0        0 0 0
	//   0 0 0     0          0 0 

	int kernel_size = 1;
	Mat element = getStructuringElement(kernel_type,
		Size(2 * kernel_size + 1, 2 * kernel_size + 1),
		Point(kernel_size, kernel_size));
	Mat src_erode;
	erode(src_gray, src_erode, element, Point(-1, -1), 3);
	Mat diff = src_gray - src_erode;
	Mat res;

	//dilate 팽창
	Mat src_dilate;
	dilate(src_erode, src_dilate, element, Point(-1, -1), 3);
	erode(src_dilate, src_erode, element, Point(-1, -1), 2);
	Mat src_invert = ~src_erode;

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(src_erode, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	cvtColor(_mMatBuff[eImgDebugGray], _mMatBuff[eImgDebugColor], COLOR_GRAY2BGR);

	Mat drawing = _mMatBuff[eImgDebugColor];

	vector<int> circle_index, triangle_index, rectangle_index;

	for (size_t i = 0; i < contours.size(); i++)
	{
		RotatedRect rt = minAreaRect(contours[i]);
		double area = contourArea(contours[i]);
		double perimeter = arcLength(contours[i], true);
		double circularity = 4 * CV_PI * area / (perimeter * perimeter);

		ostringstream tag;
		tag << "[";
		tag << to_string(i + 1);
		tag << "]";
		putText(drawing, tag.str(), rt.boundingRect().tl(), CV_FONT_HERSHEY_TRIPLEX, 0.7, Scalar(255, 255, 255));
		ostringstream ss;
		ss << std::fixed;
		ss << "[";
		ss << to_string(i + 1);
		ss << "]";
		ss << " area = ";
		ss << std::setprecision(3) << area;
		ss << " perimeter = ";
		ss << std::setprecision(3) << perimeter;
		ss << " circularity = ";
		ss << std::setprecision(3) << circularity;
		string ssTxt = ss.str();
		AddString(ssTxt.c_str());
		if (circularity < 0.5)
		{
			triangle_index.push_back(i);
			drawContours(drawing, contours, (int)triangle_index[i], Scalar(255, 100, 0), 2, 8, hierarchy);
			continue;
		}
		else if ((circularity > 0.7) && (circularity < 0.8))
		{
			rectangle_index.push_back(i);
			drawContours(drawing, contours, (int)rectangle_index[i], Scalar(0, 255, 100), 2, 8, hierarchy);
			continue;
		}
		else
		{
			circle_index.push_back(i);
			drawContours(drawing, contours, (int)circle_index[i], Scalar(100, 0, 255), 2, 8, hierarchy);
			continue;
		}

	}

	drawing = _mMatBuff[eImgDrawColor];

	for (size_t i = 0; i < contours.size(); i++)
	{
		RotatedRect rt = minAreaRect(contours[i]);
		double area = contourArea(contours[i]);
		double perimeter = arcLength(contours[i], true);
		double circularity = 4 * CV_PI * area / (perimeter * perimeter);
		ostringstream ss;
		if ((circularity > 0.5) && (circularity < 0.7))
		{
			triangle_index.push_back(i);
			continue;
		}
		else if ((circularity > 0.7) && (circularity < 0.8))
		{
			rectangle_index.push_back(i);
			continue;
		}
		else
		{
			circle_index.push_back(i);
			continue;
		}
	}

	Mat mask = _mMatBuff[eImgDrawColor].clone();
	mask = 0;

	drawing = _mMatBuff[eImgDrawColor];
	drawing = 0;

	CFileDialog dlgFileSave(FALSE, "*.*", NULL,//화일명 없음
		OFN_FILEMUSTEXIST,
		_T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"), NULL);

	for (size_t index = 0; index < rectangle_index.size(); index++)
	{
		drawContours(mask, contours, rectangle_index[index], Scalar(0, 255, 0), CV_FILLED, 8, hierarchy);
		string str = "rectangle.jpg";
		imwrite(str, mask);
		drawing += mask;
	}
	mask = 0;
	for (size_t index = 0; index < triangle_index.size(); index++)
	{
		drawContours(mask, contours, triangle_index[index], Scalar(255, 0, 0), CV_FILLED, 8, hierarchy);
		string str = "triangle.jpg";
		imwrite(str, mask);
		drawing += mask;
	}
	mask = 0;
	for (size_t index = 0; index < circle_index.size(); index++)
	{
		drawContours(mask, contours, circle_index[index], Scalar(0, 0, 255), CV_FILLED, 8, hierarchy);
		string str = "circle.jpg";
		imwrite(str, mask);
		drawing += mask;
	}
	mask = 0;

	_bShowDebug = true;
	_bShowResult = true;
	Invalidate(FALSE);


	return 0;

}

int COpenCVAppGUIDlg::OnInspHistogram()
{
	
	Mat src_gray = _mMatBuff[eImgSrcGray];

	const int maxLength = src_gray.cols* src_gray.rows;
	int cols = src_gray.cols;
	int rows = src_gray.rows;

	const int histo_max = 256;
	int histo[histo_max] = { 0, };

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			int index = row * cols + col;
			int data = src_gray.data[index];
			histo[data]++;
			
		}
	}

	cvtColor(src_gray, _mMatBuff[eImgDebugColor], COLOR_GRAY2BGR);
	Mat draw = _mMatBuff[eImgDebugColor];
	int thickness = 2;
	int lineType = LINE_8;

	for (int i = 0; i < histo_max; i++)
	{
		line(draw, Point(0,i*2), Point(histo[i]/20, i*2), Scalar(255, 0, 255), thickness, lineType);
	}


	_bShowDebug = true;
	Invalidate(FALSE);

	return 0;
}

int COpenCVAppGUIDlg::OnInspHistoEqulization()
{
	_bShowDebug = _bShowResult = false;

	Mat src_gray = _mMatBuff[eImgSrcGray];

	const int histo_max = 256;
	int histo[histo_max] = { 0, };
	int cumulative_freq[histo_max] = { 0, };
	int new_gray_value[histo_max] = { 0, };
	//get histogram :: 히스토그램
	for (size_t i = 0; i < src_gray.cols * src_gray.rows; i++) histo[src_gray.data[i]]++;

	//get cumulative frequence :: 누적분포
	cumulative_freq[0] = histo[0];
	//for (size_t i = 1; i < histo_max; i++) cumulative_freq[i]=histo[i] + cumulative_freq[i-1];

	//get new value
	int acc = 0;
	for (size_t i = 0; i < histo_max; i++)
	{
		acc += histo[i];
		cumulative_freq[i] = acc;
		//new_gray_value[i] = round((((float)cumulative_freq[i]) * 255) / src_gray.cols * src_gray.rows);
		new_gray_value[i] = round((((float)acc) * 255) / (src_gray.cols * src_gray.rows));
	}

	//drawing...histo debug color area
	int thickness = 1;
	int lineType = LINE_8;

	cvtColor(_mMatBuff[eImgSrcGray], _mMatBuff[eImgDebugColor], ColorConversionCodes::COLOR_GRAY2BGR);

	Mat debug_draw = _mMatBuff[eImgDebugColor];
	//draw   |------>
	bool view_horizontal = false;
	bool view_vertical = true;
	if (view_horizontal)
	{
		for (size_t row = 0; row < histo_max; row++)
		{
			line(debug_draw, Point(0, row * 2), Point(histo[row] / 10, row * 2), Scalar(255, 0, 255), thickness, lineType);
		}
	}

	if (view_vertical)
	{
		int height = src_gray.rows;
		for (size_t col = 0; col < histo_max; col++)
		{
			//draw histo
			Point pt1 = Point(col * 2, height - 1);//start
			Point pt2 = Point(col * 2, height - 1 - histo[col] / 10);//end
			line(debug_draw, pt1, pt2, Scalar(0, 255, 128), thickness, lineType);
		}

		int max_cumulate = cumulative_freq[histo_max - 1];
		for (size_t col = 0; col < histo_max; col++)
		{
			if (col == 0)
			{
				int scaled_v = (cumulative_freq[col] / max_cumulate) * height;
				Point pt1 = Point(col * 2, scaled_v);//start
				Point pt2 = Point(col * 2, scaled_v);//end
				line(debug_draw, pt1, pt2, Scalar(0, 0, 255), thickness, lineType);
				continue;
			}
			//draw cumulate
			int scaled_v1 = (cumulative_freq[col - 1] * 1.0 / max_cumulate) * height;
			int scaled_v2 = (cumulative_freq[col] * 1.0 / max_cumulate) * height;
			Point pt1 = Point(col * 2, height - scaled_v1);//start
			Point pt2 = Point(col * 2, height - scaled_v2);//end
			line(debug_draw, pt1, pt2, Scalar(0, 0, 255), thickness, lineType);

		}
	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat src_gray_histoEqual = _mMatBuff[eImgSrcGray].clone();
	for (size_t i = 0; i < src_gray.cols * src_gray.rows; i++)
	{
		src_gray_histoEqual.data[i] = new_gray_value[src_gray.data[i]];
	}
	cvtColor(src_gray_histoEqual, _mMatBuff[eImgDrawColor], ColorConversionCodes::COLOR_GRAY2BGR);

	//get histogram :: 히스토그램
	for (size_t i = 0; i < src_gray.cols * src_gray.rows; i++) histo[src_gray_histoEqual.data[i]]++;

	//get cumulative frequence :: 누적분포
	cumulative_freq[0] = histo[0];
	//for (size_t i = 1; i < histo_max; i++) cumulative_freq[i]=histo[i] + cumulative_freq[i-1];

	//get new value
	acc = 0;
	for (size_t i = 0; i < histo_max; i++)
	{
		acc += histo[i];
		cumulative_freq[i] = acc;
		//new_gray_value[i] = round((((float)cumulative_freq[i]) * 255) / src_gray.cols * src_gray.rows);
		new_gray_value[i] = round((((float)acc) * 255) / (src_gray.cols * src_gray.rows));
	}

	//drawing...histo debug color area
	thickness = 1;
	lineType = LINE_8;


	Mat color_draw = _mMatBuff[eImgDrawColor];
	//draw   |------>
	view_horizontal = false;
	view_vertical = true;
	if (view_horizontal)
	{
		for (size_t row = 0; row < histo_max; row++)
		{
			line(color_draw, Point(0, row * 2), Point(histo[row] / 10, row * 2), Scalar(255, 0, 255), thickness, lineType);
		}
	}

	if (view_vertical)
	{
		int height = src_gray.rows;
		for (size_t col = 0; col < histo_max; col++)
		{
			//draw histo
			Point pt1 = Point(col * 2, height - 1);//start
			Point pt2 = Point(col * 2, height - 1 - histo[col] / 13);//end
			line(color_draw, pt1, pt2, Scalar(0, 255, 128), thickness, lineType);
		}

		int max_cumulate = cumulative_freq[histo_max - 1];
		for (size_t col = 0; col < histo_max; col++)
		{
			if (col == 0)
			{
				int scaled_v = (cumulative_freq[col] / max_cumulate) * height;
				Point pt1 = Point(col * 2, scaled_v);//start
				Point pt2 = Point(col * 2, scaled_v);//end
				line(color_draw, pt1, pt2, Scalar(0, 0, 255), thickness, lineType);
				continue;
			}
			//draw cumulate
			int scaled_v1 = (cumulative_freq[col - 1] * 1.0 / max_cumulate) * height;
			int scaled_v2 = (cumulative_freq[col] * 1.0 / max_cumulate) * height;
			Point pt1 = Point(col * 2, height - scaled_v1);//start
			Point pt2 = Point(col * 2, height - scaled_v2);//end
			line(color_draw, pt1, pt2, Scalar(0, 0, 255), thickness, lineType);

		}
	}

	_bShowDebug = true;
	_bShowResult = true;

	Invalidate(FALSE);
	return 0;
}


void COpenCVAppGUIDlg::OnBnClickedButtonSample()
{
	//auto f = _mInsps["OnInspMorpology"]; //final에서 사용하는 생략형 자료형(auto)
	//auto f = _mInsps["OnInspHistogram"]; //final에서 사용하는 생략형 자료형(auto)
	auto f = _mInsps["OnInspHistoEqulization"]; //final에서 사용하는 생략형 자료형(auto)
	if (f == nullptr) return;
	auto ret = f(this); //int COpenCVAppGUIDlg::OnInspFindShapes()함수를 호출해서 리턴값에 저장 

}

LRESULT COpenCVAppGUIDlg::OnAddString(WPARAM wParam, LPARAM lParam)
{
	if (!GetSafeHwnd()) return 0;

	if (_listBoxLog.GetCount() > 500)
	{
		_listBoxLog.ResetContent();
	}

	LPCTSTR lpszLog = reinterpret_cast <LPCTSTR> (lParam);
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString nStrMsg = _T("");
	nStrMsg += lpszLog;
	int nIdx = _listBoxLog.AddString(nStrMsg);
	_listBoxLog.SetTopIndex(_listBoxLog.GetCount() - 1);

	stringstream ssTime;
	time_t const now_c = time(NULL);
	//ssTime << put_time(localtime(&now_c), "%a %d %b %Y - %I_%M_%S%p");
	ssTime << put_time(localtime(&now_c), "%a %d %b %Y-%I_%M");
	string time_c = ssTime.str();

	ofstream file;
	string fileName;
	fileName += "log";
	fileName += ssTime.str();
	fileName += ".txt";

	file.open(fileName, ios::out | ios::app);
	file << nStrMsg << endl;
	file.close();

	return 0;
}

void COpenCVAppGUIDlg::AddString(LPCSTR lpszLog)
{
	SendMessage(WM_ADD_STRING, 0, (LPARAM)lpszLog);
}
