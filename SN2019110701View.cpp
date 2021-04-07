
// SN2019110701View.cpp: CSN2019110701View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SN2019110701.h"
#endif

#include "SN2019110701Doc.h"
#include "SN2019110701View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSN2019110701View

IMPLEMENT_DYNCREATE(CSN2019110701View, CScrollView)

BEGIN_MESSAGE_MAP(CSN2019110701View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSN2019110701View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_REVERSE_IMG, &CSN2019110701View::OnReverseImg)
END_MESSAGE_MAP()

// CSN2019110701View 생성/소멸

CSN2019110701View::CSN2019110701View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSN2019110701View::~CSN2019110701View()
{
}

BOOL CSN2019110701View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CSN2019110701View 그리기

void CSN2019110701View::OnDraw(CDC* pDC)
{
	CSN2019110701Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
  	    return;  //이거 없어도 되나
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			unsigned char InVal = pDoc->m_InImg[i][j];
			unsigned char OutVal = pDoc->m_OutImg[i][j];
			pDC->SetPixel(j, i, RGB(InVal, InVal, InVal)); 
			pDC->SetPixel(j + 300, i, RGB(OutVal, OutVal, OutVal));
		}
	}

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CSN2019110701View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CSN2019110701View 인쇄


void CSN2019110701View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSN2019110701View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSN2019110701View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSN2019110701View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSN2019110701View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSN2019110701View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSN2019110701View 진단

#ifdef _DEBUG
void CSN2019110701View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSN2019110701View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSN2019110701Doc* CSN2019110701View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSN2019110701Doc)));
	return (CSN2019110701Doc*)m_pDocument;
}
#endif //_DEBUG


// CSN2019110701View 메시지 처리기


void CSN2019110701View::OnReverseImg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2019110701Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++)
			pDoc->m_OutImg[i][j] = 255 - pDoc->m_InImg[i][j];
	}

	Invalidate(FALSE);
}

