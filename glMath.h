// glMath.h: interface for the CglMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLMATH_H__1234B2A7_4D8A_4F5D_815C_4AE0D4122751__INCLUDED_)
#define AFX_GLMATH_H__1234B2A7_4D8A_4F5D_815C_4AE0D4122751__INCLUDED_
#include "glut.h"
#include "glVector3.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CglMath  
{
public:
	CglMath();
	virtual ~CglMath();
	static double InverseMatrix(double Matrix[],double inverseMatrix[]);
	static void CalculateNormal(CglVector3 *vert,CglVector3 *norm,int numRow,int numCol);
	static void Dir2HPR(CglVector3 dir,CglVector3 up,CglVector3 &hpr);
};

#endif // !defined(AFX_GLMATH_H__1234B2A7_4D8A_4F5D_815C_4AE0D4122751__INCLUDED_)
