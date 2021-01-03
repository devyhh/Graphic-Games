// glPicLoad.h: interface for the CglPicLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLPICLOAD_H__ED534D1B_A772_40BD_B4DC_4F399552A3C7__INCLUDED_)
#define AFX_GLPICLOAD_H__ED534D1B_A772_40BD_B4DC_4F399552A3C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CglImageData
{
public:
	int m_width;
	int m_height;
	int m_bits;
	unsigned char *m_pData;
	CglImageData()
	{
		m_width=0;
		m_height=0;
		m_bits=0;
		m_pData=0;
	}
	~CglImageData()
	{
		m_width=0;
		m_height=0;
		m_bits=0;
		delete m_pData;
		m_pData=0;
	}
};
class CglPicLoad  
{
public:
	CglImageData* ReadBMP(char *filename);
	CglPicLoad();
	virtual ~CglPicLoad();
	
};

#endif // !defined(AFX_GLPICLOAD_H__ED534D1B_A772_40BD_B4DC_4F399552A3C7__INCLUDED_)
