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
	
	float max_match=match_board[0];
	string pattern=CIndex[0].class_name;
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
	//complexity of this fuction is roughly =class_i's population * Array length; 13*50
	CRISPR_Index CPI=CIndex[i];
    Standar_Data_Formate Test_Data=Test_Data_Head[j];
	
	for(int x=0;x<CPI.size;x++)
	{
		CRISPR_Head Array=*CPI.pointer_box[x];
		CRISPR_Segment *Seg_Pointer=Array.head.next;
		float match=0;
		for(int y=0;y<Array.length;y++)
		{
			if(affinity(*Seg_Pointer,Test_Data))
			{
				float Credite=Revised_Value(Seg_Pointer->attr._Value,Seg_Pointer->attr._Length,D_num);//scale the value with length to compensate long array
				match+=Credite*Seg_Pointer->attr._Length/Test_Data._content.length();
			}
			Seg_Pointer=Seg_Pointer->next;
		}
		//match=match*Array.Credit_in_Population;//fix the matchness with the credits this array have among the population.
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
	ofstream ofs;
	ofs.open("..\\log.txt");
	train::Test_Run();
	for(int j=0;j<test_num;j++)
	{
		cout<<"Testing Data No."<<j;
		ofs<<"Testing Data No."<<j;
		Reset_Board();
		for(int i=0;i<class_num;i++)
		{
			Class_Match(i,j);
		}
		//cout<<"result is:";
		if(Test_Data_Head[j]._class==Chose_Answer())
		{
			correct++;
			cout<<"correct"<<endl;
			ofs<<"correct"<<endl;
			
		}
		else
		{
			error++;
			cout<<"wrong"<<endl;
			ofs<<"wrong"<<endl;
		}
	}
	cout<<"Test finished."<<endl;
	cout<<"Right:"<<correct<<" Wrong:"<<error<<endl;
	ofs<<"Right:"<<correct<<" Wrong:"<<error<<endl;
	ofs.close();
}
