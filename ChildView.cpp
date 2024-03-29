
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFC_0414a.h"
#include "ChildView.h"
#include <time.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	_wallPos = 400;
	_RecRadius = 10;
	_RecCenter.SetPoint(190, 210);
	_left = false;
	_right = false;
	_up = false;
	_down = false;
	srand((unsigned int)time(NULL));
	rand_x1 = (rand() % (17 - 2 + 1) + 2) * 20 + 20;
	rand_y1 = (rand() % (17 - 2 + 1) + 2) * 20 + 20;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
	memDc.SelectObject(&bitmap);


	CBrush wallBrush(HS_DIAGCROSS, RGB(255, 0, 0));
	memDc.SelectObject(wallBrush);
	memDc.Rectangle(0, 0, _wallPos,_wallPos );
	CBrush insideBrush(RGB(255, 255, 255));
	memDc.SelectObject(insideBrush);
	memDc.Rectangle(20, 20, 380, 380);
	CBrush brush(RGB(0, 255, 0));
	memDc.SelectObject(brush);
	memDc.Rectangle(_RecCenter.x - _RecRadius, _RecCenter.y - _RecRadius, _RecCenter.x + _RecRadius, _RecCenter.y + _RecRadius);

	CFont font;
	CFont *pOldFont;
	font.CreatePointFont(300,_T("Lucida Grande Bold"));
	pOldFont = (CFont*)memDc.SelectObject(&font);
	if (_RecCenter.x > 380 || _RecCenter.x < 20 || _RecCenter.y>380 || _RecCenter.y < 20) {
		memDc.TextOut(150, 210, _T("Game Over"));
		_left = false;
		_right = false;
		_up = false;
		_down = false;
	}
	CBrush seed(RGB(255, 102, 102));
	memDc.SelectObject(seed);
	if (rand_x1<_RecCenter.x&&rand_y1<_RecCenter.y&&rand_x1 + 20>_RecCenter.x&&rand_y1 + 20>_RecCenter.y)
	{
		rand_x1 = (rand() % (17 - 2 + 1) + 2) * 20 + 20;
		rand_y1 = (rand() % (17 - 2 + 1) + 2) * 20 + 20;
		
	}
	memDc.Ellipse(rand_x1, rand_y1, rand_x1 + 20, rand_y1 + 20);
	dc.BitBlt(0, 0, rect.right, rect.bottom, &memDc, 0, 0, SRCCOPY);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 0&&_left==true) {
		_RecCenter.x -= 20;
	}
	else if (nIDEvent == 1&&_right==true) {
		_RecCenter.x += 20;
	}
	else if (nIDEvent == 2&&_up==true) {
		_RecCenter.y -= 20;
	}
	else if (nIDEvent == 3&&_down==true) {
		_RecCenter.y += 20;
	}
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	//SetTimer(0, 30, NULL);
	return 0;
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_LEFT:
		SetTimer(0, 80, NULL);
		_left = true;
		_right = false;
		_up = false;
		_down = false;
		break;
	case VK_RIGHT:
		SetTimer(1, 80, NULL);
		_right = true;
		_left = false;
		_up = false;
		_down = false;
		break;
	case VK_UP:
		SetTimer(2, 80, NULL);
		_up = true;
		_left = false;
		_right = false;
		_down = false;
		break;
	case VK_DOWN:
		SetTimer(3, 80, NULL);
		_down = true;
		_left = false;
		_right = false;
		_up = false;
		break;
	case VK_SPACE:
		_RecCenter.SetPoint(190, 210);
		rand_x1 = (rand() % (17 - 2 + 1) + 2) * 20 + 20;
		rand_y1 = (rand() % (17 - 2 + 1) + 2) * 20 + 20;
	}
	Invalidate();
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
	//return CWnd::OnEraseBkgnd(pDC);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CWnd::OnLButtonDown(nFlags, point);
}
