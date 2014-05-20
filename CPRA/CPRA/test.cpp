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
void test::Class_Match(int i,int j)
{
	CRISPR_Index CPI=CIndex[i];
    Standar_Data_Formate Test_Data=Test_Data_Head[j];
	
	for(int x=0;x<CPI.size;x++)
	{
		CRISPR_Head Array=*CPI.pointer_box[x];
		CRISPR_Segment *Seg_Pointer=Array.head.next;
		float match=0;
		float Credite=Revised_Value(Seg_Pointer->attr._Value,Seg_Pointer->attr._Length,D_num);//scale the value with length to compensate long array
		for(int y=0;y<Array.length;y++)
		{
			if(affinity(*Seg_Pointer,Test_Data))
			{
				match+=Credite*Seg_Pointer->attr._Length/Test_Data._content.length();
			}
		}
		match=match*Array.Credit_in_Population;//fix the matchness with the credits this array have among the population.
		if(match>0)
			vote_board[i].agree++;
		else if(match<0)
			vote_board[i].reject++;
		else 
			vote_board[i].neutral++;
		match_board[i]+=match;//It stands for how strong the group believe it belongs to itself
	}

}//test if the i th CIRSPR ARRAY match the j th test data
void test::Run()
{
	train::Test_Run();
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
