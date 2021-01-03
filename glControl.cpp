// glControl.cpp: implementation of the CglControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "example.h"
#include "glControl.h"
#include "glCamera.h"
#include "OpenGL.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CglControl::CglControl(COpenGL *pGL)
{
	for(int i=0;i<KS_ALL;i++)
		m_keyStatus[i]=false;
	m_bMouseLDown=false;
	m_bMouseRDown=false;
	m_pOpenGL=pGL;
	m_pCamera=pGL->m_pCamere;
	m_fStep[0]=0.01;
	m_fStep[1]=0.01;
	m_fKeyStep = 3;
}

CglControl::~CglControl()
{

}

bool CglControl::PreTranslateMessage(unsigned int message, unsigned int wParam, unsigned int lParam)
{
	CPoint pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	switch(message)
	{
		//鼠标消息
	case WM_LBUTTONDOWN:
		m_pOpenGL->OnMouse(message,pt);
		m_MousePos=pt;
		m_bMouseLDown = TRUE;
		SetCapture(m_pOpenGL->m_hWnd);
		break;
	case WM_LBUTTONUP:
		m_pOpenGL->OnMouse(message,pt);
		m_bMouseLDown = FALSE;
		ReleaseCapture();
		break;
	case WM_RBUTTONDOWN:
		m_pOpenGL->OnMouse(message,pt);
		m_MousePos=pt;
		m_bMouseRDown = TRUE;
		SetCapture(m_pOpenGL->m_hWnd);
		break;
	case WM_RBUTTONUP:
		m_pOpenGL->OnMouse(message,pt);
		m_bMouseRDown = FALSE;
		ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		m_pOpenGL->OnMouse(message,pt);
		return MouseCtrlView(message,pt);//鼠标控制视图
		break;
	case WM_MOUSEWHEEL:
		m_pOpenGL->OnMouse(message,pt);
		pt.x = short(HIWORD(wParam))/30;	//取得滚轮滚动距离
		return MouseCtrlView(message,pt);
		break;
		//键盘消息
	case WM_KEYDOWN:
		if(wParam<=0x2f||(wParam>=0x5B&&wParam<=0xA5))
			return  SetKeyStatus(wParam,true);
		return  SetKeyStatus(wParam,true);//MapVirtualKey(wParam,MAPVK_VK_TO_CHAR)
		break;
	case WM_KEYUP:
		if(wParam<=0x2f||(wParam>=0x5B&&wParam<=0xA5))
			return  SetKeyStatus(wParam,false);
		SetKeyStatus(wParam,false);
		break;
	default:
		return false;
	}
	return true;
}

bool CglControl::MouseCtrlView(int message, CPoint pt)
{
	bool ret=false;
	if(message==WM_MOUSEMOVE)
	{
		if(m_bMouseLDown)//移动
		{
			CPoint dis;
			dis = pt - m_MousePos;
			m_pCamera->Move(0,dis.x*m_fStep[0]);
			m_pCamera->Move(1,-dis.y*m_fStep[0]);
			m_MousePos = pt;
			ret = true;
		}
		else if(m_bMouseRDown)//旋转
		{
			CPoint dis;
			dis = pt - m_MousePos;
			m_pCamera->Rotate(0,-dis.x*m_fStep[1]);
			m_pCamera->Rotate(1,-dis.y*m_fStep[1]);
			m_MousePos = pt;
			ret = true;
		}
	}
	else if(message==WM_MOUSEWHEEL)
	{
		m_pCamera->Move(2,pt.x*m_fStep[0]);
		ret = true;
	}
	if(ret)
		InvalidateRect(m_pOpenGL->m_hWnd,NULL,TRUE);
	return ret;
}

bool CglControl::SetKeyStatus(unsigned int nChar, bool bVal)
{
	m_pOpenGL->OnKey(nChar,bVal);
	switch(nChar)
	{
	case'Q':
		m_keyStatus[KS_M_BACK]=bVal;
		break;
	case 'E':
		m_keyStatus[KS_M_FRONT]=bVal;
		break;
	case 'A':
		m_keyStatus[KS_M_LEFT]=bVal;
		break;
	case 'D':
		m_keyStatus[KS_M_RIGHT]=bVal;
		break;
	case 'W':
		m_keyStatus[KS_M_UP]=bVal;
		break;
	case 'S':
		m_keyStatus[KS_M_DOWN]=bVal;
		break;
	case'U':
		m_keyStatus[KS_R_FRONT]=bVal;
		break;
	case 'O':
		m_keyStatus[KS_R_BACK]=bVal;
		break;
	case 'J':
		m_keyStatus[KS_R_LEFT]=bVal;
		break;
	case 'L':
		m_keyStatus[KS_R_RIGHT]=bVal;
		break;
	case 'I':
		m_keyStatus[KS_R_UP]=bVal;
		break;
	case 'K':
		m_keyStatus[KS_R_DOWN]=bVal;
		break;
	case '-':
	case 189:
		m_keyStatus[KS_M_STEP_N]=bVal;
		break;
	case '=':
	case 187:
		m_keyStatus[KS_M_STEP_P]=bVal;
		break;
	case '[':
	case 219:
		m_keyStatus[KS_R_STEP_N]=bVal;
		break;
	case ']':
	case 221:
		m_keyStatus[KS_R_STEP_P]=bVal;
		break;
	case VK_ESCAPE:
		m_keyStatus[KS_RESTORE]=bVal;
		break;
	default :
		return false;
	}
	KeyboardCtrlView();
	return true;
}

bool CglControl::KeyboardCtrlView()
{
	bool bHaveKeyDown = false;
	//平移
	if(m_keyStatus[KS_M_FRONT])
	{
		m_pCamera->Move(2,m_fKeyStep*m_fStep[0]);
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_M_BACK])
	{
		m_pCamera->Move(2,-m_fKeyStep*m_fStep[0]);
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_M_LEFT])
	{
		m_pCamera->Move(0,-m_fKeyStep*m_fStep[0]);
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_M_RIGHT])
	{
		m_pCamera->Move(0,+m_fKeyStep*m_fStep[0]);
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_M_UP])
	{
		m_pCamera->Move(1,m_fKeyStep*m_fStep[0]);
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_M_DOWN])
	{
		m_pCamera->Move(1,-m_fKeyStep*m_fStep[0]);
		bHaveKeyDown = true;
	}

	//旋转
	if(m_keyStatus[KS_R_FRONT])
	{
		m_pCamera->Rotate(2,m_fKeyStep*m_fStep[1]);
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_R_BACK])
	{
		m_pCamera->Rotate(2,-m_fKeyStep*m_fStep[1]);
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_R_LEFT])
	{
		m_pCamera->Rotate(0,m_fKeyStep*m_fStep[1]);
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_R_RIGHT])
	{
		m_pCamera->Rotate(0,-m_fKeyStep*m_fStep[1]);
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_R_UP])
	{
		m_pCamera->Rotate(1,m_fKeyStep*m_fStep[1]);
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_R_DOWN])
	{
		m_pCamera->Rotate(1,-m_fKeyStep*m_fStep[1]);
		bHaveKeyDown = true;
	}
	//移动速度
	if(m_keyStatus[KS_M_STEP_N])	//减小速度
	{
		m_fStep[0]*=0.9;
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_M_STEP_P])	//增加速度
	{
		m_fStep[0]*=1.1;
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_R_STEP_N])	//减小速度
	{
		m_fStep[1]*=0.9;
		bHaveKeyDown = true;
	}
	if(m_keyStatus[KS_R_STEP_P])	//增加速度
	{
		m_fStep[1]*=1.1;
		bHaveKeyDown = true;
	}

	if(m_keyStatus[KS_RESTORE])	//复原位置
	{
		//m_pCamera->Init();
		m_pCamera->LoadCamera();
		bHaveKeyDown = true;
	}
	if(bHaveKeyDown)
		InvalidateRect(m_pOpenGL->m_hWnd,NULL,FALSE);
	return bHaveKeyDown;
}

void CglControl::SetSpeed(float ms, float rs)
{
	m_fStep[0]=ms;
	m_fStep[1]=rs;
}
