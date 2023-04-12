
// OpenCVAppGUIDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "OpenCVAppGUI.h"
#include "OpenCVAppGUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
}

BEGIN_MESSAGE_MAP(COpenCVAppGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD1, &COpenCVAppGUIDlg::OnBnClickedBtnLoad1)
	ON_BN_CLICKED(IDC_BTN_SAVE, &COpenCVAppGUIDlg::OnBnClickedBtnSave)
	ON_STN_CLICKED(IDC_PICTURE, &COpenCVAppGUIDlg::OnStnClickedPicture)
	ON_BN_CLICKED(IDC_BTN_RESULT, &COpenCVAppGUIDlg::OnBnClickedBtnResult)
	ON_STN_CLICKED(IDC_VIEWPICTURE, &COpenCVAppGUIDlg::OnStnClickedViewpicture)
	ON_BN_CLICKED(IDC_BTN_RESET, &COpenCVAppGUIDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_CHECK_BTN, &COpenCVAppGUIDlg::OnBnClickedCheckBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &COpenCVAppGUIDlg::OnBnClickedCancelBtn)
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

	//ShowWindow(SW_MAXIMIZE);
	//ShowWindow(SW_MINIMIZE);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_PICTURE)->GetWindowRect(_rtImageView);
	ScreenToClient(_rtImageView);
	GetDlgItem(IDC_VIEWPICTURE)->GetWindowRect(_rtImageView2);
	ScreenToClient(_rtImageView2);
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
		if (!_imageView.IsNull())
		{
			dc.SetStretchBltMode(COLORONCOLOR);
			_imageView.Draw(dc, _rtImageView);

		}
		if (!_imageView2.IsNull())
		{
			dc.SetStretchBltMode(COLORONCOLOR);
			_imageView2.Draw(dc, _rtImageView2);

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


void COpenCVAppGUIDlg::OnBnClickedBtnLoad1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	string fileName = "jetson.bmp";
	Mat img = cv::imread(fileName, IMREAD_GRAYSCALE);
	int width = img.cols;
	int height = img.rows;
	unsigned char* pData = img.data;
	int channel = img.channels();

	if (_imageView.IsNull())
	{
		_imageView.Load(fileName.c_str());
		InvalidateRect(_rtImageView, FALSE);
	}
	AfxMessageBox("이미지가 Load되었습니다.");
}



void COpenCVAppGUIDlg::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	string fileName = "jetson_clone.bmp";
	_imageView.Save(fileName.c_str());
	AfxMessageBox("이미지가 Save되었습니다.");
}


void COpenCVAppGUIDlg::OnStnClickedPicture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void COpenCVAppGUIDlg::OnBnClickedBtnResult()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	string fileName = "jetson.bmp";
	Mat img = cv::imread(fileName, IMREAD_GRAYSCALE);
	int width = img.cols;
	int height = img.rows;
	unsigned char* pData = img.data;
	int channel = img.channels();

	if (_imageView2.IsNull())
	{
		_imageView2.Load(fileName.c_str());
		InvalidateRect(_rtImageView2, FALSE);
	}
	AfxMessageBox("이미지 Result를 나타냅니다.");

}


void COpenCVAppGUIDlg::OnStnClickedViewpicture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void COpenCVAppGUIDlg::OnBnClickedBtnReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	_imageView2.Destroy();
	InvalidateRect(_rtImageView2, TRUE);
	AfxMessageBox("이미지를 Reset합니다.");
}


void COpenCVAppGUIDlg::OnBnClickedCheckBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void COpenCVAppGUIDlg::OnBnClickedCancelBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
