
// SN2019110701View.h: CSN2019110701View 클래스의 인터페이스
//

#pragma once


class CSN2019110701View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CSN2019110701View() noexcept;
	DECLARE_DYNCREATE(CSN2019110701View)

// 특성입니다.
public:
	CSN2019110701Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CSN2019110701View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	//2021.04.06
	afx_msg void OnReverseImg();

	//2021.04.13
	BITMAPINFO *BmInfo;
	int height;
	int width;
	unsigned char m_RevImg[256][256];
	afx_msg void OnConstAdd();
	afx_msg void OnConstSub();
	afx_msg void OnConstMul();
	afx_msg void OnConstDiv();
	afx_msg void OnFrmAdd();
	afx_msg void OnFrmSub();
	afx_msg void OnFrmMul();
	afx_msg void OnLutMul();
};

#ifndef _DEBUG  // SN2019110701View.cpp의 디버그 버전
inline CSN2019110701Doc* CSN2019110701View::GetDocument() const
   { return reinterpret_cast<CSN2019110701Doc*>(m_pDocument); }
#endif

