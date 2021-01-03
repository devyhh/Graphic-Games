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
	vector<Zombie*> zombies;//记录僵尸的数组（栈）
	//int count;//僵尸数量
};