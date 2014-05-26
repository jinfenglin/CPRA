#include "test.h"
#define LOG_PATH "..\\log.txt"
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
void test::Class_Match(int i,int j,string dataset)//To test claculate the matchness between i th class with j th testing data
{ 
	//complexity of this fuction is roughly =class_i's population * Array length; 13*50
	CRISPR_Index CPI=CIndex[i];
	Standar_Data_Formate Test_Data;
	if(dataset=="test")
		 Test_Data=Test_Data_Head[j];
	else if(dataset=="train")
		 Test_Data=Train_Data_Head[j];
	
	for(int x=0;x<CPI.size;x++)
	{
		CRISPR_Head Array=*CPI.pointer_box[x];// the x th CRISPR array in the CIndex belong to the i th Class 
		CRISPR_Segment *Seg_Pointer=Array.head.next;//segment pointers to iterate the items on the array
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
		if(!SUPER_FLAG)
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
void test::OutPutCRISPR(ofstream &ofs)
{
	for(int i=0;i<class_num;i++)
		{
			for(int j=0;j<CIndex[i].size;j++)
			{
				//cout<<"CRIPSR array No."<<j<<":"<<"Segment Length="<<CHead[j].segment_length<<" Array_Length="<<CHead[j].length<<" Credit in Population="<<CHead[j].Credit_in_Population<<endl;
				ofs<<"CRIPSR array No."<<j<<":"<<"Segment Length="<<CHead[j].segment_length<<" Array_Length="<<CHead[j].length<<" Credit in Population="<<CHead[j].Credit_in_Population<<endl;
				CRISPR_Segment *sg=CHead[j].head.next;
				for(int x=0;x<CHead[j].length;x++)
				{
					ofs<<sg->attr<<endl;
					sg=sg->next;
				}
			}
	}
}
bool test::Training_Data_Accuracy(ofstream &ofs)//to reflect how many accuracy it has when tested with training data
{
	correct=0;
	error=0;
	for(int j=0;j<train_num;j++)
	{
		cout<<"Training Data No."<<j;
		ofs<<"Training Data No."<<j;
		Reset_Board();
		for(int i=0;i<class_num;i++)
		{
			Class_Match(i,j,"train");
		}
		//cout<<"result is:";
		if(Train_Data_Head[j]._class==Chose_Answer())
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
	Output_Result(correct,error,accuracy,ofs);
	return true;
}
void test::Run()
{	
	clock_t start_point,end_point;
	start_point=clock();
	ofstream ofs;
	ofs.open(LOG_PATH);
	train::Test_Run();
	end_point=clock();
	ofs<<"Training Time="<<(end_point-start_point)/(double)CLOCKS_PER_SEC<<" S"<<endl;
	OutPutCRISPR(ofs);
	Training_Data_Accuracy(ofs);
	correct=0;
	error=0;
	start_point=clock();
	for(int j=0;j<test_num;j++)
	{
		cout<<"Testing Data No."<<j;
		ofs<<"Testing Data No."<<j;
		Reset_Board();
		for(int i=0;i<class_num;i++)
		{
			Class_Match(i,j,"test");
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
	end_point=clock();
	ofs<<"Training Time="<<(end_point-start_point)/(double)CLOCKS_PER_SEC<<" S"<<endl;
	Output_Result(correct,error,accuracy,ofs);
	ofs.close();
}
