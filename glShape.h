// glShape.h: interface for the CglShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLSHAPE_H__810EA52D_5C3D_466E_84FE_DF188F92B516__INCLUDED_)
#define AFX_GLSHAPE_H__810EA52D_5C3D_466E_84FE_DF188F92B516__INCLUDED_
#include "glVector3.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CglShape  
{
public:
	void DrawCoord(double len);
	void DrawBall(float radius,int lon,int lat);
	CglShape();
	virtual ~CglShape();
	CglVector3 *m_vertArray;	//����
	CglVector3 *m_normalArray;	//����
	CglVector3 *m_texArray;	//��������
	int		*m_indexArray;
	int m_nVert;			//��Ҫ���Ƶĵ�ĸ���
};

#endif // !defined(AFX_GLSHAPE_H__810EA52D_5C3D_466E_84FE_DF188F92B516__INCLUDED_)
