// glCamera.h: interface for the CglCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLCAMERA_H__090064F1_F0BF_4146_A666_5CC6841483C2__INCLUDED_)
#define AFX_GLCAMERA_H__090064F1_F0BF_4146_A666_5CC6841483C2__INCLUDED_
#include "glVector3.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CglCamera  
{
public:
	void SetType(int type);
	void LoadCamera();
	void SaveCamera();
	void Init();
	void SetCamera(const CglVector3& pos, const CglVector3& obj_dir,bool bObj=true,int type=0);
	void ShowView();
	void Rotate(int dir,double len);
	void Move(int dir,double len);
	CglCamera();
	virtual ~CglCamera();
	CglVector3 m_pos;	//视点当前位置
	CglVector3 m_hpr;	//视点方向角，x为h,y为p,z为r
	CglVector3 m_eyedir;//视线方向
	CglVector3 m_updir;	//上方向量
	double m_viewMatrix[16];	//视图矩阵
	double m_viewMatrixInverse[16];	//视图矩阵的逆矩阵
	double m_viewMatrixSave[16];	//保存的视图矩阵
	int m_type;//	相机类型。0表示地面漫游(hpr累积)，1表示任意漫游，2表示环绕漫游
};

#endif // !defined(AFX_GLCAMERA_H__090064F1_F0BF_4146_A666_5CC6841483C2__INCLUDED_)
