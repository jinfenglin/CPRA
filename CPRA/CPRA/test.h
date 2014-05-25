#include "train.h"
using namespace std;

class test :public train
{
public:
	test(BUILDING_METHOD );
	test(BUILDING_METHOD ,int );
	string Chose_Answer();
	void Class_Match(int i,int j);
	void Run();
	void OutPutCRISPR(ofstream &ofs);
	~test();
private:
	int error;
	int correct;
	float accuracy;
};