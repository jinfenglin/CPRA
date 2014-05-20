#include "test.h"
test::test(BUILDING_METHOD method):train(method)
{
	error=0;
	correct=0;
	accuracy=0;
}
test::test(BUILDING_METHOD method,int n):train(n,method)
{
	error=0;
	correct=0;
	accuracy=0;
}
string test::Chose_Answer()//use matchness and leave the vote aside
{
	string pattern;
	float max_match=match_board[0];
	for(int i=1;i<class_num;i++)
	{
		if(match_board[i]>max_match)
		{
			max_match=match_board[i];
			pattern=CIndex[i].class_name;
		}
	}
	return pattern;
}
void test::Run()
{
	for(int j=0;j<test_num;j++)
	{
		Reset_Board();
		for(int i=0;i<class_num;i++)
		{
			Class_Match(i,j);
		}
		if(Test_Data_Head[j]._class==Chose_Answer())
		{
			correct++;
		}
		else
		{
			error++;
		}
	}
}
