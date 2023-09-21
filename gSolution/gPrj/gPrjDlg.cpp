
// gPrjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "gPrj.h"
#include "gPrjDlg.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


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


// CgPrjDlg 대화 상자



CgPrjDlg::CgPrjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GPRJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON1, &CgPrjDlg::OnBnClickedButton1)
//ON_BN_CLICKED(IDC_BTN_DLG, &CgPrjDlg::OnBnClickedBtnDlg)
ON_WM_DESTROY()
//ON_BN_CLICKED(IDOK, &CgPrjDlg::OnBnClickedOk)
ON_BN_CLICKED(IDC_BTN_TEST, &CgPrjDlg::OnBnClickedBtnTest)
ON_BN_CLICKED(IDC_BTN_PROCESS, &CgPrjDlg::OnBnClickedBtnProcess)
ON_BN_CLICKED(IDC_BTN_MAKE_PATTERN, &CgPrjDlg::OnBnClickedBtnMakePattern)
ON_BN_CLICKED(IDC_BTN_GET_DATA, &CgPrjDlg::OnBnClickedBtnGetData)
//ON_BN_CLICKED(IDC_BTN_CIRCLE, &CgPrjDlg::OnBnClickedBtnCircle)
//ON_BN_CLICKED(IDC_BTN_CIRCLE_DATA, &CgPrjDlg::OnBnClickedBtnCircleData)
END_MESSAGE_MAP()


// CgPrjDlg 메시지 처리기

BOOL CgPrjDlg::OnInitDialog()
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
	MoveWindow(0, 0, 1280, 800);  // 1. 윈도우를 좌표 (0, 0)에서 (1280, 800)으로 이동 및 크기 조정
	m_pDlgImage = new CDlgImage;  // 2. 새로운 CDlgImage 객체를 생성합니다.
	m_pDlgImage->Create(IDD_CDlgImage, this);  // 3. CDlgImage 다이얼로그를 생성하고 현재 다이얼로그(부모 창)에 종속시킴
	m_pDlgImage->ShowWindow(SW_SHOW);  // 4. 새로 생성한 CDlgImage 다이얼로그를 화면에 표시
	//m_pDlgImage->MoveWindow(0, 0, 640, 480);  // 5. CDlgImage 다이얼로그를 좌표 (0, 0)에서 (640, 480)으로 이동 및 크기 조정

	// 두 번째 다이얼로그의 위치를 (640, 0)으로 설정하여 화면에서 오른쪽에 배치함
	m_pDlgImgResult = new CDlgImage;  // 6. 두 번째 CDlgImage 객체 생성
	m_pDlgImgResult->Create(IDD_CDlgImage, this);  // 7. 두 번째 CDlgImage 다이얼로그 생성
	m_pDlgImgResult->ShowWindow(SW_SHOW);  // 8. 두 번째 CDlgImage 다이얼로그 표시
	m_pDlgImgResult->MoveWindow(640, 0, 640, 480);  // 9. 두 번째 CDlgImage 다이얼로그 이동 및 크기 조정

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CgPrjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CgPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#include "CDlgImage.h"
//void CgPrjDlg::OnBnClickedBtnDlg()
//{
//	m_pDlgImage->ShowWindow(SW_SHOW);
//}


void CgPrjDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pDlgImage) {
		delete m_pDlgImage;
	}
	if (m_pDlgImgResult) {
		delete m_pDlgImgResult;
	}
}

void CgPrjDlg::callFunc(int n)
{
	//int nData = n;
	cout << n << endl;
}

//void CgPrjDlg::OnBnClickedOk()
//{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDialogEx::OnOK();
//}

void CgPrjDlg::OnBnClickedBtnTest()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();  // unsigned char 포인터를 사용하여 이미지 데이터에 접근
	int nWidth = m_pDlgImage->m_image.GetWidth();  // 640, 480, pitch
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);

	for (int k = 0; k < MAX_POINT; k++) {
		int x = rand() % nWidth;
		int y = rand() % nHeight;
		fm[y * nPitch + x] = rand() % 0xff;
	}

	int nIndex = 0;
	int nTh = 100;
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			if (fm[j * nPitch + i] > nTh) {
				if (m_pDlgImgResult->m_nDataCount < MAX_POINT) {
					cout << nIndex << ":" << i << "," << j << endl;
					m_pDlgImgResult->m_ptData[nIndex].x = i;
					m_pDlgImgResult->m_ptData[nIndex].y = j;
					m_pDlgImgResult->m_nDataCount = ++nIndex;
				}
			}
		}
	}
	//memset(fm, 0, 320 * 240);  // memset 함수를 사용하여 이미지 데이터를 모두 0으로 초기화
	m_pDlgImage->Invalidate();  // 화면을 무효화하여 변경 사항을 반영
	m_pDlgImgResult->Invalidate();
}

#include "CProcess.h"
#include <chrono>  // chrono 라이브러리를 포함합니다.

void CgPrjDlg::OnBnClickedBtnProcess()
{
	CProcess process;  // CProcess 클래스의 객체를 생성
	auto start = chrono::system_clock::now();  // 현재 시간을 측정하기 위해 chrono 라이브러리를 사용하는 시작 시간을 기록
	int nRet = process.getStarInfo(&m_pDlgImage->m_image, 100);  // CProcess 클래스의 getStarInfo 함수를 호출하여 이미지 분석을 수행하고, 결과를 nRet에 저장
	auto end = chrono::system_clock::now();  // 이미지 분석이 끝난 후에 다시 현재 시간을 측정하여 종료 시간을 기록
	auto millisec = chrono::duration_cast<chrono::milliseconds>(end - start);  // 시간 간격을 밀리초로 변환
	cout << nRet << "\t" << millisec.count() << "ms" << endl;  // 분석 결과(nRet)와 걸린 시간(millisec)을 출력
}


void CgPrjDlg::OnBnClickedBtnGetData()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();  // unsigned char 포인터를 사용하여 이미지 데이터에 접근
	int nWidth = m_pDlgImage->m_image.GetWidth();  // 640, 480, pitch
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	int nTh = 0x80;
	CRect rect(0, 0, nWidth, nHeight);
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	cout << dCenterX << "\t" << dCenterY << endl;
}


void CgPrjDlg::OnBnClickedBtnMakePattern()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();  // unsigned char 포인터를 사용하여 이미지 데이터에 접근
	int nWidth = m_pDlgImage->m_image.GetWidth();  // 640, 480, pitch
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);

	// 일정 영역에 대한 포인트 만들기
	CRect rect(100, 100, 200, 200);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			fm[j * nPitch + i] = rand() % 0xff;
		}
	}
	m_pDlgImage->Invalidate();
}

