#include "stdafx.h"
#include "plant-control.h"
#define size 3

plant_control::plant_control(void)
{

}

plant_control::~plant_control(void)
{
	for (vector<Cglplant*>::iterator zombieIter = plants.begin(); zombieIter != plants.end(); zombieIter++)
		delete *zombieIter;
	plants.clear();
}

void plant_control::create()
{
	int Rand=rand();
	if(Rand%200==0)
	{
		Cglplant *newplant=new Cglplant;
		CglVector3 pos;
		pos.Set(20*size,0,(rand()%5+1)*5*size);//z坐标为{-5,-10,-15,-20,-25}中的一个
		newplant->SetPostion(pos);
		plants.push_back(newplant);//添加新的僵尸
	}
}

void  plant_control::Update()
{
	create();
	Cglplant *plant;
	for (vector<Cglplant*>::iterator plantIter = plants.begin(); plantIter != plants.end(); )
	{
		plant=*plantIter;
		if(plant->lifemode==DEAD)
		{
			plantIter=plants.erase(plantIter);
			delete plant;
		}
		else
		{
			plant->Update();
			plantIter++;
		}
	}

}

void plant_control::Display()
{
	Cglplant *plant;
	CglVector3 pos;
	for (vector<Cglplant*>::iterator plantIter = plants.begin(); plantIter != plants.end(); plantIter++)
	{
		plant=*plantIter;
		pos=plant->GetPosition();
		glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		int Rand=rand();
		if(Rand%6==0)
		{
			int rr=rand()%6+1;
			if(rr==1)
				plant->draw1();
			if(rr==2)
				plant->draw2();
			if(rr==3)
				plant->draw3();
			if(rr==4)
				plant->draw4();
			if(rr==5)
				plant->draw5();
		}
		glPopMatrix();
	}
}