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