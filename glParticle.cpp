// glParticle.cpp: implementation of the CglParticle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "example.h"
#include "glParticle.h"
#include "glut.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CglParticle::CglParticle()
{
	m_color[0]=m_color[1]=m_color[2]=m_color[3]=1;
	m_particleDir[1].Set(0,1,0);
	m_size=1;
	m_XYratio=1;
	m_bActive=false;
}

CglParticle::~CglParticle()
{

}

void CglParticle::Draw()
{
	glColor4fv(m_color);
	glBegin(GL_TRIANGLE_STRIP);							
	glTexCoord2f(0,0);	glVertex3dv(m_posCorner[0]);
	glTexCoord2f(0,1);	glVertex3dv(m_posCorner[1]);
	glTexCoord2f(1,0);	glVertex3dv(m_posCorner[2]);
	glTexCoord2f(1,1);	glVertex3dv(m_posCorner[3]);
	glEnd();
}

void CglParticle::BillBoard(const CglVector3 &eyepos)
{
	m_particleDir[0] = eyepos-m_pos;
	m_particleDir[0].Normalize();
	m_particleDir[2] = m_particleDir[0].crossMul(m_particleDir[1]);
	m_particleDir[3] = m_particleDir[2].crossMul(m_particleDir[0]);
	CglVector3 posleft = m_pos+m_particleDir[2]*m_size;
	CglVector3 posright = m_pos-m_particleDir[2]*m_size;
	m_posCorner[0] = posleft+m_particleDir[3]*m_size*m_XYratio;
	m_posCorner[1] = posleft-m_particleDir[3]*m_size*m_XYratio;
	m_posCorner[2] = posright+m_particleDir[3]*m_size*m_XYratio;
	m_posCorner[3] = posright-m_particleDir[3]*m_size*m_XYratio;
}
