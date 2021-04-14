
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
	ON_COMMAND(IDM_CONST_ADD, &CSN2019110701View::OnConstAdd)
	ON_COMMAND(IDM_CONST_SUB, &CSN2019110701View::OnConstSub)
	ON_COMMAND(IDM_CONST_MUL, &CSN2019110701View::OnConstMul)
	ON_COMMAND(IDM_CONST_DIV, &CSN2019110701View::OnConstDiv)
	ON_COMMAND(IDM_FRM_ADD, &CSN2019110701View::OnFrmAdd)
	ON_COMMAND(IDM_FRM_SUB, &CSN2019110701View::OnFrmSub)
	ON_COMMAND(IDM_FRM_MUL, &CSN2019110701View::OnFrmMul)
	ON_COMMAND(IDM_LUT_MUL, &CSN2019110701View::OnLutMul)
END_MESSAGE_MAP()

// CSN2019110701View 생성/소멸

CSN2019110701View::CSN2019110701View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

	//2021.04.13
	height = width = 256;
	int rwsize = (((width * 8) + 31) / 32 * 4); //영상 폭은 항상 4바이트의 배수여야 함

	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

	BmInfo->bmiHeader.biBitCount = 8;
	BmInfo->bmiHeader.biClrImportant = 256;
	BmInfo->bmiHeader.biClrUsed = 256;
	BmInfo->bmiHeader.biCompression = 0;
	BmInfo->bmiHeader.biHeight = height;
	BmInfo->bmiHeader.biPlanes = 1;
	BmInfo->bmiHeader.biSize = 40;
	BmInfo->bmiHeader.biSizeImage = rwsize * height;
	BmInfo->bmiHeader.biWidth = width;
	BmInfo->bmiHeader.biXPelsPerMeter = 0;
	BmInfo->bmiHeader.biYPelsPerMeter = 0;
	for (int i = 0; i < 256; i++) //palette number is 256
	{
		BmInfo->bmiColors[i].rgbRed =
			BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbBlue = i;
		BmInfo->bmiColors[i].rgbReserved = 0;
	}
}

CSN2019110701View::~CSN2019110701View()
{
	//2021.04.13 
	free(BmInfo);
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
	
	//2021.04.13
	//배열을 아래위가 반전된 영태로 만든다. 원 영상(m_InImg)의 화면출력
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) m_RevImg[i][j] = pDoc->m_InImg[height - i - 1][j];

	SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height,
		0, 0, 0, height, m_RevImg, BmInfo, DIB_RGB_COLORS);

	//처리한 결과영상(m_OutImg)의 화면출력을 위한 부분
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) m_RevImg[i][j] = pDoc->m_OutImg[height - i - 1][j];

	SetDIBitsToDevice(pDC->GetSafeHdc(), 300, 0, width, height,
		0, 0, 0, height, m_RevImg, BmInfo, DIB_RGB_COLORS);


	/*
	if (!pDoc)
  	    return; 


	//2021.04.06
	
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			unsigned char InVal = pDoc->m_InImg[i][j];
			unsigned char OutVal = pDoc->m_OutImg[i][j];
			pDC->SetPixel(j, i, RGB(InVal, InVal, InVal)); 
			pDC->SetPixel(j + 300, i, RGB(OutVal, OutVal, OutVal));
		}
	}
	*/
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
	//2021.04.06
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


	//2021.04.06
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++)
			pDoc->m_OutImg[i][j] = 255 - pDoc->m_InImg[i][j];
	}

	Invalidate(FALSE);
}




void CSN2019110701View::OnConstAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//2021.04.13
	CSN2019110701Doc* pDoc = GetDocument();  //도큐멘트 클래스를 참조하기 위해
	ASSERT_VALID(pDoc);  //인스턴스 주소를 가져옴

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int tempVal = pDoc->m_InImg[i][j] + 60; //더할값은 60
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}

	Invalidate(FALSE); //화면 갱신
}


void CSN2019110701View::OnConstSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//2021.04.13
	CSN2019110701Doc* pDoc = GetDocument();  //도큐멘트 클래스를 참조하기 위해
	ASSERT_VALID(pDoc);  //인스턴스 주소를 가져옴

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int tempVal = pDoc->m_InImg[i][j] - 60; 
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}

	Invalidate(FALSE); //화면 갱신
}


void CSN2019110701View::OnConstMul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

    //2021.04.13
	CSN2019110701Doc* pDoc = GetDocument();  //도큐멘트 클래스를 참조하기 위해
	ASSERT_VALID(pDoc);  //인스턴스 주소를 가져옴

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int tempVal = (int)(pDoc->m_InImg[i][j]*1.4); 
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}

	Invalidate(FALSE); //화면 갱신
}


void CSN2019110701View::OnConstDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//2021.04.13
	CSN2019110701Doc* pDoc = GetDocument();  //도큐멘트 클래스를 참조하기 위해
	ASSERT_VALID(pDoc);  //인스턴스 주소를 가져옴

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int tempVal = (int)(pDoc->m_InImg[i][j] / 1.4);
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}

	Invalidate(FALSE); //화면 갱신
}


void CSN2019110701View::OnFrmAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//2021.04.13
	CSN2019110701Doc* pDoc = GetDocument();  //도큐멘트 클래스를 참조하기 위해
	ASSERT_VALID(pDoc);  //인스턴스 주소를 가져옴

	pDoc->TwoImgLoad(); //더하기 연산을 할 두 영상을 입력한다.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			int tempVal = pDoc->m_InImg1[i][j] + pDoc->m_InImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE); //화면갱신
}


void CSN2019110701View::OnFrmSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//2021.04.13
	CSN2019110701Doc* pDoc = GetDocument();  //도큐멘트 클래스를 참조하기 위해
	ASSERT_VALID(pDoc);  //인스턴스 주소를 가져옴

	pDoc->TwoImgLoad(); //빼기 연산을 할 두 영상을 입력한다.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			int tempVal = (abs)(pDoc->m_InImg1[i][j] - pDoc->m_InImg2[i][j]);
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE); //화면갱신
}


void CSN2019110701View::OnFrmMul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//2021.04.13
	CSN2019110701Doc* pDoc = GetDocument();  //도큐멘트 클래스를 참조하기 위해
	ASSERT_VALID(pDoc);  //인스턴스 주소를 가져옴

	pDoc->TwoImgLoad(); //곱연산을 할 두 영상을 입력한다.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			int tempVal = pDoc->m_InImg1[i][j] & pDoc->m_InImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE); //화면갱신
}


void CSN2019110701View::OnLutMul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//2021.04.13
	CSN2019110701Doc* pDoc = GetDocument();  //도큐멘트 클래스를 참조하기 위해
	ASSERT_VALID(pDoc);  //인스턴스 주소를 가져옴

	unsigned char LUT[256];//LUT로 사용할 메모리를 선언

	//LUT값을 계산한다
	for (int i = 0; i < 256; i++) {
		int temp = (int)((float)i*1.4);
		LUT[i] = temp > 255 ? 255 : temp;
	}

	//LUT를 통하여 영상을 처리한다
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pDoc->m_OutImg[i][j] = LUT[pDoc->m_InImg[i][j]];
		}
	}
	Invalidate(FALSE); //화면 갱신
}
