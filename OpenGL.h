// OpenGL.h: interface for the COpenGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGL_H__E5995580_D8B1_4938_ADFE_4A915C808FF2__INCLUDED_)
#define AFX_OPENGL_H__E5995580_D8B1_4938_ADFE_4A915C808FF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "glut.h"
#include "glCamera.h"
#include "glControl.h"
#include "glFont.h"
#include "glMaterial.h"
#include "glPicLoad.h"
#include "glShape.h"
#include "glMath.h"
#include "glParticle.h"
#include "glParticleCtrl.h"
#include<GLAux.h>
class COpenGL  
{
public:
	virtual void InDraw();
	void OnView();
	bool PreTranslateMessage(unsigned int message,unsigned int wParam,unsigned int lParam);
	void OnSize(int w,int h);
	void OnPaint();
	virtual void PostInit();
	bool Init(HWND hWnd);
	COpenGL();
	virtual ~COpenGL();
	virtual bool OnKey(unsigned int nChar,bool bDown);
	virtual bool OnMouse(int message,CPoint pt);
	friend class CglControl;
protected:
	HDC m_hDC;
	HGLRC m_hglrc;
	float m_PerspectiveParam[4];
	CglControl *m_pControl;
	HWND m_hWnd;
	CglCamera *m_pCamere;
	CglFont *m_pFont;
	CglShape *m_pShape;
	CglPicLoad *m_pPicLoad;
	float m_fps;
};

#endif // !defined(AFX_OPENGL_H__E5995580_D8B1_4938_ADFE_4A915C808FF2__INCLUDED_)
