// glControl.h: interface for the CglControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLCONTROL_H__00C4D92B_FFB4_44B7_BF3A_93B7226729DA__INCLUDED_)
#define AFX_GLCONTROL_H__00C4D92B_FFB4_44B7_BF3A_93B7226729DA__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class COpenGL;
class CglCamera;
class CglControl  
{
public:
	void SetSpeed(float ms,float rs);
	bool KeyboardCtrlView();
	
	bool PreTranslateMessage(unsigned int message,unsigned int wParam,unsigned int lParam);
	CglControl(COpenGL *pGL);
	virtual ~CglControl();

	//按键状态；
	enum KEYSTATUS{KS_M_RIGHT,KS_M_LEFT,KS_M_UP,KS_M_DOWN,KS_M_BACK,KS_M_FRONT,\
		KS_R_LEFT,KS_R_RIGHT,KS_R_UP,KS_R_DOWN,KS_R_FRONT,KS_R_BACK,\
		KS_M_STEP_N,KS_M_STEP_P,KS_R_STEP_N,KS_R_STEP_P,\
		KS_RESTORE,KS_ALL
		}KeyVal;
	bool m_keyStatus[KS_ALL];

	//鼠标按键状态
	bool m_bMouseLDown;	
	bool m_bMouseRDown;	
	CPoint m_MousePos;

	COpenGL *m_pOpenGL;	
	CglCamera *m_pCamera;
private:
	bool SetKeyStatus(unsigned int nChar,bool bVal);
	bool MouseCtrlView(int message,CPoint pt);
	double m_fStep[2];//移动和旋转步长缩放倍率
	float m_fKeyStep;//键盘按下一个运动命令代表移动步长
};

#endif // !defined(AFX_GLCONTROL_H__00C4D92B_FFB4_44B7_BF3A_93B7226729DA__INCLUDED_)
