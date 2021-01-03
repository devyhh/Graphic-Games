// glFont.cpp: implementation of the CglFont class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "example.h"
#include "glFont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CglFont::CglFont()
{
	m_bHaveCreate3DFont = false;
	m_pFontSelected = NULL;
	m_iDisplayListStart = 0;
}

CglFont::~CglFont()
{
	if(m_bHaveCreate3DFont)
		glDeleteLists(m_iDisplayListStart, m_iNumberChars) ;
	if(m_pFontSelected)
		delete m_pFontSelected;
	for(int n=0; n< m_fontlist.GetSize();n+=2)
	{
		int base = m_fontlist[n];
		int len = m_fontlist[n+1];
		glDeleteLists(base,len);
	}
}
void CglFont::Font2D(char * str, double x, double y, int type)
{
	//设置投影方式：平行投影
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//输出字符串
	int len = strlen(str);
	glRasterPos2f(x, y);
	for(int i=0; i<len; ++i)
	{
		switch(type) {
		case 1:
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
			break;
		case 2:
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
			break;
		case 3:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, str[i]);
			break;
		case 4:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
			break;
		case 5:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[i]);
			break;
		case 6:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
			break;
		case 7:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
			break;
		}
	}
	//恢复投影方式
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
bool CglFont::Create3DFont()
{
	// Initialize Default Font Structure
	m_logFontDefault.lfHeight 		= -10 ;
	m_logFontDefault.lfWidth 		= 0 ;
	m_logFontDefault.lfEscapement 	= 0 ;
	m_logFontDefault.lfOrientation 	= 0 ;
	m_logFontDefault.lfWeight 		= FW_NORMAL ;
	m_logFontDefault.lfItalic 		= FALSE ;
	m_logFontDefault.lfUnderline 	= FALSE ;
	m_logFontDefault.lfStrikeOut 	= FALSE ;
	m_logFontDefault.lfCharSet		= ANSI_CHARSET ;
	m_logFontDefault.lfOutPrecision = OUT_TT_PRECIS ;
	m_logFontDefault.lfClipPrecision= CLIP_DEFAULT_PRECIS ;
	m_logFontDefault.lfQuality 		= PROOF_QUALITY ;
	m_logFontDefault.lfPitchAndFamily = VARIABLE_PITCH | TMPF_TRUETYPE | FF_MODERN ;
	strcpy(m_logFontDefault.lfFaceName, "Arial") ;  
	// Create Default Font
	
	// Setup wglGetFontOutline Parameters
	m_iFormat 		= m_iFormatDefault 		= WGL_FONT_POLYGONS ;
	m_fDeviation 	= m_fDeviationDefault 	= 0.0f ;
	m_fExtrusion 	= m_fExtrusionDefault 	= 0.1f ;
	
	// Delete existing display list numbers ;
	m_pFontSelected = new CFont;
	BOOL bResult = m_pFontSelected->CreateFontIndirect(&m_logFontDefault) ;
	ASSERT(bResult) ;

	// Display list varaibles.
	m_iFirstChar = 32 ;
	m_iLastChar = 126 ;
	m_iNumberChars = m_iLastChar - m_iFirstChar ;
	
	
	if (m_iDisplayListStart != 0 )
	{	
		// Detelete the existing lists.
		glDeleteLists(m_iDisplayListStart, m_iNumberChars) ;
	}
	
	// Generate new display lists.
	m_iDisplayListStart = glGenLists(m_iNumberChars) ;
	m_iDisplayListBase = m_iDisplayListStart - m_iFirstChar ; 
	// Get the DC for the current rendering context.	
	HDC hdc = wglGetCurrentDC();
	CDC* pdc = CDC::FromHandle(hdc) ;
	
	// Select the font.
	CFont* pOldFont = (CFont*)pdc->SelectObject(m_pFontSelected) ;
	
	// Generate the display lists...
	GLYPHMETRICSFLOAT agmf[128]; // Fixed size...
	
	bResult = 
		wglUseFontOutlines(	hdc,
		m_iFirstChar,		// First character
		m_iNumberChars,		// Number
		m_iDisplayListStart,	// Starting Display list number
		m_fDeviation,		// Deviation
		m_fExtrusion,		// Extrusion
		m_iFormat,			// Format or WGL_FONT_LINES
		agmf) ;				// Information pointer
	
	if (!bResult)
	{
		TRACE("Error in wglUseFontOutlines.\r\n") ;
	}
	
	if (pOldFont) pdc->SelectObject(pOldFont) ;
	return true;
}
bool CglFont::Font3D(CString str)
{
	if(!m_bHaveCreate3DFont)
	{
		if(Create3DFont())
			m_bHaveCreate3DFont = true;
		else
			return false;
	}
	glListBase(m_iDisplayListBase) ; //NOTE CAN THIS BE NEGATIVE????
	glCallLists(str.GetLength(),GL_UNSIGNED_BYTE,(LPCTSTR)str ) ;	
	return true;
}

bool CglFont::Font3D(CString str,int &id)
{
	if(id<0)
	{
		GLYPHMETRICSFLOAT pgmf[1];
		HDC hDC=wglGetCurrentDC();
		HFONT hFont;
		LOGFONT lf ;
		memset(&lf,0,sizeof(LOGFONT));
		lf.lfHeight = 1 ;
		lf.lfWidth = 0 ;
		lf.lfEscapement = 0 ;
		lf.lfOrientation = 0 ;
		lf.lfWeight = FW_NORMAL ;
		lf.lfItalic = FALSE ;
		lf.lfUnderline = FALSE ;
		lf.lfStrikeOut = FALSE ;
		lf.lfCharSet = GB2312_CHARSET ;
		lf.lfOutPrecision = OUT_TT_PRECIS ;
		lf.lfClipPrecision= CLIP_DEFAULT_PRECIS ;
		lf.lfQuality = PROOF_QUALITY ;
		lf.lfPitchAndFamily = VARIABLE_PITCH | TMPF_TRUETYPE | FF_MODERN ;
		lstrcpy (lf.lfFaceName, "宋体");
		hFont = CreateFontIndirect(&lf);
		//设置当前字体
		SelectObject(wglGetCurrentDC(),hFont);
		
		DWORD dwChar;
		//for(size_t i=0;i<strlen((char *)str);i++)
		CArray<DWORD,DWORD> dwCharArray;
		int i;
		for(i=0;i<str.GetLength();i++)
		{
			unsigned char a = (unsigned char)str[i];
			unsigned char b = (unsigned char)str[i+1];
			if(IsDBCSLeadByte(a))
			{
				dwChar=(DWORD)((a<<8)|b);
				i++;
			}
			else
				dwChar=a;
			dwCharArray.Add(dwChar);
		}
		int ListBase=glGenLists(dwCharArray.GetSize());
		for(i=0;i<dwCharArray.GetSize();i++)
		{
			wglUseFontOutlines(hDC,dwCharArray[i],1,ListBase+i,0.0,0.1f,WGL_FONT_POLYGONS,pgmf);
		}
		id = m_fontlist.Add(ListBase);
		m_fontlist.Add(dwCharArray.GetSize());
		id /= 2;
	}
	int base = m_fontlist[id*2];
	int len = m_fontlist[id*2+1];
	for(int i=0;i<len;i++)
		glCallList(base+i);
	return true;
}