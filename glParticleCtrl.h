// glParticleCtrl.h: interface for the CglParticleCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLPARTICLECTRL_H__1E2CC9DB_3D1A_4260_BC38_96641CF07810__INCLUDED_)
#define AFX_GLPARTICLECTRL_H__1E2CC9DB_3D1A_4260_BC38_96641CF07810__INCLUDED_
#include "glParticle.h"
#include "glut.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CglParticleCtrl  
{
public:
	void Draw();
	void UpdatePos(const CglVector3 &eyepos);	//更新粒子的位置
	void Init(int num);
	CglParticleCtrl();
	virtual ~CglParticleCtrl();
private:
	void ResetParticle(int id,bool bFirst = false);	//设置粒子的初始化状态
	CglParticle m_particle[10000];	//预生成一定的粒子
	int m_numParticle;//仿真用的粒子个数
	GLuint m_textureid;//粒子纹理
	int m_lasttime;			//记录粒子运行的上次时间

};

#endif // !defined(AFX_GLPARTICLECTRL_H__1E2CC9DB_3D1A_4260_BC38_96641CF07810__INCLUDED_)
