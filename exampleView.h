// exampleView.h : interface of the CExampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLEVIEW_H__5FCEB8D4_7AD1_4981_AC88_EA901B8747F1__INCLUDED_)
#define AFX_EXAMPLEVIEW_H__5FCEB8D4_7AD1_4981_AC88_EA901B8747F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "myOpenGL.h"
class CExampleView : public CView
{
	CmyOpenGL m_gl;
protected: // create from serialization only
	CExampleView();
	DECLARE_DYNCREATE(CExampleView)

// Attributes
public:
	CExampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExampleView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in exampleView.cpp
inline CExampleDoc* CExampleView::GetDocument()
   { return (CExampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLEVIEW_H__5FCEB8D4_7AD1_4981_AC88_EA901B8747F1__INCLUDED_)
