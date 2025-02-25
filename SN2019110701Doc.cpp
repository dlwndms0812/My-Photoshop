﻿
// SN2019110701Doc.cpp: CSN2019110701Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SN2019110701.h"
#endif

#include "SN2019110701Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSN2019110701Doc

IMPLEMENT_DYNCREATE(CSN2019110701Doc, CDocument)

BEGIN_MESSAGE_MAP(CSN2019110701Doc, CDocument)
END_MESSAGE_MAP()


// CSN2019110701Doc 생성/소멸

CSN2019110701Doc::CSN2019110701Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CSN2019110701Doc::~CSN2019110701Doc()
{
}

BOOL CSN2019110701Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CSN2019110701Doc serialization

void CSN2019110701Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.

		//2021.04.06
		ar.Write(m_OutImg, 256 * 256);
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		CFile *infile = ar.GetFile(); 
		if (infile->GetLength() != 256 * 256)  {
			AfxMessageBox((LPCTSTR)"파일 크기 오류");
			return;
		}
		ar.Read(m_InImg, (UINT)infile->GetLength());
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CSN2019110701Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CSN2019110701Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSN2019110701Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSN2019110701Doc 진단

#ifdef _DEBUG
void CSN2019110701Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSN2019110701Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSN2019110701Doc 명령


void CSN2019110701Doc::TwoImgLoad()
{
	// TODO: 여기에 구현 코드 추가.

	//2021.04.13
	CFile file;
	CFileDialog opendlg1(TRUE); //공통 대화상자(첫 번째 파일 오픈)
	if (opendlg1.DoModal() == IDOK)
	{
		//첫 번째 이미지 읽기
		file.Open(opendlg1.GetPathName(), CFile::modeRead);  //GetFileName는 윈도우xp, GetPathName는 윈도우7
		file.Read(m_InImg1, sizeof(m_InImg1));
		file.Close();
	}

	CFileDialog opendlg2(TRUE); //공통 대화상자(두 번째 파일 오픈)
	if (opendlg2.DoModal() == IDOK)
	{
		//두 번째 이미지 읽기
		file.Open(opendlg2.GetPathName(), CFile::modeRead);
		file.Read(m_InImg2, sizeof(m_InImg2));
		file.Close();
	}
}
