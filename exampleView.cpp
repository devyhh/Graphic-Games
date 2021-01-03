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
	m_gl.OnPaint();	//OpenGL的绘制。
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
	//直接把所有鼠标键盘消息都发送给OpenGL处理。
	m_gl.PreTranslateMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
	return CView::PreTranslateMessage(pMsg);
}

void CExampleView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	if(!m_gl.Init(this->GetSafeHwnd()))	//windows窗口生成完毕后，此时初始化OpenGL,把窗口绘制权利交给OpenGL
		AfxMessageBox("error!");
	SetTimer(1,30,NULL);
	// TODO: Add your specialized code here and/or call the base class
	
}

BOOL CExampleView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;	//直接返回true，禁止windows绘制屏幕底色。绘制工作完全交给OpenGL
	return CView::OnEraseBkgnd(pDC);
}

void CExampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	m_gl.OnSize(cx,cy);	//当窗口大小调整时候调整OpenGL的视图
	// TODO: Add your message handler code here
}

void CExampleView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_gl.OnPaint();
	CView::OnTimer(nIDEvent);
}
