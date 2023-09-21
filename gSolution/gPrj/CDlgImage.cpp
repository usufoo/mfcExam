// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "gPrj.h"
#include "afxdialogex.h"
#include "CDlgImage.h"
#define COLOR_RED	RGB(0xff, 0x00, 0x00)
#define COLOR_GREEN	RGB(0x00, 0xff, 0x00)


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{

}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_UP_PARENT, &CDlgImage::OnBnClickedBtnUpParent)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CDlgImage::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기
#include "gPrjDlg.h"
void CDlgImage::OnBnClickedBtnUpParent()
{
	static int n = 100;
	CgPrjDlg* pDlg = (CgPrjDlg*)m_pParent;
	pDlg->callFunc(n++);
}

BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 640, 480);
	InitImage();
	//AfxMessageBox(_T("ready?"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgImage::InitImage()
{
	int nWidth = 4096*5;
	int nHeight = 4096*5;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_image.SetColorTable(0, 256, rgb);
		}
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}

void CDlgImage::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}

void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_image) {
		m_image.Draw(dc, 0, 0);
	}
	drawData(&dc);
}

void CDlgImage::drawData(CDC* pDC)
{
	CRect rect;  // 화면에 그릴 사각형의 크기와 특성을 설정하기 위한 변수를 생성
	CPen pen;  // 그릴 선의 특성을 설정하기 위한 펜 객체를 생성
	pen.CreatePen(PS_SOLID, 2, COLOR_RED); // 빨간색 펜, 2 픽셀 두께
	CPen* pOldPen = pDC->SelectObject(&pen); // 현재 펜을 저장

	for (int i = 0; i < m_nDataCount; i++) {  // 데이터를 기반으로 화면에 원(Ellipse)을 그림
		rect.SetRect(m_ptData[i], m_ptData[i]);  // 현재 데이터 위치를 기준으로 사각형을 생성
		rect.InflateRect(1, 1);  // 사각형을 약간 확장시켜서 원처럼 보이도록 함
		pDC->Ellipse(rect);  // 사각형을 화면에 그려서 원 모양 생성
	}

	pDC->SelectObject(pOldPen);  // 펜 복원
}

