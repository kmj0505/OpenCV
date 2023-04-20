
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
#include <format>

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
	UpdateInspList();
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
		//UpdateInspList();
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


void COpenCVAppGUIDlg::OnBnClickedButtonSample()
{
	//auto f = _mInsps["OnInspMatchingExample"]; //final에서 사용하는 생략형 자료형(auto)
	//auto f = _mInsps["OnInspMatching"]; //final에서 사용하는 생략형 자료형(auto)
	//auto f = _mInsps["OnInspMatchingWally"]; //final에서 사용하는 생략형 자료형(auto)
	auto f = _mInsps["OnInspMatchingZoom"]; //final에서 사용하는 생략형 자료형(auto)
	if (f == nullptr) return;
	auto ret = f(this); //int COpenCVAppGUIDlg::OnInspFindShapes()함수를 호출해서 리턴값에 저장 
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


	//source to source of map
	//_SourceImage.copyTo(_mMatBuff[eImgSrc]);

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
	_mInsps.clear();
	_mInsps.insert(make_pair("OnInspMatchingExample", COpenCVAppGUIDlg::CallInspMatchingExample));
	_mInsps.insert(make_pair("OnInspMatching", COpenCVAppGUIDlg::CallInspMatching));
	_mInsps.insert(make_pair("OnInspMatchingWally", COpenCVAppGUIDlg::CallInspMatchingWally));
	_mInsps.insert(make_pair("OnInspMatchingZoom", COpenCVAppGUIDlg::CallInspMatchingZoom));

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

int COpenCVAppGUIDlg::CallInspMatchingExample(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspMatchingExample();
}
int COpenCVAppGUIDlg::CallInspMatching(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspMatching();
}
int COpenCVAppGUIDlg::CallInspMatchingWally(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspMatchingWally();
}
int COpenCVAppGUIDlg::CallInspMatchingZoom(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspMatchingZoom();
}



int COpenCVAppGUIDlg::OnInspMatchingExample()
{
	_bShowDebug = _bShowResult = false;

	Mat search_img = cv::imread("../Build/x64/images/search_image.png", IMREAD_GRAYSCALE);
	Mat search_ptrn = cv::imread("../Build/x64/images/search_pattern.png", IMREAD_GRAYSCALE);
	Mat matching_img = Mat::zeros(search_img.size(), CV_64F);
	//Mat matching_img = search_img.clone();
	//matching_img = 0; 로도 쓸 수 있음

	//pattern matching
	for (size_t row = 0; row < search_img.rows - search_ptrn.rows; row++)
	{
		for (size_t col = 0; col < search_img.cols - search_ptrn.cols; col++)
		{
			uchar* pSearch = search_img.data;
			uchar* pPtrn = search_ptrn.data;//5x2
			// * * * * *
			// * * * * *

			double TM_SQDIFF = 0.0;
			double TM_SQDIFF_NORMED = 0.0;

			for (size_t prow = 0; prow < search_ptrn.rows; prow++)
			{
				for (size_t pcol = 0; pcol < search_ptrn.cols; pcol++)
				{
					int search_index = (row + prow) * search_img.cols + (col + pcol);
					int ptrn_index = prow * search_ptrn.cols + pcol;

					double diff = pSearch[search_index] - pPtrn[ptrn_index];
					TM_SQDIFF += (diff * diff);
					//diff = diff * diff;
					//matching_img.at<double>(row + prow, col + pcol) = diff;

				}
			}
			double ptrnSQ = 0., searchSQ = 0.;
			for (size_t prow = 0; prow < search_ptrn.rows; prow++)
			{
				for (size_t pcol = 0; pcol < search_ptrn.cols; pcol++)
				{
					int search_index = (row + prow) * search_img.cols + (col + pcol);
					int ptrn_index = prow * search_ptrn.cols + pcol;
					searchSQ += pSearch[search_index] * pSearch[search_index];
					ptrnSQ += pPtrn[ptrn_index] * pPtrn[ptrn_index];
				}
			}

			//matching_img.at<double>(row, col) = TM_SQDIFF;
			if (ptrnSQ == 0) ptrnSQ = 1;
			TM_SQDIFF_NORMED = TM_SQDIFF / sqrt(ptrnSQ * searchSQ);
			matching_img.at<double>(row, col) = TM_SQDIFF_NORMED;
		}
	}
	_bShowDebug = true;
	_bShowResult = true;

	Invalidate(FALSE);
	return 0;
}
int COpenCVAppGUIDlg::OnInspMatching()
{
	_bShowDebug = _bShowResult = false;

	Mat search_img = cv::imread("../Build/x64/images/search_array.png", IMREAD_GRAYSCALE);
	Mat search_ptrn = cv::imread("../Build/x64/images/search_ptrn_rect.png", IMREAD_GRAYSCALE);
	Mat matching_img = Mat::zeros(search_img.size(), CV_64F);
	//Mat matching_img = search_img.clone();
	//matching_img = 0; 로도 쓸 수 있음

	if (0)//C++_Debug_Performance : 72s
	{
		/*Mat matching_img = search_img.clone();
			matching_img = 0;*/
		Mat matching_img = Mat::zeros(Size(search_img.cols - search_ptrn.cols + 1, search_img.rows - search_ptrn.rows + 1), CV_32F);

		vector<Point> ptFind; ptFind.clear();
		//pattern matching
		for (size_t row = 0; row < search_img.rows - search_ptrn.rows + 1; row++)
		{
			for (size_t col = 0; col < search_img.cols - search_ptrn.cols + 1; col++)
			{
				uchar* pSearch = search_img.data;
				uchar* pPtrn = search_ptrn.data;//5x2

				double TM_SQDIFF = 0.0;
				double TM_SQDIFF_NORMED = 0.0;
				for (size_t prow = 0; prow < search_ptrn.rows; prow++)
				{
					for (size_t pcol = 0; pcol < search_ptrn.cols; pcol++)
					{
						int search_index = (row + prow) * search_img.cols + (col + pcol);
						int ptrn_index = prow * search_ptrn.cols + pcol;

						double diff = pSearch[search_index] - pPtrn[ptrn_index];
						TM_SQDIFF += (diff * diff);
					}
				}
				double ptrnSQ = 0., searchSQ = 0.;
				for (size_t prow = 0; prow < search_ptrn.rows; prow++)
				{
					for (size_t pcol = 0; pcol < search_ptrn.cols; pcol++)
					{
						int search_index = (row + prow) * search_img.cols + (col + pcol);
						int ptrn_index = prow * search_ptrn.cols + pcol;
						searchSQ += pSearch[search_index] * pSearch[search_index];
						ptrnSQ += pPtrn[ptrn_index] * pPtrn[ptrn_index];
					}
				}

				//matching_img.at<double>(row, col) = TM_SQDIFF;
				//if (TM_SQDIFF == 0)
				//	ptFind.push_back(Point(col, row));

				if (ptrnSQ == 0) ptrnSQ = 1;
				TM_SQDIFF_NORMED = TM_SQDIFF / sqrt(ptrnSQ * searchSQ);
				matching_img.at<float>(row, col) = TM_SQDIFF_NORMED;

				if (TM_SQDIFF_NORMED <= 0.003)
					ptFind.push_back(Point(col, row));
			}
		}

		Mat search_img_color = cv::imread("../Build/x64/images/search_array.png", IMREAD_ANYCOLOR);
		for (size_t i = 0; i < ptFind.size(); i++)
		{
			cv::rectangle(search_img_color, Rect(ptFind[i].x, ptFind[i].y, search_ptrn.cols, search_ptrn.rows), Scalar(0, 0, 255), 3);
		}


	}


	if (1) // OpenCV + Debug = 164ms
	{
		Mat match_result;
		cv::matchTemplate(search_img, search_ptrn, match_result, TemplateMatchModes::TM_SQDIFF_NORMED);
		double minV, maxV;
		Point minLoc, maxLoc, matchLoc;
		cv::minMaxLoc(match_result, &minV, &maxV, &minLoc, &maxLoc);
		matchLoc = minLoc;//TemplateMatchModes::TM_SQDIFF_NORMED
		Mat search_img_color = cv::imread("../Build/x64/images/search_array.png", IMREAD_ANYCOLOR);
		cv::rectangle(search_img_color, Rect(matchLoc.x, matchLoc.y, search_ptrn.cols, search_ptrn.rows), Scalar(0, 0, 255), 3);

		Mat match_bin;
		double match_threshold = 0.003;
		threshold(match_result, match_bin, match_threshold, 255, ThresholdTypes::THRESH_BINARY_INV);

		match_bin.convertTo(match_bin, CV_8UC1);
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(match_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		for (size_t i = 0; i < contours.size(); i++)
		{
			RotatedRect rt = minAreaRect(contours[i]);
			cv::rectangle(search_img_color, Rect(rt.center.x, rt.center.y, search_ptrn.cols, search_ptrn.rows), Scalar(0, 0, 255), 3);
		}
	}

	_bShowDebug = true;
	_bShowResult = true;

	Invalidate(FALSE);
	return 0;
}
int COpenCVAppGUIDlg::OnInspMatchingWally()
{
	_bShowDebug = _bShowResult = false;

	Mat search_img = cv::imread("../Build/x64/images/search_wally.png", IMREAD_GRAYSCALE);
	Mat search_ptrn = cv::imread("../Build/x64/images/search_ptrn.png", IMREAD_GRAYSCALE);
	Mat matching_img = Mat::zeros(search_img.size(), CV_64F);
	//Mat matching_img = search_img.clone();
	//matching_img = 0; 로도 쓸 수 있음

	if (0)//C++_Debug_Performance : 72s
	{
		Mat matching_img = Mat::zeros(search_img.size(), CV_64F);

		vector<Point> ptFind; ptFind.clear();
		//pattern matching
		for (size_t row = 0; row < search_img.rows - search_ptrn.rows; row++)
		{
			for (size_t col = 0; col < search_img.cols - search_ptrn.cols; col++)
			{
				uchar* pSearch = search_img.data;
				uchar* pPtrn = search_ptrn.data;//5x2
				// * * * * *
				// * * * * *

				double TM_SQDIFF = 0.0;
				double TM_SQDIFF_NORMED = 0.0;
				for (size_t prow = 0; prow < search_ptrn.rows; prow++)
				{
					for (size_t pcol = 0; pcol < search_ptrn.cols; pcol++)
					{
						int search_index = (row + prow) * search_img.cols + (col + pcol);
						int ptrn_index = prow * search_ptrn.cols + pcol;

						double diff = pSearch[search_index] - pPtrn[ptrn_index];
						TM_SQDIFF += (diff * diff);

						//diff = diff* diff;
						//matching_img.at<double>(row + prow, col + pcol) = diff;

					}
				}
				double ptrnSQ = 0., searchSQ = 0.;
				for (size_t prow = 0; prow < search_ptrn.rows; prow++)
				{
					for (size_t pcol = 0; pcol < search_ptrn.cols; pcol++)
					{
						int search_index = (row + prow) * search_img.cols + (col + pcol);
						int ptrn_index = prow * search_ptrn.cols + pcol;
						searchSQ += pSearch[search_index] * pSearch[search_index];
						ptrnSQ += pPtrn[ptrn_index] * pPtrn[ptrn_index];
					}
				}

				//matching_img.at<double>(row, col) = TM_SQDIFF;
				if (TM_SQDIFF == 0)
					ptFind.push_back(Point(col, row));
				if (ptrnSQ == 0) ptrnSQ = 1;
				TM_SQDIFF_NORMED = TM_SQDIFF / sqrt(ptrnSQ * searchSQ);
				matching_img.at<double>(row, col) = TM_SQDIFF_NORMED;
			}
		}

		Mat search_img_color = cv::imread("../Build/x64/images/search_wally.png", IMREAD_ANYCOLOR);
		for (size_t i = 0; i < ptFind.size(); i++)
		{
			cv::rectangle(search_img_color, Rect(ptFind[i].x, ptFind[i].y, search_ptrn.cols, search_ptrn.rows), Scalar(0, 0, 255), 3);
		}


	}

	if (1) // OpenCV + Debug = 164ms
	{
		Mat match_result;
		cv::matchTemplate(search_img, search_ptrn, match_result, TemplateMatchModes::TM_SQDIFF_NORMED);
		double minV, maxV;
		Point minLoc, maxLoc, matchLoc;
		cv::minMaxLoc(match_result, &minV, &maxV, &minLoc, &maxLoc);
		matchLoc = minLoc;//TemplateMatchModes::TM_SQDIFF_NORMED
		Mat search_img_color = cv::imread("../Build/x64/images/search_wally.png", IMREAD_ANYCOLOR);
		cv::rectangle(search_img_color, Rect(matchLoc.x, matchLoc.y, search_ptrn.cols, search_ptrn.rows), Scalar(255, 0, 0), 3);
	}

	_bShowDebug = true;
	_bShowResult = true;

	Invalidate(FALSE);
	return 0;
}
int COpenCVAppGUIDlg::OnInspMatchingZoom()
{	
	_bShowDebug = _bShowResult = false;

	Mat search_img = cv::imread("../Build/x64/images/search_array.png", IMREAD_GRAYSCALE);
	Mat search_img_color = cv::imread("../Build/x64/images/search_array.png", IMREAD_ANYCOLOR);
	for (double zoom = 1.0; zoom < 2.0; zoom += 0.01) {
		Mat search_ptrn = cv::imread("../Build/x64/images/search_ptrn_rect_small.png", IMREAD_GRAYSCALE);
		//Mat matching_img = search_img.clone();
		//matching_img = 128;
		//Mat matching_img(search_img.size(), CV_64F,Scalar(128,128,128));
		resize(search_ptrn, search_ptrn, Size(search_ptrn.cols * zoom, search_ptrn.rows * zoom), 0, 0, InterpolationFlags::INTER_AREA);
		Mat match_result;
		Mat match100;
		cv::matchTemplate(search_img, search_ptrn, match_result, TemplateMatchModes::TM_CCORR_NORMED);
		vector<Point> matchLoc;
		//cv::minMaxLoc(match_result, &minV, &maxV, &minLoc, &maxLoc);
		match100 = match_result * 100;
		for (int row = 0; row < match_result.rows; row++) {
			for (int col = 0; col < match_result.cols; col++) {
				if (match100.at<float>(row, col) >= 99.545) {
					matchLoc.push_back(Point(col, row));
				}
			}
		}//TemplateMatchModes::TM_SQDIFF_NORMED

		if (matchLoc.size() == 6) {
			for (int i = 0; i < matchLoc.size(); i++) {
				cv::rectangle(search_img_color, Rect(matchLoc[i].x, matchLoc[i].y, search_ptrn.cols, search_ptrn.rows), Scalar(0, 0, 255), 3);
			}
			break;
		}
		else {
			matchLoc.clear();
		}
	}
	_bShowDebug = _bShowResult = true;

	Invalidate(FALSE);
	return 0;

}

void COpenCVAppGUIDlg::AddString(LPCSTR lpszLog)
{
	SendMessage(WM_ADD_STRING, 0, (LPARAM)lpszLog);
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
