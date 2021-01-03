#include "stdafx.h"
#include "Zombie.h"

#define TexNum 2
#define TN 100
#define size 40

GLuint Zombie_texture[TexNum]={0};
CglVector3 Zombie_face1[20],Zombie_face2[20],hat_1[20],hat_2[20],hat_3[20],hat_4[20];

int Zombie::LoadGLTextures()
{
	//AUX_RGBImageRec *TextureImage1=0,*TextureImage=0;					// Create Storage Space For The Texture
	AUX_RGBImageRec *TextureImage[TexNum];
	memset(TextureImage,0,sizeof(void *)*TexNum);

	if ((TextureImage[0]=auxDIBImageLoad("face.bmp"))!=NULL&&(TextureImage[1]=auxDIBImageLoad("clothes.bmp"))!=NULL)
	{
		glGenTextures(TexNum, &Zombie_texture[0]);					// Create The Texture
		
		glBindTexture(GL_TEXTURE_2D, Zombie_texture[0]);
		gluBuild2DMipmaps(GL_TEXTURE_2D,3,TextureImage[0]->sizeX, TextureImage[0]->sizeY,GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);	// Linear Filteringd

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);	//颜色直接相乘

		if(TextureImage[0]->data)
			free(TextureImage[0]->data);
		free(TextureImage[0]);

		glBindTexture(GL_TEXTURE_2D, Zombie_texture[1]);
		// Generate The Texture
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
		
		if (TextureImage[1]->data)					// If Texture Image Exists
			free(TextureImage[1]->data);				// Free The Texture Image Memory
		free(TextureImage[1]);						// Free The Image Structure
		
		return true;
	}

	return false;								// Return The Status
}

Zombie::Zombie(void)
{
	lifemode=ZOMBIE_ALIVE;
	actionmode=WALKING;
	life=100.0;
	speed=0.001*size;
	countFrame=0;
	arm_type=0;
	leg_type=0;
	direction.Set(0,0,1);
	LoadGLTextures();
	pFont=new CglFont;
	//position.Set(20,0,-50);
	for(int i=0;i<20;i++)
	{
		double x,z;
		x=size*cos(2*PAI*i/20.0);
		z=size*sin(2*PAI*i/20.0);
		Zombie_face1[i].Set(0.5*x,0.5*z,0.5*size);
		Zombie_face2[i].Set(0.5*x,0.5*z,0.0f);
		hat_1[i].Set(0.4*x,1.5*size,0.4*z);
		hat_2[i].Set(0.4*x,0.6*size,0.4*z);
		hat_3[i].Set(0.8*x,0.6*size,0.8*z);
		hat_4[i].Set(0.8*x,0.4*size,0.8*z);
	}
}

Zombie::~Zombie(void)
{
}

void Zombie::Update()
{
	countFrame++;
	if(rand()%20==0)
		life-=3.5;
	if(countFrame%10==0)
	{
		arm_type=1-arm_type;
		if(actionmode==WALKING)
			leg_type=1-leg_type;
	}
		
	if(actionmode==WALKING)
		position=position+direction*speed*size;
	if(life<1.0)
		lifemode=ZOMBIE_DEAD;
}

void Zombie::Draw()
{
	CglVector3 rotdir,dir;
	float rotang;
	dir.Set(0,0,1);
	direction.Normalize();
	rotang=acos(dir.dotMul(direction));
	if(abs(rotang)<=1e-5||abs(rotang-PAI)<=1e-5)
		rotdir.Set(0,1,0);
	else
		rotdir=direction.crossMul(dir);
	rotdir.Normalize();
	//float size=1;

	glPushMatrix();
	glRotatef(RadToAng(rotang),rotdir.x,rotdir.y,rotdir.z);

	//血条
	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(0,0,(1-0.01*life)*size);
	glTranslatef(0,3*size,0);
	glScalef(0.2,0.2,0.02*life);
	glutSolidCube(size);
	glPopMatrix();

	//剩余血量
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(0,3.2*size,0);
	glRotatef(90,0,1,0);
	glScalef(0.5*size,0.5*size,0.5*size);
	sprintf(rest_life,"%.2f%%",life);
	pFont->Font3D(rest_life);
	glPopMatrix();

	//贴脸
	glPushMatrix();

	glColor3f(1,1,0.2);
	glTranslatef(0,size,0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Zombie_texture[0]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.05,0.05);glVertex3f(-0.35*size,-0.35*size,0.251*size);
	glTexCoord2f(0.05,0.95);glVertex3f(-0.35*size,0.35*size,0.251*size);
	glTexCoord2f(0.95,0.95);glVertex3f(0.35*size,0.35*size,0.251*size);
	glTexCoord2f(0.95,0.05);glVertex3f(0.35*size,-0.35*size,0.251*size);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	//帽子
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0,0,0);
	glVertex3d(0.0f,1.5f*size,0.0f);
	for(int i=0;i<=20;i++)
	{
		glColor3f(1,1,1);
		glVertex3dv(hat_1[i%20]);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	
	for(int i=0;i<=20;i++)
	{
		glColor3f(1,1,1);
		glVertex3dv(hat_1[i%20]);
		glColor3f(0,0,0);
		glVertex3dv(hat_2[i%20]);
	}

	for(int i=0;i<=20;i++)
	{
		glColor3f(0,0,0);
		glVertex3dv(hat_2[i%20]);
		glColor3f(1,1,1);
		glVertex3dv(hat_3[i%20]);
	}

	for(int i=0;i<=20;i++)
	{
		glColor3f(1,1,1);
		glVertex3dv(hat_3[i%20]);
		glColor3f(0,0,0);
		glVertex3dv(hat_4[i%20]);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0,0,0);
	glVertex3d(0.0f,0.4f*size,0.0f);
	for(int i=0;i<=20;i++)
	{
		glColor3f(0,0,0);
		glVertex3dv(hat_4[i%20]);
	}
	glEnd();

	//头
	glColor3f(1,1,0.2);
	glScalef(1,1,0.5);
	glutSolidSphere(0.5*size,36,20);


	//脸
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,0.2);
	glVertex3d(0.0f,0.0f,0.5f*size);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(Zombie_face1[i%20]);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,1,0.2);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(Zombie_face1[i%20]);
		glVertex3dv(Zombie_face2[i%20]);
	}
	glEnd();

	glPopMatrix();


	//身子
	glPushMatrix();
	glTranslatef(0,-size*0.2,0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Zombie_texture[1]);


	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	
	//正面
	glTexCoord2f(0,0);glVertex3f(-0.351*size,-0.551*size,0.251*size);
	glTexCoord2f(0,1);glVertex3f(-0.351*size,0.551*size,0.251*size);
	glTexCoord2f(1,1);glVertex3f(0.351*size,0.551*size,0.251*size);
	glTexCoord2f(1,0);glVertex3f(0.351*size,-0.551*size,0.251*size);
	
	//背面
	glTexCoord2f(0,0);glVertex3f(-0.351*size,-0.551*size,-0.251*size);
	glTexCoord2f(0,0.5);glVertex3f(-0.351*size,0.551*size,-0.251*size);
	glTexCoord2f(0.35,0.5);glVertex3f(0.351*size,0.551*size,-0.251*size);
	glTexCoord2f(0.35,0);glVertex3f(0.351*size,-0.551*size,-0.251*size);

	//侧面
	glTexCoord2f(0,0);glVertex3f(0.351*size,-0.551*size,0.251*size);
	glTexCoord2f(0,0.5);glVertex3f(0.351*size,0.551*size,0.251*size);
	glTexCoord2f(0.35,0.5);glVertex3f(0.351*size,0.551*size,-0.251*size);
	glTexCoord2f(0.35,0);glVertex3f(0.351*size,-0.551*size,-0.251*size);

	glTexCoord2f(0,0);glVertex3f(-0.351*size,-0.551*size,0.251*size);
	glTexCoord2f(0,0.5);glVertex3f(-0.351*size,0.551*size,0.251*size);
	glTexCoord2f(0.35,0.5);glVertex3f(-0.351*size,0.551*size,-0.251*size);
	glTexCoord2f(0.35,0);glVertex3f(-0.351*size,-0.551*size,-0.251*size);

	//上下底面
	glTexCoord2f(0,0);glVertex3f(-0.351*size,0.551*size,-0.251*size);
	glTexCoord2f(0,0.5);glVertex3f(0.351*size,0.551*size,-0.251*size);
	glTexCoord2f(0.35,0.5);glVertex3f(0.351*size,0.551*size,0.251*size);
	glTexCoord2f(0.35,0);glVertex3f(-0.351*size,0.551*size,0.251*size);

	glTexCoord2f(0,0);glVertex3f(-0.351*size,-0.551*size,-0.251*size);
	glTexCoord2f(0,0.5);glVertex3f(0.351*size,-0.551*size,-0.251*size);
	glTexCoord2f(0.35,0.5);glVertex3f(0.351*size,-0.551*size,0.251*size);
	glTexCoord2f(0.35,0);glVertex3f(-0.351*size,-0.551*size,0.251*size);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(0,0,0);
	glScalef(0.7,1.1,0.5);
	glutSolidCube(size);

	glPopMatrix();

	//右上臂
	//glColor3f(0,1,0);
	//glPushMatrix();
	//glTranslatef(-size*0.55,size*0.25,0);
	//if(type==0)
	//	glRotatef(50,1,0,0);
	//else
	//	glRotatef(-50,1,0,0);
	//glTranslatef(0,-size*0.3,0);
	//glScalef(0.2,0.8,0.2);
	//glutSolidCube(size);
	//glPopMatrix();

	//右下臂
	//glColor3f(0,1,0);
	//glPushMatrix();
	//glTranslatef(-size*0.55,size*0.25,0);
	//if(type==0)
	//	glRotatef(50,1,0,0);
	//else
	//	glRotatef(-50,1,0,0);
	//glTranslatef(0,-size*0.6,size*0.3);
	//glScalef(0.2,0.2,0.5);
	//glutSolidCube(size);
	//glPopMatrix();
	
	//右臂
	glColor3f(0,1,0);
	glPushMatrix();
	glTranslatef(-size*0.55,size*0.25,0);
	if(arm_type==0)
		glRotatef(-80,1,0,0);
	else
		glRotatef(-100,1,0,0);
	glTranslatef(0,-size*0.5,0);
	glScalef(0.2,1.2,0.2);
	glutSolidCube(size);
	glPopMatrix();

	////左上臂
	//glColor3f(0,1,0);
	//glPushMatrix();
	//glTranslatef(size*0.55,size*0.25,0);
	//if(type==0)
	//	glRotatef(-50,1,0,0);
	//else
	//	glRotatef(50,1,0,0);
	//glTranslatef(0,-size*0.3,0);
	//glScalef(0.2,0.8,0.2);
	//glutSolidCube(size);
	//glPopMatrix();

	////左下臂
	//glColor3f(0,1,0);
	//glPushMatrix();
	//glTranslatef(size*0.55,size*0.25,0);
	//if(type==0)
	//	glRotatef(-50,1,0,0);
	//else
	//	glRotatef(50,1,0,0);
	//glTranslatef(0,-size*0.6,size*0.3);
	//glScalef(0.2,0.2,0.5);
	//glutSolidCube(size);
	//glPopMatrix();

	//左臂
	glColor3f(0,1,0);
	glPushMatrix();
	glTranslatef(size*0.55,size*0.25,0);
	if(arm_type==0)
		glRotatef(-100,1,0,0);
	else
		glRotatef(-80,1,0,0);
	glTranslatef(0,-size*0.5,0);
	glScalef(0.2,1.2,0.2);
	glutSolidCube(size);
	glPopMatrix();


	//右大腿
	glColor3f(0.2,0.2,1);
	glPushMatrix();
	glTranslatef(-size*0.2,-size*0.7,0);
	if(leg_type==0)
	{
		glRotatef(-50,1,0,0);
		glTranslatef(0,-size*0.5,0);
		glScalef(0.2,0.7,0.2);
		glutSolidCube(size);
	}
	else
	{
		glRotatef(30,1,0,0);
		glTranslatef(0,-size*0.5,0);
		glScalef(0.2,0.7,0.2);
		glutSolidCube(size);
	}
	glPopMatrix();

	//右小腿
	glColor3f(0.4,0.2,1);
	glPushMatrix();
	glTranslatef(-size*0.2,-size*0.7,0);
	if(leg_type==0)
	{
		glRotatef(-50,1,0,0);
		glTranslatef(0,-size*0.75,-size*0.15);
		glScalef(0.2,0.2,0.5);
		glutSolidCube(size);
	}
	else
	{
		glRotatef(30,1,0,0);
		glTranslatef(0,-size*1.1,0);
		glScalef(0.2,0.5,0.2);
		glutSolidCube(size);
	}
	glPopMatrix();

	//左大腿
	glColor3f(0,1,1);
	glPushMatrix();
	glTranslatef(size*0.2,-size*0.7,0);
	if(leg_type==0)
	{
		glRotatef(30,1,0,0);
		glTranslatef(0,-size*0.5,0);
		glScalef(0.2,0.7,0.2);
		glutSolidCube(size);
	}
	else
	{
		glRotatef(-50,1,0,0);
		glTranslatef(0,-size*0.5,0);
		glScalef(0.2,0.7,0.2);
		glutSolidCube(size);
	}
	glPopMatrix();

	//左小腿
	glColor3f(0.5,1,1);
	glPushMatrix();
	glTranslatef(size*0.2,-size*0.7,0);
	if(leg_type==0)
	{
		glRotatef(30,1,0,0);
		glTranslatef(0,-size*1.1,0);
		glScalef(0.2,0.5,0.2);
		glutSolidCube(size);
	}
	else
	{
		glRotatef(-50,1,0,0);
		glTranslatef(0,-size*0.75,-size*0.15);
		glScalef(0.2,0.2,0.5);
		glutSolidCube(size);
	}
	glPopMatrix();
	glPopMatrix();

}


