// glMaterial.h: interface for the CglMaterial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLMATERIAL_H__38A53685_9FFF_4FEC_822F_D79FD4B60E0A__INCLUDED_)
#define AFX_GLMATERIAL_H__38A53685_9FFF_4FEC_822F_D79FD4B60E0A__INCLUDED_
#include "glut.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CglMaterial  
{
public:
	static GLuint LoadGLTextures(char *filename);
	static GLuint LoadGLTransparentTextures(char *filename);	//颜色越深透明度越高
	CglMaterial();
	virtual ~CglMaterial();

};

#endif // !defined(AFX_GLMATERIAL_H__38A53685_9FFF_4FEC_822F_D79FD4B60E0A__INCLUDED_)
