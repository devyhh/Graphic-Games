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
	CglParticle m_particle[10000];	//预生成一定的粒子
	int m_numParticle;//仿真用的粒子个数
	GLuint m_textureid;//粒子纹理
};

#endif // !defined(AFX_PARTICLECTRL_H__F709C3D9_5677_4B26_ACD3_A576B14BEAAD__INCLUDED_)
