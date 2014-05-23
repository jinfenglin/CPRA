#include "tools.h"
tools::tools()
{
	srand(time(NULL));
}
tools::~tools()
{
}
void tools::trim(string &str,char ch)  //delete all the char ch in the string str
{

	while(str.find(ch)!=string::npos)
	{
		int pos=str.find(ch);
		str.erase(str.find(ch),1);
	}
}
int tools::RandomInt(int n)
{

	return rand()%n;
}
int tools::RandomInt()
{

	return rand();
}
void tools::Output_Result(int correct,int error ,float accuracy,ofstream &ofs)
{	
	accuracy=(float)correct/(correct+error);
	cout<<"Test finished."<<endl;
	cout<<"Right:"<<correct<<" Wrong:"<<error<<endl;
	cout<<"Accuracy:"<<accuracy<<endl;
	ofs<<"Right:"<<correct<<" Wrong:"<<error<<endl;
	ofs<<"Accuracy:"<<accuracy<<endl;
}