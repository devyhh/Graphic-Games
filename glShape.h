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
	CglVector3 *m_vertArray;	//顶点
	CglVector3 *m_normalArray;	//法线
	CglVector3 *m_texArray;	//纹理坐标
	int		*m_indexArray;
	int m_nVert;			//需要绘制的点的个数
};

#endif // !defined(AFX_GLSHAPE_H__810EA52D_5C3D_466E_84FE_DF188F92B516__INCLUDED_)
