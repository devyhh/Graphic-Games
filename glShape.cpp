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
	m_vertArray=0;	//顶点
	m_normalArray=0;//法线
	m_texArray=0;	//纹理坐标
	m_nVert=0;		//需要绘制的索引点的个数
	m_indexArray=0;	//索引
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

void CglShape::DrawBall(float radius, int lon, int lat)//使用经度分割lon,维度分割lat,半径radius绘制一个球。
{
	if(!m_nVert)
	{
		int i,j,nVert=0;
		//计算网格坐标和法向量
		double lonCur,lonStep=2*PAI/lon,latCur,latStep=PAI/lat;
		lon+=1;
		CglVector3 facenormal;
		m_vertArray = new CglVector3[lon*(lat+1)];
		m_normalArray = new CglVector3[lon*(lat+1)];
		m_texArray = new CglVector3[lon*(lat+1)];
		
		//////////////////////////////////////////////////////////////////////////
		//计算所有网格点的位置和法向量
		//1、计算所有网格点的位置
		for(lonCur=0,i=0;i<lon;lonCur+=lonStep,i++)	//经度
		{
			for(latCur=-PAI/2,j=0;j<=lat;latCur+=latStep,j++)	//维度
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
		//2、计算所有点的法向量
		for(i=0;i<lon;i++)	//经度
		{
			for(j=0;j<lat;j++)	//维度
			{
				int index[4];//相邻四个点的索引
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
		//3、所有法向量单位化
		nVert=0;
		for(lonCur=0,i=0;i<lon;lonCur+=lonStep,i++)	//经度
		{
			for(latCur=-PAI/2,j=0;j<=lat;latCur+=latStep,j++)	//维度
			{	
				m_normalArray[nVert++].Normalize();
			}
		}
		//////////////////////////////////////////////////////////////////////////
		//计算所有需要绘制的点的坐标
		
		m_nVert = lon*(lat+1)*2+(lon-1)*2;	//申请索引的个数。绘制收尾相连的三角带。
		m_indexArray = new int[m_nVert];
		int n=0;
		for(i=0;i<lon;i++)	//经度
		{
			for(j=0;j<=lat;j++)	//维度
			{
				int index[2];//相邻四个点的索引
				index[1]=i*(lat+1)+j;
				if(i==lon-1)
					index[0]=j;
				else
					index[0]=index[1]+lat+1;
				if(i!=0&&j==0)//头节点重复
					m_indexArray[n++]=index[0];
				m_indexArray[n++]=index[0];
				m_indexArray[n++]=index[1];
				if(i!=lon-1&&j==lat)//尾部节点重复
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

void CglShape::DrawCoord(double len)//绘制坐标轴
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
