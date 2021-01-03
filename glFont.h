// glFont.h: interface for the CglFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLFONT_H__6C94D756_CC61_4203_B4A1_D0A7D46BD91B__INCLUDED_)
#define AFX_GLFONT_H__6C94D756_CC61_4203_B4A1_D0A7D46BD91B__INCLUDED_
#include "glut.h"
#include <afxtempl.h>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CglFont  
{
public:
	CglFont();
	virtual ~CglFont();
	void Font2D(char * str, double x, double y, int type);
	bool Font3D(CString str);
	bool Font3D(CString str,int &id);
private:
	bool Create3DFont();
	LOGFONT m_logFontDefault ;
	int m_iFormat ;
	double m_fDeviation ;
	double m_fExtrusion ;
	CFont* m_pFontSelected ;
	int m_iFormatDefault ;
	double m_fDeviationDefault ;
	double m_fExtrusionDefault ;
	int m_iFirstChar ;
	int m_iLastChar ;
	int m_iNumberChars ;
	int m_iDisplayListStart ;
	int m_iDisplayListBase ;
	bool m_bHaveCreate3DFont;
	CArray<int,int>m_fontlist;//保存所有的已经生成的三维字体列表
};

#endif // !defined(AFX_GLFONT_H__6C94D756_CC61_4203_B4A1_D0A7D46BD91B__INCLUDED_)
