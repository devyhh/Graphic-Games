// glVector3.h: interface for the CglVector3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLVECTOR3_H__926CE975_74C8_4369_B898_7D3823497800__INCLUDED_)
#define AFX_GLVECTOR3_H__926CE975_74C8_4369_B898_7D3823497800__INCLUDED_

#include "math.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PAI (3.14159)
//弧度转角度
#define RadToAng(x) ((x)/PAI*180)
//角度转弧度
#define AngToRad(x) ((x)/180.0*PAI)

class CglVector3  
{
public:
	CglVector3(void){x=0;y=0;z=0;};
	CglVector3(double fx,double fy,double fz)
	{
		x=fx;y=fy;z=fz;
	}
	
	CglVector3(float *pos)
	{
		x=pos[0];
		y=pos[1];
		z=pos[2];
	}
	CglVector3(double *pos)
	{
		x=pos[0];
		y=pos[1];
		z=pos[2];
	}
	void Set(double fx,double fy,double fz)
	{
		x=fx;y=fy;z=fz;
	}
	void Set(float *pos)
	{
		x=pos[0];
		y=pos[1];
		z=pos[2];
	}
	void Set(double *pos)
	{
		x=pos[0];
		y=pos[1];
		z=pos[2];
	}
	void Get(double *pos)
	{
		pos[0]=x;
		pos[1]=y;
		pos[2]=z;
	}
	void Get(float *pos)
	{
		pos[0]=float(x);
		pos[1]=float(y);
		pos[2]=float(z);
	}
public:
	~CglVector3(void){};
public:
	double x,y,z;
	operator double*()
	{
		return &x;
	}
	operator const double*() const
	{
		return &x;
	}
	CglVector3& operator=(const CglVector3& p)
	{
		x=p.x;y=p.y;z=p.z;
		return *this;
	}
	CglVector3 operator+(const CglVector3& p) const
	{
		CglVector3 vec;
		vec.x = x+p.x;
		vec.y = y+p.y;
		vec.z = z+p.z;
		return vec;
	}
	bool operator==(const CglVector3& p)
	{
		if(fabs(x-p.x)<1e-5)
			if(fabs(y-p.x)<1e-5)
				if(fabs(x-p.x)<1e-5)
					return true;
		return false;
	}
	CglVector3& operator+=(const CglVector3& p)
	{
		x+=p.x;
		y+=p.y;
		z+=p.z;
		return *this;
	}
	CglVector3& operator-=(const CglVector3& p)
	{
		x-=p.x;
		y-=p.y;
		z-=p.z;
		return *this;
	}
	CglVector3 operator-(const CglVector3& p) const
	{
		CglVector3 vec;
		vec.x = x-p.x;
		vec.y = y-p.y;
		vec.z = z-p.z;
		return vec;
	}
	CglVector3 operator-() const
	{
		CglVector3 vec;
		vec.x = -x;
		vec.y = -y;
		vec.z = -z;
		return vec;
	}
	CglVector3 operator*(double data) const
	{
		CglVector3 vec;
		vec.x = x*data;
		vec.y = y*data;
		vec.z = z*data;
		return vec;
	}
	friend CglVector3 operator*(double data, const CglVector3& p)
	{
		CglVector3 vec;
		vec.x = p.x*data;
		vec.y = p.y*data;
		vec.z = p.z*data;
		return vec;
	}
	CglVector3 operator*(float *mat) const
	{
		double v[4];
		int i;
		for(i=0;i<4;i++)
		{
			v[i] = mat[i*4]*x +mat[1+i*4]*y +mat[2+i*4]*z +mat[3+i*4];
		}
		CglVector3 vec;
		for(i=0;i<3;i++)
			vec[i] = v[0]/v[3];
		return vec;
	}
	friend CglVector3 operator*(float *mat, const CglVector3& p)
	{
		double v[4];
		for(int i=0;i<4;i++)
		{
			v[i] = mat[i]*p.x +mat[4+i]*p.y +mat[8+i]*p.z +mat[12+i];
		}
		CglVector3 vec;
		vec.x = v[0]/v[3];
		vec.y = v[1]/v[3];
		vec.z = v[2]/v[3];
		return vec;
	}
	CglVector3 operator*(double *mat) const
	{
		double v[4];
		int i;
		for(i=0;i<4;i++)
		{
			v[i] = mat[i*4]*x +mat[1+i*4]*y +mat[2+i*4]*z +mat[3+i*4];
		}
		CglVector3 vec;
		for(i=0;i<3;i++)
			vec[i] = v[0]/v[3];
		return vec;
	}
	friend CglVector3 operator*(double *mat, const CglVector3& p)
	{
		double v[4];
		for(int i=0;i<4;i++)
		{
			v[i] = mat[i]*p.x +mat[4+i]*p.y +mat[8+i]*p.z +mat[12+i];
		}
		CglVector3 vec;
		vec.x = float(v[0]/v[3]);
		vec.y = float(v[1]/v[3]);
		vec.z = float(v[2]/v[3]);
		return vec;
	}
	CglVector3 operator/(double data) const
	{
		CglVector3 vec;
		vec.x = x/data;
		vec.y = y/data;
		vec.z = z/data;
		return vec;
	}
	double dotMul(const CglVector3&p)
	{
		return x*p.x+y*p.y+z*p.z;
	}
	CglVector3 crossMul(const CglVector3&p) const
	{
		CglVector3 vec;
		vec.x=y*p.z-z*p.y;
		vec.y=z*p.x-x*p.z;
		vec.z=x*p.y-y*p.x;
		return vec;
	}
	double len()
	{
		return sqrt(x*x+y*y+z*z);
	}
	void Normalize()
	{	
		double l=len();
		x /= l;
		y /= l;
		z /= l;
	}
	void Add(int addr,double val)
	{
		if(addr==0)
			x+=val;
		else if(addr==1)
			y+=val;
		else if(addr==2)
			z+=val;
	}
	void Rotate(double seta,int axis)//绕某个轴旋转seta角度,弧度角
	{
		switch(axis)
		{
		case 0://X 轴
			{
				double y1=y*cos(seta)-z*sin(seta);
				z =y*sin(seta)+z*cos(seta);
				y=y1;
			}
			break;
		case 1://Y 轴
			{
				double x1=x*cos(seta)+z*sin(seta);
				z =-x*sin(seta)+z*cos(seta);
				x=x1;
			}
			break;
		case 2://Y 轴
			{
				double x1=x*cos(seta)-y*sin(seta);
				y =x*sin(seta)+y*cos(seta);
				x=x1;
			}
			break;
		}
	}
	void Rotate(double seta,double x,double y,double z)//绕某个方向转seta角度,弧度角
	{	
		double dis1=x*x+z*z;
		double dis2=dis1+y*y;
		dis1 = sqrt(dis1);
		dis2 = sqrt(dis2);
		//先绕x轴转，使轴转动到XOZ平面上,角度为xyz与XOZ夹角
		double setax = acos(dis1/dis2);
		if(y<0) setax = -setax;
		Rotate(setax,0);
		//再绕y轴转，使轴转动到Z轴重合位置,角度为xyz投影与z轴夹角
		double setay = acos(z/dis1);
		if(x>0) setay = -setay;
		Rotate(setay,1);
		//开始绕z轴转
		Rotate(seta,2);
		//////////////////////////////////////////////////////////////////////////恢复
		//绕y转回来。
		Rotate(-setay,1);
		//绕x转回来。
		Rotate(-setax,0);
	}
};

#endif // !defined(AFX_GLVECTOR3_H__926CE975_74C8_4369_B898_7D3823497800__INCLUDED_)
