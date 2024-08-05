
// MfcStartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MfcStart.h"
#include "MfcStartDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
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


// CMfcStartDlg 대화 상자



CMfcStartDlg::CMfcStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSTART_DIALOG, pParent)
	, m_nptXStart(0)
	, m_nptYStart(0)
	, m_nptXEnd(0)
	, m_nptYEnd(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ST_PIC_DRAW, m_stPicDraw);
	DDX_Text(pDX, IDC_ED_PTX_START, m_nptXStart);
	DDX_Text(pDX, IDC_ED_PTY_START, m_nptYStart);
	DDX_Text(pDX, IDC_ED_PTX_END, m_nptXEnd);
	DDX_Text(pDX, IDC_ED_PTY_END, m_nptYEnd);

	DDV_MinMaxInt(pDX, m_nptXStart, 0, m_szPicDraw.cx);
	DDV_MinMaxInt(pDX, m_nptYStart, 0, m_szPicDraw.cx);
	DDV_MinMaxInt(pDX, m_nptXEnd, 0, m_szPicDraw.cx);
	DDV_MinMaxInt(pDX, m_nptYEnd, 0, m_szPicDraw.cx);
}

BEGIN_MESSAGE_MAP(CMfcStartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMfcStartDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMfcStartDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMfcStartDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CMfcStartDlg 메시지 처리기

BOOL CMfcStartDlg::OnInitDialog()
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
	CRect rtPicArea;
	m_stPicDraw.GetClientRect(rtPicArea);

	m_szPicDraw.cx = rtPicArea.Width();
	m_szPicDraw.cy = rtPicArea.Height();

	m_nBpp = GetDeviceCaps(GetDC()->m_hDC, BITSPIXEL) == 8 ? 8 : 24;

	cout << "Pic Width : " << m_szPicDraw.cx << ", Height : " << m_szPicDraw.cy << ", BPP : " << m_nBpp << endl;

	srand(GetTickCount64());

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMfcStartDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMfcStartDlg::OnPaint()
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
HCURSOR CMfcStartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMfcStartDlg::OnBnClickedBtnDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_ImgDisp != nullptr) {
		m_ImgDisp.Destroy();
	}

	m_ptLoadImgCenter.x = -1;
	m_ptLoadImgCenter.y = -1;

	m_ImgDisp.Create(m_szPicDraw.cx, -m_szPicDraw.cy, m_nBpp);

	int iLim = min(m_szPicDraw.cx, m_szPicDraw.cy) / 5;

	m_nRadius = rand() % iLim + 5;			// 최소 반지름은 5가 되게 한다.

	cout << "Gen Radius is " << m_nRadius << endl;

	if (m_nBpp == 8) {
		static RGBQUAD rgb[256];

		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_ImgDisp.SetColorTable(0, 256, rgb);
		}
	}

	PBYTE pFm = (PBYTE)m_ImgDisp.GetBits();
	memset(pFm, 0xff, (((m_szPicDraw.cx * m_nBpp) + 31 & ~31) >> 3) * m_szPicDraw.cy);

	UpdateData();

	m_nptXStart = m_nptXStart < m_nRadius ? m_nRadius : m_nptXStart;
	m_nptXStart = m_nptXStart > (m_szPicDraw.cx - m_nRadius) ? m_szPicDraw.cx - m_nRadius : m_nptXStart;

	m_nptYStart = m_nptYStart < m_nRadius ? m_nRadius : m_nptYStart;
	m_nptYStart = m_nptYStart > (m_szPicDraw.cy - m_nRadius) ? m_szPicDraw.cy - m_nRadius : m_nptYStart;

	UpdateData(false);

	DrawCircle(pFm, m_nptXStart, m_nptYStart, m_nRadius, RGB(80, 80, 80));

	UpdateDisplay();
}

void CMfcStartDlg::DrawCircle(PBYTE pFm, int x, int y, int nRadius, COLORREF color)
{
	int nCenterX = x;
	int nCenterY = y;
	int nPitch = m_ImgDisp.GetPitch();

	BYTE bGray, bRed, bGreen, bBlue;

	switch (m_nBpp / 8) {
	case 1:
		bGray = (GetRValue(color) * 30
			+ GetGValue(color) * 59
			+ GetBValue(color) * 11) / 100;
		break;
	case 3:
	default:
		bRed = GetRValue(color);
		bGreen = GetGValue(color);
		bBlue = GetBValue(color);
		break;
	}

	for (int j = y - nRadius; j < y + nRadius; j++) {
		for (int i = x - nRadius; i < x + nRadius; i++) {
			if (m_nBpp / 8 == 1) {
				if (IsInCircle(i, j, nCenterX, nCenterY, nRadius)) {
					pFm[j * nPitch + i] = bGray;
				}
			}
			else {
				if (IsInCircle(i, j, nCenterX, nCenterY, nRadius)) {
					pFm[j * nPitch + i * (m_nBpp / 8) + 0] = bRed;
					pFm[j * nPitch + i * (m_nBpp / 8) + 1] = bGreen;
					pFm[j * nPitch + i * (m_nBpp / 8) + 2] = bBlue;
				}
			}
			
		}
	}
}

bool CMfcStartDlg::IsInCircle(int x, int y, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = (double)x - nCenterX;
	double dY = (double)y - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}


void CMfcStartDlg::OnBnClickedBtnAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nRadius < 1) {
		AfxMessageBox(_T("Draw 버튼을 먼저 눌러서 원을 먼저 생성하여야 합니다."));
		return;
	}

	m_ptLoadImgCenter.x = -1;
	m_ptLoadImgCenter.y = -1;

	UpdateData();

	m_nptXEnd = m_nptXEnd < m_nRadius ? m_nRadius : m_nptXEnd;
	m_nptXEnd = m_nptXEnd > (m_szPicDraw.cx - m_nRadius) ? m_szPicDraw.cx - m_nRadius : m_nptXEnd;

	m_nptYEnd = m_nptYEnd < m_nRadius ? m_nRadius : m_nptYEnd;
	m_nptYEnd = m_nptYEnd > (m_szPicDraw.cy - m_nRadius) ? m_szPicDraw.cy - m_nRadius : m_nptYEnd;

	UpdateData(false);

	int iMaxCnt = max(abs(m_nptXStart - m_nptXEnd), abs(m_nptYStart - m_nptYEnd));
	
	for (int i = 0; i < iMaxCnt; i++) {
		MoveCircle(i == 0, iMaxCnt);
		Sleep(10);
	}
}

void CMfcStartDlg::MoveCircle(bool bInit, int nMax)
{
	static double dSttX = 0;
	static double dSttY = 0;
	static int nImgCnt = 0;

	PBYTE pFm = (PBYTE)m_ImgDisp.GetBits();

	if (bInit) {
		memset(pFm, 0xff, (((m_szPicDraw.cx * m_nBpp) + 31 & ~31) >> 3) * m_szPicDraw.cy);
		dSttX = m_nptXStart;
		dSttY = m_nptYStart;
		nImgCnt = 0;
	}

	double dXAdd = (double)abs(m_nptXStart - m_nptXEnd) / nMax;
	double dYAdd = (double)abs(m_nptYStart - m_nptYEnd) / nMax;

	int iXAdd = m_nptXStart < m_nptXEnd ? 1 : -1;
	int iYAdd = m_nptYStart < m_nptYEnd ? 1 : -1;

	dXAdd *= iXAdd;
	dYAdd *= iYAdd;

	DrawCircle(pFm, dSttX, dSttY, m_nRadius, RGB(255, 255, 255));
	DrawCircle(pFm, dSttX += dXAdd, dSttY += dYAdd, m_nRadius, RGB(80, 80, 80));

	UpdateDisplay();

	CString strFile;
	strFile.Format(_T(".\\image%d.jpg"), nImgCnt);
	m_ImgDisp.Save(strFile);
	nImgCnt++;
}

void CMfcStartDlg::UpdateDisplay()
{
	CDC* pPIcDC = m_stPicDraw.GetWindowDC();
	m_ImgDisp.Draw(pPIcDC->m_hDC, 0, 0);

	if (m_ptLoadImgCenter.x != -1 && m_ptLoadImgCenter.y != -1) {
		CPen pen;
		pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		CPen* oldPen = pPIcDC->SelectObject(&pen);
		const int LINE_LENGTH = 4;
		CPoint ptLine1 = m_ptLoadImgCenter;
		CPoint ptLine2 = m_ptLoadImgCenter;

		ptLine1.x -= LINE_LENGTH;
		ptLine1.y -= LINE_LENGTH;

		ptLine2.x += LINE_LENGTH;
		ptLine2.y += LINE_LENGTH;

		pPIcDC->MoveTo(ptLine1);
		pPIcDC->LineTo(ptLine2);

		ptLine1 = m_ptLoadImgCenter;
		ptLine2 = m_ptLoadImgCenter;

		ptLine1.x += LINE_LENGTH;
		ptLine1.y -= LINE_LENGTH;

		ptLine2.x -= LINE_LENGTH;
		ptLine2.y += LINE_LENGTH;

		pPIcDC->MoveTo(ptLine1);
		pPIcDC->LineTo(ptLine2);

		pPIcDC->SelectObject(oldPen);

		ptLine1 = m_ptLoadImgCenter;

		CString strPos;
		strPos.Format(_T("(%d, %d)"), m_ptLoadImgCenter.x, m_ptLoadImgCenter.y);
		int nMaxCount = 0;
		SIZE szSize;
		GetTextExtentExPoint(pPIcDC->m_hDC, strPos, strPos.GetLength(), m_szPicDraw.cx, &nMaxCount, nullptr, &szSize);

		ptLine1.x += LINE_LENGTH;
		ptLine1.y += LINE_LENGTH;

		if (ptLine1.x + szSize.cx > m_szPicDraw.cx) {
			ptLine1.x = m_ptLoadImgCenter.x - LINE_LENGTH - szSize.cx;
		}

		if (ptLine1.y + szSize.cy > m_szPicDraw.cy) {
			ptLine1.y = m_ptLoadImgCenter.y - LINE_LENGTH - szSize.cy;
		}

		pPIcDC->SetBkMode(TRANSPARENT);
		pPIcDC->TextOut(ptLine1.x, ptLine1.y, strPos);
	}
}


void CMfcStartDlg::OnBnClickedBtnOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, .JPG) | *.BMP;*.JPG;*.bmp;*.jpg;|모든파일(*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal()) {
		CString pathName = dlg.GetPathName();
		
		if (m_ImgDisp != nullptr) {
			m_ImgDisp.Destroy();
		}

		m_ImgDisp.Load(pathName);

		FindCircleCenter();

		UpdateDisplay();
	}
	else {
		m_ptLoadImgCenter.x = -1;
		m_ptLoadImgCenter.y = -1;
	}
}

void CMfcStartDlg::FindCircleCenter()
{
	CImage invert_image;

	invert_image.Create(m_ImgDisp.GetWidth(), m_ImgDisp.GetHeight(), 8);

	static RGBQUAD rgb[256];

	for (int i = 0; i < 256; i++) {
		rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		invert_image.SetColorTable(0, 256, rgb);
	}

	COLORREF temp_color;

	for (int y = 0; y < m_ImgDisp.GetHeight(); y++) {
		for (int x = 0; x < m_ImgDisp.GetWidth(); x++) {
			temp_color = m_ImgDisp.GetPixel(x, y);

			BYTE bRed = GetRValue(temp_color);
			BYTE bGreen = GetGValue(temp_color);
			BYTE bBlue = GetBValue(temp_color);

			BYTE bInvertRed = 255 - bRed;
			BYTE bInvertGreen = 255 - bGreen;
			BYTE bInvertBlue = 255 - bBlue;

			invert_image.SetPixel(x, y, RGB(bInvertRed, bInvertGreen, bInvertBlue));
		}
	}

	PBYTE pFm = (PBYTE)invert_image.GetBits();

	int nPitch = invert_image.GetPitch();
	int nMinX = -1, nMaxX = -1;
	int nMinY = -1, nMaxY = -1;

	for (int y = 0; y < invert_image.GetHeight(); y++) {
		for (int x = 0; x < invert_image.GetWidth(); x++) {
			if (pFm[y * nPitch + x] > 0) {
				if (nMinX == -1) {
					nMinX = x;
					nMaxX = x;
				}
				else if (nMinX > x) {
					nMinX = x;
				}
				else if (nMaxX < x) {
					nMaxX = x;
				}

				if (nMinY == -1) {
					nMinY = y;
					nMaxY = y;
				}
				else if (nMinY > y) {
					nMinY = y;
				}
				else if (nMaxY < y) {
					nMaxY = y;
				}
			}
		}
	}

	m_ptLoadImgCenter.x = nMinX + abs(nMaxX - nMinX) / 2;
	m_ptLoadImgCenter.y = nMinY + abs(nMaxY - nMinY) / 2;
}
