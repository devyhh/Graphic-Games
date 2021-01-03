// glParticleCtrl.cpp: implementation of the CglParticleCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "example.h"
#include "glParticleCtrl.h"
#include "OpenGL.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CglParticleCtrl::CglParticleCtrl()
{

}

CglParticleCtrl::~CglParticleCtrl()
{

}

void CglParticleCtrl::Init(int num)
{
	m_numParticle = num;
	int i;
	m_lasttime = GetTickCount();
	srand(m_lasttime);
	for(i=0;i<m_numParticle;i++)
	{
		ResetParticle(i,true);
	}
	//加入粒子纹理
	CglMaterial material;
	m_textureid = material.LoadGLTextures("雪花.bmp");
}
extern bool g_bPause;
void CglParticleCtrl::UpdatePos(const CglVector3 &eyepos)
{
	int i;
	int curtime = GetTickCount();
	float usetime = (curtime - m_lasttime)/1000.0;
	m_lasttime = curtime;
	for(i=0;i<m_numParticle;i++)
	{
		if(m_particle[i].m_bActive)	//活的粒子
		{
			m_particle[i].m_lifetime-=1;
		//	if(m_particle[i].m_lifetime<=0)
		//		m_particle[i].m_bActive=false;
			if(!g_bPause)
			{
				m_particle[i].m_speed+=usetime*m_particle[i].m_acc;
				m_particle[i].m_pos += usetime*m_particle[i].m_speed;
			}		
			if(m_particle[i].m_pos[1]<-100)
				m_particle[i].m_bActive=false;
		}
		else	//重新激活粒子
		{
			ResetParticle(i);
		}
		m_particle[i].BillBoard(eyepos);
	}
}

void CglParticleCtrl::Draw()
{
	glPushAttrib(GL_ENABLE_BIT|GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	//打开混合
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glDepthMask(GL_FALSE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,m_textureid);
	for(int i=0;i<m_numParticle;i++)
	{
		if(m_particle[i].m_bActive)	//活的粒子
			m_particle[i].Draw();
	}
	glPopAttrib();
}

void CglParticleCtrl::ResetParticle(int id,bool bFirst)
{
	m_particle[id].m_bActive=true;
	//初始位置
	m_particle[id].m_pos.x=	(double(rand())/RAND_MAX)*800-400;
	m_particle[id].m_pos.z=	(double(rand())/RAND_MAX)*800-400;
	if(bFirst)
		m_particle[id].m_pos.y=	(double(rand())/RAND_MAX)*280;
	else
		m_particle[id].m_pos.y=	280;

	m_particle[id].m_lifetime=100;
	m_particle[id].m_acc.Set(0,-10,0);
	double speed = double(rand())/RAND_MAX*30+1;
	CglVector3 movedir;
	double seta = double(rand())/RAND_MAX*PAI/3;	//30度以内
	movedir[0]= sin(seta);
	movedir[1]=-1;
	movedir[2]=0;
	movedir.Normalize();
	m_particle[id].m_speed = movedir*speed;
	m_particle[id].m_size=1;
	m_particle[id].m_color[3]=1;
}
