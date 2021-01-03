// glParticle.h: interface for the CglParticle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLPARTICLE_H__4645AC51_4FDA_433B_8315_923C6F9C96E0__INCLUDED_)
#define AFX_GLPARTICLE_H__4645AC51_4FDA_433B_8315_923C6F9C96E0__INCLUDED_
#include "glVector3.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CglParticleCtrl;
class CglParticle  
{
public:
	void BillBoard(const CglVector3 &eyepos);
	void Draw();
	CglParticle();
	virtual ~CglParticle();
	friend class CglParticleCtrl;
private:
	CglVector3 m_pos;	//粒子中心位置
	double m_size;			//粒子的大小
	double m_XYratio;		//粒子的长宽比例
	CglVector3 m_particleDir[4];	//计算粒子billboard位置时用到的方向
	CglVector3 m_posCorner[4];		//粒子角点的坐标
	
	float m_color[4];	//粒子的颜色
	bool m_bActive;		//粒子是否存活
//	CglVector3 m_particleMoveDir;//粒子的运动方向
//	double m_dSpeed;		//粒子运动速度
	CglVector3 m_speed;		//速度
	CglVector3 m_acc;		//加速度
	double m_lifetime;		//粒子生命值
	double m_colorfade;
};

#endif // !defined(AFX_GLPARTICLE_H__4645AC51_4FDA_433B_8315_923C6F9C96E0__INCLUDED_)
