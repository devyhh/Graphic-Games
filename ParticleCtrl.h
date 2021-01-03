// ParticleCtrl.h: interface for the CParticleCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTICLECTRL_H__F709C3D9_5677_4B26_ACD3_A576B14BEAAD__INCLUDED_)
#define AFX_PARTICLECTRL_H__F709C3D9_5677_4B26_ACD3_A576B14BEAAD__INCLUDED_
#include "glParticle.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParticleCtrl  
{
public:
	CParticleCtrl();
	virtual ~CParticleCtrl();
private:
	CglParticle m_particle[10000];	//Ԥ����һ��������
	int m_numParticle;//�����õ����Ӹ���
	GLuint m_textureid;//��������
};

#endif // !defined(AFX_PARTICLECTRL_H__F709C3D9_5677_4B26_ACD3_A576B14BEAAD__INCLUDED_)
