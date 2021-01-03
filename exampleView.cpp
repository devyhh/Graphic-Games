// exampleView.cpp : implementation of the CExampleView class
//

#include "stdafx.h"
#include "example.h"

#include "exampleDoc.h"
#include "exampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExampleView

IMPLEMENT_DYNCREATE(CExampleView, CView)

BEGIN_MESSAGE_MAP(CExampleView, CView)
	//{{AFX_MSG_MAP(CExampleView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExampleView construction/destruction

CExampleView::CExampleView()
{
	// TODO: add construction code here

}

CExampleView::~CExampleView()
{
}

BOOL CExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExampleView drawing

void CExampleView::OnDraw(CDC* pDC)
{
	CExampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	m_gl.OnPaint();	//OpenGL�Ļ��ơ�
}

/////////////////////////////////////////////////////////////////////////////
// CExampleView printing

BOOL CExampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExampleView diagnostics

#ifdef _DEBUG
void CExampleView::AssertValid() const
{
	CView::AssertValid();
}

void CExampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExampleDoc* CExampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExampleDoc)));
	return (CExampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExampleView message handlers

BOOL CExampleView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	//ֱ�Ӱ�������������Ϣ�����͸�OpenGL����
	m_gl.PreTranslateMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
	return CView::PreTranslateMessage(pMsg);
}

void CExampleView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	if(!m_gl.Init(this->GetSafeHwnd()))	//windows����������Ϻ󣬴�ʱ��ʼ��OpenGL,�Ѵ��ڻ���Ȩ������OpenGL
		AfxMessageBox("error!");
	SetTimer(1,30,NULL);
	// TODO: Add your specialized code here and/or call the base class
	
}

BOOL CExampleView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;	//ֱ�ӷ���true����ֹwindows������Ļ��ɫ�����ƹ�����ȫ����OpenGL
	return CView::OnEraseBkgnd(pDC);
}

void CExampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	m_gl.OnSize(cx,cy);	//�����ڴ�С����ʱ�����OpenGL����ͼ
	// TODO: Add your message handler code here
}

void CExampleView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_gl.OnPaint();
	CView::OnTimer(nIDEvent);
}
