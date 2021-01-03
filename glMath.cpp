// glMath.cpp: implementation of the CglMath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "example.h"
#include "glMath.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CglMath::CglMath()
{

}

CglMath::~CglMath()
{

}

void CglMath::CalculateNormal(CglVector3 *vert, CglVector3 *norm, int numRow,int numCol)
{
	//初始化法向量为0
	int nIndex=0,i,j;
	for(i=0;i<numRow;i++)	
	{
		for(j=0;j<numCol;j++)
		{
			norm[nIndex++].Set(0,0,0);
		}
	}
	//计算所有点的法向量
	CglVector3 facenormal;
	for(i=0;i<numRow-1;i++)	
	{
		for(j=0;j<numCol;j++)
		{
			int index[4];//相邻四个点的索引
			index[0]=i*numCol+j;
			index[1]=j;
			index[2]=index[1]+1;
			index[3]=index[0]+1;
			facenormal = (vert[index[0]] - vert[index[1]]).crossMul(vert[index[2]] - vert[index[1]]);
			norm[index[0]]+=facenormal;
			norm[index[1]]+=facenormal;
			norm[index[2]]+=facenormal;
			facenormal = (vert[index[2]] - vert[index[3]]).crossMul(vert[index[0]] - vert[index[3]]);
			norm[index[2]]+=facenormal;
			norm[index[3]]+=facenormal;
			norm[index[0]]+=facenormal;
		}
	}
	//3、所有法向量单位化
	nIndex=0;
	for(i=0;i<numRow;i++)	
	{
		for(j=0;j<numCol;j++)
		{
			norm[nIndex++].Normalize();
		}
	}
}
void CglMath::Dir2HPR(CglVector3 dir,CglVector3 up,CglVector3 &hpr)		
{
	dir.Normalize();
	up.Normalize();
	if(dir.y==1||dir.y==-1)//万向锁
	{
		dir.y+=0.001;
		dir.x =0.001;
		dir.z =0.001;
		dir.Normalize();
	}
	CglVector3 dir_XoZ(dir.x,0,dir.z);
	dir_XoZ.Normalize();
	double temp = dir_XoZ.dotMul(dir);
	temp = max(min(temp,1),-1);
	hpr.y = double(RadToAng(acos(temp)));//p值，绕x旋转
	if(dir.y<0)
		hpr.y=-hpr.y;
	
	hpr.x = double(RadToAng(acos(-dir_XoZ.z)));//h值，绕y旋转
	
	if(dir.x>0)
		hpr.x=-hpr.x;
	//(0,1,0)在平面dir上的投影与up在dir上的投影的夹角
	//点q到平面n上的投影为q'=q+(d-qn)n
	//这里q=(0,1,0);d=0;n=dir.
	CglVector3 dir_upStd,dir_up;
	CglVector3 Ydir(0,1,0);
	dir_upStd = Ydir + (-Ydir.dotMul(dir))*dir;
	dir_up = up + (-up.dotMul(dir))*dir;
	dir_upStd.Normalize();
	dir_up.Normalize();
	temp = dir_upStd.dotMul(dir_up);
	temp = max(min(temp,1),-1);
	hpr.z=double(RadToAng(acos(temp)));
	//判断正负
	CglVector3 dir_leftStd=dir_upStd.crossMul(dir);
	temp = dir_leftStd.dotMul(dir_up);
	if(temp<0) hpr.z=-hpr.z;
}
double CglMath::InverseMatrix(double Matrix[],double inverseMatrix[])
{
	double imat[16];
	int i,j,k;
	for(i=0;i<16;i++)imat[i]=Matrix[i];
	int is[4];
	int js[4];
	double fDet = 1.0f,temp;
	int f = 1;
	
	for ( k = 0; k < 4; k ++)
	{
		// 第一步，全选主元
		double fMax = 0.0f;
		for ( i = k; i < 4; i ++)
		{
			for ( j = k; j < 4; j ++)
			{
				const double f = fabs(imat[j*4+i]);
				if (f > fMax)
				{
					fMax	= f;
					is[k]	= i;
					js[k]	= j;
				}
			}
		}
		if (fabs(fMax) < 1e-15)
			return 0;
		
		if (is[k] != k)
		{
			f = -f;
			temp = imat[k];imat[k]=imat[is[k]];imat[is[k]]=temp;
			temp = imat[4+k];imat[4+k]=imat[4+is[k]];imat[4+is[k]]=temp;
			temp = imat[8+k];imat[8+k]=imat[8+is[k]];imat[8+is[k]]=temp;
			temp = imat[12+k];imat[12+k]=imat[12+is[k]];imat[12+is[k]]=temp;
		}
		if (js[k] != k)
		{
			f = -f;
			temp = imat[k*4];imat[k*4]=imat[js[k]*4];imat[js[k]*4]=temp;
			temp = imat[k*4+1];imat[k*4+1]=imat[js[k]*4+1];imat[js[k]*4+1]=temp;
			temp = imat[k*4+2];imat[k*4+2]=imat[js[k]*4+2];imat[js[k]*4+2]=temp;
			temp = imat[k*4+3];imat[k*4+3]=imat[js[k]*4+3];imat[js[k]*4+3]=temp;
		}
		
		// 计算行列值
		fDet *= imat[k*4+k];
		
		// 计算逆矩阵
		
		// 第二步
		imat[k*4+k] = 1.0/imat[k*4+k];
		// 第三步
		for ( j = 0; j < 4; j ++)
		{
			if (j != k)
				imat[j*4+k]*=imat[k*4+k];
			//m(k, j) *= m(k, k);
		}
		// 第四步
		for ( i = 0; i < 4; i ++)
		{
			if (i != k)
			{
				for	(j = 0; j < 4; j ++)
				{
					if (j != k)
						imat[j*4+i] -= imat[k*4+i]*imat[j*4+k];
					//m(i, j) = m(i, j) - m(i, k) * m(k, j);
				}
			}
		}
		// 第五步
		for (i = 0; i < 4; i ++)
		{
			if (i != k)
				imat[k*4+i] *= -imat[k*4+k];
			//m(i, k) *= -m(k, k);
		}
	}
	
	for	(k = 3; k >= 0; k --)
	{
		if (js[k] != k)
		{
			temp = imat[k];imat[k]=imat[js[k]];imat[js[k]]=temp;
			temp = imat[4+k];imat[4+k]=imat[4+js[k]];imat[4+js[k]]=temp;
			temp = imat[8+k];imat[8+k]=imat[8+js[k]];imat[8+js[k]]=temp;
			temp = imat[12+k];imat[12+k]=imat[12+js[k]];imat[12+js[k]]=temp;
		}
		if (is[k] != k)
		{
			temp = imat[k*4];imat[k*4]=imat[is[k]*4];imat[is[k]*4]=temp;
			temp = imat[1+k*4];imat[1+k*4]=imat[1+is[k]*4];imat[1+is[k]*4]=temp;
			temp = imat[2+k*4];imat[2+k*4]=imat[2+is[k]*4];imat[2+is[k]*4]=temp;
			temp = imat[3+k*4];imat[3+k*4]=imat[3+is[k]*4];imat[3+is[k]*4]=temp;
		}
	}
	for(i=0;i<16;i++)
		inverseMatrix[i] = imat[i];
	return fDet * f;
}

