// myOpenGL.cpp: implementation of the CmyOpenGL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "example.h"
#include"glplant.h"
#include "myOpenGL.h"
#include "windows.h"
#include "glaux.h"
#pragma comment(lib,"glaux.lib")
GLuint texture[1]={0};
GLuint texturee[1]={0};
float seta = 0;
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Zombie_Control *pZombieControl; 
int LoadGLTextures()
{
	AUX_RGBImageRec *TextureImage=0;
	AUX_RGBImageRec *TextureImagee=0;
	if ((TextureImage=auxDIBImageLoad("1.bmp"))!=NULL)
	{
		glGenTextures(1, &texture[0]);					
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		if (TextureImage->data)					
			free(TextureImage->data);			
		free(TextureImage);	
	}
	if ((TextureImagee=auxDIBImageLoad("2.bmp"))!=NULL)
	{
		glGenTextures(1, &texturee[0]);					
		glBindTexture(GL_TEXTURE_2D, texturee[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImagee->sizeX, TextureImagee->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImagee->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		if (TextureImagee->data)					
			free(TextureImagee->data);			
		free(TextureImagee);
	}
		return true;
}
void Drawplant()
{
	Cglplant a,b,c,d,e,f;
	//a.poss_x=1;
	//a.poss_y=1;
	//a.draw1();

	//b.poss_x=50;
	//b.poss_y=50;
	//b.draw2();

	//c.poss_x=-50;
	//c.poss_y=-50;
	//c.draw3();

	//d.poss_x=100;
	//d.poss_y=100;
	//d.draw4();

	//e.poss_x=-100;
	//e.poss_y=-100;
	//e.draw5();

	a.poss_x=0;
	a.poss_y=0;
	a.draw1();

	b.poss_x=0;
	b.poss_y=50;
	b.draw2();

	c.poss_x=0;
	c.poss_y=-50;
	c.draw3();

	d.poss_x=0;
	d.poss_y=100;
	d.draw4();

	e.poss_x=0;
	e.poss_y=-100;
	e.draw5();

}
void RenderWorld()
{
	//绘制坐标轴
	//glBegin(GL_LINES);
	//glColor3f(1,0,0);
	//glVertex3f(0,0,0);
	//glVertex3f(100,0,0);
	//glColor3f(0,1,0);
	//glVertex3f(0,0,0);
	//glVertex3f(0,100,0);
	//glColor3f(0,0,1);
	//glVertex3f(0,0,0);
	//glVertex3f(0,0,100);
	//glEnd();	
	//绘制光源，用一个小红球代替
	glPushMatrix();
	glRotatef(seta,0,0,1);	//绕(1,1,1)方向旋转变换
	glTranslatef(100,0,0);	//光源距离球心20米的地方
	glColor3f(1,0,0);		//红色小球
	glutSolidSphere(5,100,100);	//绘制小球
	float pos[4]={0,0,0,1};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);	//设置光源位置
	glPopMatrix();
	//绘制模型
	glColor3f(0.9,0.9,0.9);		//目标是白色
	//glEnable(GL_LIGHTING);
//	glutSolidTeapot(5);
	//glutSolidSphere(5,100,100);
	
}

bool g_bPause = false;

CmyOpenGL::CmyOpenGL()
{
	m_bWired=false;
}

CmyOpenGL::~CmyOpenGL()
{

}

void CmyOpenGL::SetRC()
{


	LoadGLTextures();
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glShadeModel(GL_FLAT);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_BACK,GL_LINE);//
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	float amb[4]={0.3,0.0,0.0,1};					//红色环境光
//	float amb[4]={0.0,0.0,0.0,1};
	float dif[4]={1.0,1.0,1.0,1};					//白色漫射光和反射光
//	float dif[4]={0.0,0.0,0.0,1};					//白色漫射光和反射光
	float spe[4]={1.0,1.0,1.0,1};
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb);			
//	glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);
	glLightfv(GL_LIGHT0,GL_SPECULAR,spe);
	glEnable( GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
}

void CmyOpenGL::PostInit()
{
	//seta+=0.1;

	glClearColor(0.5,0.5,0.5,1);
	m_pCamere->SetCamera(CglVector3(300,300,300),CglVector3(0,0,0),true);
	m_pCamere->SaveCamera();
	m_pControl->SetSpeed(0.5,0.1);

	m_particle.Init(1000);
	SetRC();	
	pZombieControl=new Zombie_Control;

}

void CmyOpenGL::InDraw()
{
	pZombieControl->Update();
	pZombieControl->Display();

	myDisplay();
}

void CmyOpenGL::myDisplay()
{
	if(m_bWired)
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	m_pShape->DrawCoord(100);
	DrawSky();
	DrawFloor();
	DrawModel();
	Drawplant();
	RenderWorld();
}

bool CmyOpenGL::OnKey(unsigned int nChar,bool bDown)
{
	if(bDown)
	switch(nChar)
	{
	case VK_F1:
		m_bWired = !m_bWired;
		break;
	case VK_F2:
		g_bPause = !g_bPause;
		break;
	}
	return false;
}


void CmyOpenGL::DrawModel()
{
	if(!g_bPause)
		seta+=1;;
	//glRotatef(seta,0,1,0);
	
	if(seta<180)
	{
		glDisable(GL_LIGHTING);
	}
	else
	{
		glEnable(GL_LIGHTING);
		if(seta>360)
		{
			seta=seta-360;
		}
	}

	m_particle.UpdatePos(m_pCamere->m_pos);
	m_particle.Draw();
}

void CmyOpenGL::DrawSky()
{
	glFrontFace(GL_CW);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj,GLU_SMOOTH);
	gluQuadricTexture(qobj,GL_TRUE);

	static float r=0.0;
	r+=0.08;
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glCullFace(GL_BACK);
	//glBindTexture(GL_TEXTURE_2D, T);
	glTranslatef(0,0,0); 
	glRotatef(r,0.0f,1.0f,0.0f); //天空慢慢旋转,模拟云流动
	glRotatef(90,1,0,0);
	glColor4f(1,1,1,1);
	gluSphere(qobj,1000,32,32);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
	glPopMatrix();

	
}

void CmyOpenGL::DrawFloor()
{
	glFrontFace(GL_CW);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturee[0]);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glColor3f(1.0,1.0,1.0);//白地板
	glBegin(GL_QUADS);//逆时针画出来的正方形才是正面朝着我们的
    glVertex3f(-1000,0,-1000);
    glVertex3f(1000,0.0,-1000);
    glVertex3f(1000,0.0,1000);
    glVertex3f(-1000,0,1000);
    glEnd();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
	glPopMatrix();
}

void CmyOpenGL::DrawSun()
{

}