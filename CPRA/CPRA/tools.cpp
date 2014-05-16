#include "tools.h"
tools::tools()
{}
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