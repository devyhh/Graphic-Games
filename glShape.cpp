// glShape.cpp: implementation of the CglShape class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "example.h"
#include "glShape.h"
#include "glMath.h"
#include "glut.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CglShape::CglShape()
{
	m_vertArray=0;	//����
	m_normalArray=0;//����
	m_texArray=0;	//��������
	m_nVert=0;		//��Ҫ���Ƶ�������ĸ���
	m_indexArray=0;	//����
}

CglShape::~CglShape()
{
	if(m_vertArray)
		delete []m_vertArray;
	if(m_normalArray)
		delete []m_normalArray;
	if(m_texArray)
		delete []m_texArray;
	if(m_indexArray)
		delete []m_indexArray;
	m_vertArray=0;	
	m_normalArray=0;
	m_texArray=0;
	m_indexArray=0;
	m_nVert=0;	
}

void CglShape::DrawBall(float radius, int lon, int lat)//ʹ�þ��ȷָ�lon,ά�ȷָ�lat,�뾶radius����һ����
{
	if(!m_nVert)
	{
		int i,j,nVert=0;
		//������������ͷ�����
		double lonCur,lonStep=2*PAI/lon,latCur,latStep=PAI/lat;
		lon+=1;
		CglVector3 facenormal;
		m_vertArray = new CglVector3[lon*(lat+1)];
		m_normalArray = new CglVector3[lon*(lat+1)];
		m_texArray = new CglVector3[lon*(lat+1)];
		
		//////////////////////////////////////////////////////////////////////////
		//��������������λ�úͷ�����
		//1����������������λ��
		for(lonCur=0,i=0;i<lon;lonCur+=lonStep,i++)	//����
		{
			for(latCur=-PAI/2,j=0;j<=lat;latCur+=latStep,j++)	//ά��
			{			
				m_vertArray[nVert][2]=radius*cos(latCur)*sin(lonCur);
				m_vertArray[nVert][0]=radius*cos(latCur)*cos(lonCur);
				m_vertArray[nVert][1]=radius*sin(latCur);
				m_normalArray[nVert].Set(0,0,0);
				double dlon = lonCur/(PAI*2);
				double dlat = (latCur+PAI/2)/PAI;
				m_texArray[nVert][0]=dlon;
				m_texArray[nVert][1]=1-dlat;
				nVert++;
			}
		}
		//2���������е�ķ�����
		for(i=0;i<lon;i++)	//����
		{
			for(j=0;j<lat;j++)	//ά��
			{
				int index[4];//�����ĸ��������
				index[0]=i*(lat+1)+j;
				if(i==lon-1)
					index[1]=j;
				else
					index[1]=index[0]+lat+1;
				index[2]=index[1]+1;
				index[3]=index[0]+1;
				facenormal = (m_vertArray[index[0]] - m_vertArray[index[1]]).crossMul(m_vertArray[index[2]] - m_vertArray[index[1]]);
				m_normalArray[index[0]]+=facenormal;
				m_normalArray[index[1]]+=facenormal;
				m_normalArray[index[2]]+=facenormal;
				facenormal = (m_vertArray[index[2]] - m_vertArray[index[3]]).crossMul(m_vertArray[index[0]] - m_vertArray[index[3]]);
				m_normalArray[index[2]]+=facenormal;
				m_normalArray[index[3]]+=facenormal;
				m_normalArray[index[0]]+=facenormal;
			}
		}
		//3�����з�������λ��
		nVert=0;
		for(lonCur=0,i=0;i<lon;lonCur+=lonStep,i++)	//����
		{
			for(latCur=-PAI/2,j=0;j<=lat;latCur+=latStep,j++)	//ά��
			{	
				m_normalArray[nVert++].Normalize();
			}
		}
		//////////////////////////////////////////////////////////////////////////
		//����������Ҫ���Ƶĵ������
		
		m_nVert = lon*(lat+1)*2+(lon-1)*2;	//���������ĸ�����������β���������Ǵ���
		m_indexArray = new int[m_nVert];
		int n=0;
		for(i=0;i<lon;i++)	//����
		{
			for(j=0;j<=lat;j++)	//ά��
			{
				int index[2];//�����ĸ��������
				index[1]=i*(lat+1)+j;
				if(i==lon-1)
					index[0]=j;
				else
					index[0]=index[1]+lat+1;
				if(i!=0&&j==0)//ͷ�ڵ��ظ�
					m_indexArray[n++]=index[0];
				m_indexArray[n++]=index[0];
				m_indexArray[n++]=index[1];
				if(i!=lon-1&&j==lat)//β���ڵ��ظ�
					m_indexArray[n++]=index[1];
			}
		}
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_DOUBLE,24,m_vertArray);
	glNormalPointer(GL_DOUBLE,24,m_normalArray);
	glTexCoordPointer(2,GL_DOUBLE,24,m_texArray);
	glDrawElements(GL_TRIANGLE_STRIP,m_nVert, GL_UNSIGNED_INT,m_indexArray);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void CglShape::DrawCoord(double len)//����������
{
	//glBegin(GL_LINES);
	//glColor3f(1,0,0);
	//glVertex3f(0,0,0);
	//glVertex3f(len,0,0);
	//glColor3f(0,1,0);
	//glVertex3f(0,0,0);
	//glVertex3f(0,len,0);
	//glColor3f(0,0,1);
	//glVertex3f(0,0,0);
	//glVertex3f(0,0,len);
	//glEnd();
}
