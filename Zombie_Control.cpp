#include "stdafx.h"
#include "Zombie_Control.h"
#define size 40

Zombie_Control::Zombie_Control(void)
{

}

Zombie_Control::~Zombie_Control(void)
{
	for (vector<Zombie*>::iterator zombieIter = zombies.begin(); zombieIter != zombies.end(); zombieIter++)
		delete *zombieIter;
	zombies.clear();
}

void Zombie_Control::createZombie()
{
	int Rand=rand();
	if(Rand%50==0)
	{
		Zombie *newZombie=new Zombie;
		CglVector3 pos;
		//pos.Set(20*size,0,-(rand()%5+1)*5*size);//z坐标为{-5,-10,-15,-20,-25}中的一个
		pos.Set((rand()%5-2)*50,2*size,-25*size);//z坐标为{-5,-10,-15,-20,-25}中的一个
		//pos.Set(2*size,(rand()%5-2)*50,-25*size);
		newZombie->SetPostion(pos);
		zombies.push_back(newZombie);//添加新的僵尸
	}
}

void Zombie_Control::Update()
{
	createZombie();
	Zombie *zombie;
	for (vector<Zombie*>::iterator zombieIter = zombies.begin(); zombieIter != zombies.end(); )
	{
		zombie=*zombieIter;
		if(zombie->lifemode==ZOMBIE_DEAD)
		{
			zombieIter=zombies.erase(zombieIter);
			delete zombie;
		}
		else
		{
			zombie->Update();
			zombieIter++;
		}
	}

}

void Zombie_Control::Display()
{
	Zombie *zombie;
	CglVector3 pos;
	for (vector<Zombie*>::iterator zombieIter = zombies.begin(); zombieIter != zombies.end(); zombieIter++)
	{
		zombie=*zombieIter;
		pos=zombie->GetPosition();
		glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		zombie->Draw();
		glPopMatrix();
	}
}