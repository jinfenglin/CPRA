#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
using namespace std;
class tools
{
public:
	tools();
	int RandomInt();
	int RandomInt(int );
	void Output_Result(int correct,int error ,float accuracy,ofstream &ofs);
	~tools();
	void trim(string &str,char ch);
private:
};