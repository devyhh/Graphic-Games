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
	CglVector3 m_pos;	//��������λ��
	double m_size;			//���ӵĴ�С
	double m_XYratio;		//���ӵĳ������
	CglVector3 m_particleDir[4];	//��������billboardλ��ʱ�õ��ķ���
	CglVector3 m_posCorner[4];		//���ӽǵ������
	
	float m_color[4];	//���ӵ���ɫ
	bool m_bActive;		//�����Ƿ���
//	CglVector3 m_particleMoveDir;//���ӵ��˶�����
//	double m_dSpeed;		//�����˶��ٶ�
	CglVector3 m_speed;		//�ٶ�
	CglVector3 m_acc;		//���ٶ�
	double m_lifetime;		//��������ֵ
	double m_colorfade;
};

#endif // !defined(AFX_GLPARTICLE_H__4645AC51_4FDA_433B_8315_923C6F9C96E0__INCLUDED_)
