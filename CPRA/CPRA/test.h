#include "train.h"
using namespace std;

class test :public train
{
public:
	test(BUILDING_METHOD );
	test(BUILDING_METHOD ,int );
	string Chose_Answer();
	void Run();
	~test();
private:
	int error;
	int correct;
	float accuracy;
};