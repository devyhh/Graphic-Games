#include "glplant.h"
#include<vector>

using namespace std;
class plant_control
{
public:
	plant_control(void);
	~plant_control(void);

	void create();
	void Update();
	void Display();
	vector<Cglplant*> plants;//��¼���飨ջ��
};