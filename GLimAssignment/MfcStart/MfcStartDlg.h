
// MfcStartDlg.h: 헤더 파일
//

#pragma once

class CMfcStartDlg;

typedef struct tag_ThOpenParams {
	CMfcStartDlg* pDlg;
	CString strImgPath;
} ThOpenParams, *LPThOpenParams;

// CMfcStartDlg 대화 상자
class CMfcStartDlg : public CDialogEx
{
// 생성입니다.
public:
	CMfcStartDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	typedef enum en_TargetCtrl {
		TARGET_ACTION,
		TARGET_OPEN
	} TargetCtrl;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSTART_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	SIZE m_szPicDraw;
	int m_nBpp;
	int m_nRadius;
	CPoint m_ptLoadImgCenter;

	bool m_bThreadEnable;

public:
	CStatic m_stPicDraw;
	int m_nptXStart;
	int m_nptYStart;
	int m_nptXEnd;
	int m_nptYEnd;

	CImage m_ImgDisp;
	afx_msg void OnBnClickedBtnDraw();

	void InitImgDisp(bool bResetPrevImg);
	void DrawCircle(PBYTE pFm, int x, int y, int nRadius, COLORREF color);
	bool IsInCircle(int x, int y, int nCenterX, int nCenterY, int nRadius);
	afx_msg void OnBnClickedBtnAction();
	void MoveCircle(bool bInit, int nMax);
	void UpdateDisplay(CDC* pDC);
	afx_msg void OnBnClickedBtnOpen();
	void ImgOpenProc(CString strPathName);

	static UINT ThreadAction(LPVOID pParam);
	static UINT ThreadOpen(LPVOID pParam);

	void FindCircleCenter();

	void EnableCtrlState(bool bEnable, TargetCtrl targetCtrl);
	afx_msg void OnDestroy();

	void ResetPoints();
};
