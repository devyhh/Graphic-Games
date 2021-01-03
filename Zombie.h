#pragma once
#include"OpenGL.h"

enum ACTIONMODE{WALKING,STOP};
enum ZOMBIE_LIFEMODE{ZOMBIE_ALIVE,ZOMBIE_DEAD};

#pragma comment(lib,"GLAUX.lib")

class Zombie
{
public:
	Zombie(void);
	~Zombie(void);
	void Draw();
	void atteck();
	void SetPostion(CglVector3 Position){position=Position;}
	void SetDirection(CglVector3 Direction){direction=Direction;}
	void Update();
	CglVector3 GetPosition() {return position;}
	CglVector3 GetDirection() {return direction;}
	int LoadGLTextures();

	int actionmode,lifemode;
private:
	CglVector3 direction;
	//CVector head;
	CglVector3 position;
	float speed;
	float life;
	int countFrame,arm_type,leg_type;
	CglFont *pFont;
	char rest_life[100];
};