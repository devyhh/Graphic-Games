#include "stdafx.h"
#include "example.h"
#include"glplant.h"
#include "glut.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define TexNum 1
#define size 3
int i=0;
int j=0;
GLuint texture1[1]={0};
GLuint texture2[1]={0};
GLuint texture3[1]={0};
CglVector3 face1[20],face2[20];


int Cglplant::LoadGLTextures()								// Load Bitmaps And Convert To Textures
{
	AUX_RGBImageRec *TextureImage=0;					// Create Storage Space For The Texture
	AUX_RGBImageRec *TextureImage1=0;
	AUX_RGBImageRec *TextureImage2=0;
	if ((TextureImage=auxDIBImageLoad("eye.bmp"))!=NULL)
	{
		glGenTextures(1, &texture1[0]);					// Create The Texture
		glBindTexture(GL_TEXTURE_2D, texture1[0]);
		// Generate The Texture
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
		
		if (TextureImage->data)					// If Texture Image Exists
			free(TextureImage->data);				// Free The Texture Image Memory
		free(TextureImage);						// Free The Image Structure
		
	}
	if ((TextureImage1=auxDIBImageLoad("6.bmp"))!=NULL)
	{
		glGenTextures(1, &texture2[0]);					// Create The Texture
		glBindTexture(GL_TEXTURE_2D, texture2[0]);
		// Generate The Texture
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage1->sizeX, TextureImage1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage1->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
		
		if (TextureImage1->data)					// If Texture Image Exists
			free(TextureImage1->data);				// Free The Texture Image Memory
		free(TextureImage1);						// Free The Image Structure
		
	}
	if ((TextureImage2=auxDIBImageLoad("8.bmp"))!=NULL)
	{
		glGenTextures(1, &texture3[0]);					// Create The Texture
		glBindTexture(GL_TEXTURE_2D, texture3[0]);
		// Generate The Texture
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage2->sizeX, TextureImage2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage2->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
		
		if (TextureImage2->data)					// If Texture Image Exists
			free(TextureImage2->data);				// Free The Texture Image Memory
		free(TextureImage2);						// Free The Image Structure
		
	}
	return true;
	return false;								// Return The Status
}

Cglplant::Cglplant()
{
	poss_x=0;
	poss_y=0;
	
	initialize();
	//LoadGLTextures();
	return;
}

Cglplant::Cglplant(float x,float y)
{
	poss_x=x;
	poss_y=y;
	initialize();
	return;
}

void Cglplant::initialize()
{
	scale=1.0f;
		lifemode=ALIVE;
	life=100.0;
	speed=0.01;
	countFrame=0;
	LoadGLTextures();

	
}

void Cglplant::Update()
{
	countFrame++;
	if(rand()%20==0)
		life-=3.5;
	if(life<1.0)
		lifemode=DEAD;
}



void Cglplant::draw1()
{
	glPushMatrix();
	

	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslatef(poss_y*2,0,poss_x*2);
	glScalef(0.5,1,0.5);
	glColor3f(0,39,1);
	glRotatef(-90,1,0,0);
	GLUquadricObj *b;
	b=gluNewQuadric();
	gluCylinder(b,20,20,70,320,320);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,10,2.5);
	glTranslatef(poss_y*2,80,poss_x*2);
	glScalef(10,10,7);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(poss_y*2,75,poss_x*2-50);
	glColor3f(-50,10,-5);
	glRotatef(0,1,0,0);
	GLUquadricObj *c;
	c=gluNewQuadric();
	gluCylinder(c,10,10,50,320,320);
	glPopMatrix();

	glPushMatrix();
	glColor3f(3,39,1);
	glTranslatef(poss_y*2-20,30,poss_x*2);
	glRotatef(0,0,-90,0);
	glScalef(3,2,1);
	glutSolidSphere(5,100,100);
	glPopMatrix();


	glPushMatrix();
	glColor3f(3,39,1);
	glTranslatef(poss_y*2+20,30,poss_x*2);
	glRotatef(0,0,-90,0);
	glScalef(3,2,1);
	glutSolidSphere(5,100,100);
	glPopMatrix();



	glPushMatrix();

	glColor3f(0,10,2.5);
	glTranslatef(0,10,0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture1[0]);
	glBegin(GL_QUADS);

	//glTexCoord2f(0.05,0.05);glVertex3f(-0.35*size,-0.35*size,0.251*size);
	//glTexCoord2f(0.05,0.95);glVertex3f(-0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.95);glVertex3f(0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.05);glVertex3f(0.35*size,-0.35*size,0.251*size);

	//glTexCoord2f(0,0);glVertex3f(-25,45,20);
	//glTexCoord2f(0,1);glVertex3f(-25,95,20);
	//glTexCoord2f(1,1);glVertex3f(25,95,20);
	//glTexCoord2f(1,0);glVertex3f(25,45,20);

	glTexCoord2f(0,0);glVertex3f(poss_y*2-25,45,poss_x*2-18);
	glTexCoord2f(0,1);glVertex3f(poss_y*2-25,95,poss_x*2-18);
	glTexCoord2f(1,1);glVertex3f(poss_y*2+25,95,poss_x*2-18);
	glTexCoord2f(1,0);glVertex3f(poss_y*2+25,45,poss_x*2-18);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,0.2);
	glVertex3d(0.0f,0.0f,0.5f*size);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,1,0.2);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
		glVertex3dv(face2[i%20]);
	}
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glColor3f(3,10,3);
	glTranslatef(poss_y*2,75,poss_x*2-20-i);
	if(i<=500) i+=10;
	if(i==500) i=0;
	glRotatef(0,0,-90,0);
	glScalef(2,2,2);
	glutSolidSphere(5,100,100);
	glPopMatrix();


	glPopMatrix();

	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}

void Cglplant::draw2()
{
	glPushMatrix();
	

	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslatef(poss_y*2,0,poss_x*2);
	glScalef(0.5,1,0.5);
	glColor3f(0,39,1);
	glRotatef(-90,1,0,0);
	GLUquadricObj *b;
	b=gluNewQuadric();
	gluCylinder(b,20,20,70,320,320);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,10,2.5);
	glTranslatef(poss_y*2,80,poss_x*2);
	glScalef(10,10,7);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(poss_y*2+10,75,poss_x*2-50);
	glColor3f(-50,10,-5);
	glRotatef(0,1,0,0);
	GLUquadricObj *c;
	c=gluNewQuadric();
	gluCylinder(c,10,10,50,320,320);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(poss_y*2-10,75,poss_x*2-50);
	glColor3f(-50,10,-5);
	glRotatef(0,1,0,0);
	GLUquadricObj *d;
	d=gluNewQuadric();
	gluCylinder(d,10,10,50,320,320);
	glPopMatrix();

	glPushMatrix();
	glColor3f(3,39,1);
	glTranslatef(poss_y*2-20,30,poss_x*2);
	glRotatef(0,0,-90,0);
	glScalef(3,2,1);
	glutSolidSphere(5,100,100);
	glPopMatrix();


	glPushMatrix();
	glColor3f(3,39,1);
	glTranslatef(poss_y*2+20,30,poss_x*2);
	glRotatef(0,0,-90,0);
	glScalef(3,2,1);
	glutSolidSphere(5,100,100);
	glPopMatrix();


	glPushMatrix();

	glColor3f(0,10,2.5);
	glTranslatef(0,10,0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture1[0]);
	glBegin(GL_QUADS);

	//glTexCoord2f(0.05,0.05);glVertex3f(-0.35*size,-0.35*size,0.251*size);
	//glTexCoord2f(0.05,0.95);glVertex3f(-0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.95);glVertex3f(0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.05);glVertex3f(0.35*size,-0.35*size,0.251*size);

	//glTexCoord2f(0,0);glVertex3f(-25,45,20);
	//glTexCoord2f(0,1);glVertex3f(-25,95,20);
	//glTexCoord2f(1,1);glVertex3f(25,95,20);
	//glTexCoord2f(1,0);glVertex3f(25,45,20);

	glTexCoord2f(0,0);glVertex3f(poss_y*2-25,45,poss_x*2-18);
	glTexCoord2f(0,1);glVertex3f(poss_y*2-25,95,poss_x*2-18);
	glTexCoord2f(1,1);glVertex3f(poss_y*2+25,95,poss_x*2-18);
	glTexCoord2f(1,0);glVertex3f(poss_y*2+25,45,poss_x*2-18);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,0.2);
	glVertex3d(0.0f,0.0f,0.5f*size);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,1,0.2);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
		glVertex3dv(face2[i%20]);
	}
	glEnd();

	glPopMatrix();


	glPopMatrix();

	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}

void Cglplant::draw3()
{
	glPushMatrix();
	

	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslatef(poss_y*2,0,poss_x*2);
	glScalef(0.5,1,0.5);
	glColor3f(0,39,1);
	glRotatef(-90,1,0,0);
	GLUquadricObj *b;
	b=gluNewQuadric();
	gluCylinder(b,20,20,70,320,320);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,10,2.5);
	glTranslatef(poss_y*2,80,poss_x*2);
	glScalef(10,10,7);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(poss_y*2,80,poss_x*2-50);
	glColor3f(-50,10,-5);
	glRotatef(0,1,0,0);
	glScalef(2.5,2.5,1);
	GLUquadricObj *c;
	c=gluNewQuadric();
	gluCylinder(c,10,10,50,320,320);
	glPopMatrix();

	glPushMatrix();
	glColor3f(3,39,1);
	glTranslatef(poss_y*2-20,30,poss_x*2);
	glRotatef(0,0,-90,0);
	glScalef(3,2,1);
	glutSolidSphere(5,100,100);
	glPopMatrix();


	glPushMatrix();
	glColor3f(3,39,1);
	glTranslatef(poss_y*2+20,30,poss_x*2);
	glRotatef(0,0,-90,0);
	glScalef(3,2,1);
	glutSolidSphere(5,100,100);
	glPopMatrix();


	glPushMatrix();

	glColor3f(0,10,2.5);
	glTranslatef(0,10,0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture1[0]);
	glBegin(GL_QUADS);

	//glTexCoord2f(0.05,0.05);glVertex3f(-0.35*size,-0.35*size,0.251*size);
	//glTexCoord2f(0.05,0.95);glVertex3f(-0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.95);glVertex3f(0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.05);glVertex3f(0.35*size,-0.35*size,0.251*size);

	//glTexCoord2f(0,0);glVertex3f(-25,45,20);
	//glTexCoord2f(0,1);glVertex3f(-25,95,20);
	//glTexCoord2f(1,1);glVertex3f(25,95,20);
	//glTexCoord2f(1,0);glVertex3f(25,45,20);

	glTexCoord2f(0,0);glVertex3f(poss_y*2-25,45,poss_x*2-18);
	glTexCoord2f(0,1);glVertex3f(poss_y*2-25,95,poss_x*2-18);
	glTexCoord2f(1,1);glVertex3f(poss_y*2+25,95,poss_x*2-18);
	glTexCoord2f(1,0);glVertex3f(poss_y*2+25,45,poss_x*2-18);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,0.2);
	glVertex3d(0.0f,0.0f,0.5f*size);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,1,0.2);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
		glVertex3dv(face2[i%20]);
	}
	glEnd();

	glPopMatrix();


	glPopMatrix();

	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}

void Cglplant::draw4()
{
	glPushMatrix();
	

	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslatef(poss_y*2,0,poss_x*2);
	glScalef(0.5,1,0.5);
	glColor3f(0,39,1);
	glRotatef(-90,1,0,0);
	GLUquadricObj *b;
	b=gluNewQuadric();
	gluCylinder(b,20,20,70,320,320);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,10,2.5);
	glTranslatef(poss_y*2,80,poss_x*2);
	glScalef(10,10,7);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(poss_y*2+10,70,poss_x*2-50);
	glColor3f(-50,10,-5);
	glRotatef(0,1,0,0);
	GLUquadricObj *c;
	c=gluNewQuadric();
	gluCylinder(c,10,10,50,320,320);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(poss_y*2-10,70,poss_x*2-50);
	glColor3f(-50,10,-5);
	glRotatef(0,1,0,0);
	GLUquadricObj *d;
	d=gluNewQuadric();
	gluCylinder(d,10,10,50,320,320);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(poss_y*2+10,90,poss_x*2-50);
	glColor3f(-50,10,-5);
	glRotatef(0,1,0,0);
	GLUquadricObj *e;
	e=gluNewQuadric();
	gluCylinder(e,10,10,50,320,320);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(poss_y*2-10,90,poss_x*2-50);
	glColor3f(-50,10,-5);
	glRotatef(0,1,0,0);
	GLUquadricObj *f;
	f=gluNewQuadric();
	gluCylinder(f,10,10,50,320,320);
	glPopMatrix();

	glPushMatrix();
	glColor3f(3,39,1);
	glTranslatef(poss_y*2-20,30,poss_x*2);
	glRotatef(0,0,-90,0);
	glScalef(3,2,1);
	glutSolidSphere(5,100,100);
	glPopMatrix();


	glPushMatrix();
	glColor3f(3,39,1);
	glTranslatef(poss_y*2+20,30,poss_x*2);
	glRotatef(0,0,-90,0);
	glScalef(3,2,1);
	glutSolidSphere(5,100,100);
	glPopMatrix();


	glPushMatrix();

	glColor3f(0,10,2.5);
	glTranslatef(0,10,0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture1[0]);
	glBegin(GL_QUADS);

	//glTexCoord2f(0.05,0.05);glVertex3f(-0.35*size,-0.35*size,0.251*size);
	//glTexCoord2f(0.05,0.95);glVertex3f(-0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.95);glVertex3f(0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.05);glVertex3f(0.35*size,-0.35*size,0.251*size);

	//glTexCoord2f(0,0);glVertex3f(-25,45,20);
	//glTexCoord2f(0,1);glVertex3f(-25,95,20);
	//glTexCoord2f(1,1);glVertex3f(25,95,20);
	//glTexCoord2f(1,0);glVertex3f(25,45,20);

	glTexCoord2f(0,0);glVertex3f(poss_y*2-25,45,poss_x*2-18);
	glTexCoord2f(0,1);glVertex3f(poss_y*2-25,95,poss_x*2-18);
	glTexCoord2f(1,1);glVertex3f(poss_y*2+25,95,poss_x*2-18);
	glTexCoord2f(1,0);glVertex3f(poss_y*2+25,45,poss_x*2-18);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,0.2);
	glVertex3d(0.0f,0.0f,0.5f*size);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,1,0.2);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
		glVertex3dv(face2[i%20]);
	}
	glEnd();

	glPopMatrix();


	glPopMatrix();

	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}

void Cglplant::draw5()
{
	glPushMatrix();
	


	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslatef(poss_y*2,0,poss_x*2);
	glScalef(0.5,1,0.5);
	glColor3f(0,39,1);
	glRotatef(-90,1,0,0);
	GLUquadricObj *b;
	b=gluNewQuadric();
	gluCylinder(b,20,20,70,320,320);
	glPopMatrix();

	glPushMatrix();
	glColor3f(20,20,1.5);
	glTranslatef(poss_y*2,80,poss_x*2);
	glScalef(10,10,5);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(3,39,1);
	glTranslatef(poss_y*2-20,30,poss_x*2);
	glRotatef(0,0,-90,0);
	glScalef(3,2,1);
	glutSolidSphere(5,100,100);
	glPopMatrix();


	glPushMatrix();
	glColor3f(3,39,1);
	glTranslatef(poss_y*2+20,30,poss_x*2);
	glRotatef(0,0,-90,0);
	glScalef(3,2,1);
	glutSolidSphere(5,100,100);
	glPopMatrix();


	glPushMatrix();

	glColor3f(20,20,1.5);
	glTranslatef(0,10,0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture2[0]);
	glBegin(GL_QUADS);

	//glTexCoord2f(0.05,0.05);glVertex3f(-0.35*size,-0.35*size,0.251*size);
	//glTexCoord2f(0.05,0.95);glVertex3f(-0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.95);glVertex3f(0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.05);glVertex3f(0.35*size,-0.35*size,0.251*size);

	//glTexCoord2f(0,0);glVertex3f(-25,45,20);
	//glTexCoord2f(0,1);glVertex3f(-25,95,20);
	//glTexCoord2f(1,1);glVertex3f(25,95,20);
	//glTexCoord2f(1,0);glVertex3f(25,45,20);

	glTexCoord2f(0,0);glVertex3f(poss_y*2-25,45,poss_x*2-13);
	glTexCoord2f(0,1);glVertex3f(poss_y*2-25,95,poss_x*2-13);
	glTexCoord2f(1,1);glVertex3f(poss_y*2+25,95,poss_x*2-13);
	glTexCoord2f(1,0);glVertex3f(poss_y*2+25,45,poss_x*2-13);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	/*glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,0.2);
	glVertex3d(0.0f,0.0f,0.5f*size);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,1,0.2);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
		glVertex3dv(face2[i%20]);
	}
	glEnd();*/

	glPopMatrix();

	j=rand()%100+1;
	if(j%50==0)
	{
	glPushMatrix();
	glColor3f(20,20,1.5);
	glTranslatef(poss_y*2,80,poss_x*2-15);
	glScalef(10,10,1);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();

	glColor3f(20,20,1.5);
	glTranslatef(0,10,0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture3[0]);
	glBegin(GL_QUADS);

	//glTexCoord2f(0.05,0.05);glVertex3f(-0.35*size,-0.35*size,0.251*size);
	//glTexCoord2f(0.05,0.95);glVertex3f(-0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.95);glVertex3f(0.35*size,0.35*size,0.251*size);
	//glTexCoord2f(0.95,0.05);glVertex3f(0.35*size,-0.35*size,0.251*size);

	//glTexCoord2f(0,0);glVertex3f(-25,45,20);
	//glTexCoord2f(0,1);glVertex3f(-25,95,20);
	//glTexCoord2f(1,1);glVertex3f(25,95,20);
	//glTexCoord2f(1,0);glVertex3f(25,45,20);

	glTexCoord2f(0,0);glVertex3f(poss_y*2-25,45,poss_x*2-20);
	glTexCoord2f(0,1);glVertex3f(poss_y*2-25,95,poss_x*2-20);
	glTexCoord2f(1,1);glVertex3f(poss_y*2+25,95,poss_x*2-20);
	glTexCoord2f(1,0);glVertex3f(poss_y*2+25,45,poss_x*2-20);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	/*glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,0.2);
	glVertex3d(0.0f,0.0f,0.5f*size);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,1,0.2);
	for(int i=0;i<=20;i++)
	{
		glVertex3dv(face1[i%20]);
		glVertex3dv(face2[i%20]);
	}
	glEnd();*/

	glPopMatrix();


	}

	glPopMatrix();

	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}