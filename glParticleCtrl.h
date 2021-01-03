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
	void UpdatePos(const CglVector3 &eyepos);	//�������ӵ�λ��
	void Init(int num);
	CglParticleCtrl();
	virtual ~CglParticleCtrl();
private:
	void ResetParticle(int id,bool bFirst = false);	//�������ӵĳ�ʼ��״̬
	CglParticle m_particle[10000];	//Ԥ����һ��������
	int m_numParticle;//�����õ����Ӹ���
	GLuint m_textureid;//��������
	int m_lasttime;			//��¼�������е��ϴ�ʱ��

};

#endif // !defined(AFX_GLPARTICLECTRL_H__1E2CC9DB_3D1A_4260_BC38_96641CF07810__INCLUDED_)
