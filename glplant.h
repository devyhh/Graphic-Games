// glplant.h: interface for the Cglplant class.
//
//////////////////////////////////////////////////////////////////////
#include "glVector3.h"
#include"OpenGL.h"

//enum ACTIONMODE{WALKING,STOP};
enum PLANT_LIFEMODE{ALIVE,DEAD};

#pragma comment(lib,"GLAUX.lib")

class Cglplant
{
public:
	Cglplant();
	Cglplant(float x,float y);

	int poss_x;
	int poss_y;
	CglVector3 position;

	float scale;
	int price;
	int roll;
	int cd;
	int cdlength;
	int state;
	int lifemode,actionmode;
	float speed;
	float life;
	CglVector3 direction;
	int countFrame,arm_type,leg_type;
	CglFont *pFont;
	char rest_life[100];
	int LoadGLTextures();

	void Update();
	void SetPostion(CglVector3 Position){position=Position;}
	CglVector3 GetPosition() {return position;}
	void draw1();
	void draw2();
	void draw3();
	void draw4();
	void draw5();
	void initialize();
};

