#include "Zombie.h"
#include<vector>

using namespace std;
class Zombie_Control
{
public:
	Zombie_Control(void);
	~Zombie_Control(void);

	void createZombie();
	void Update();
	void Display();
	vector<Zombie*> zombies;//��¼��ʬ�����飨ջ��
	//int count;//��ʬ����
};