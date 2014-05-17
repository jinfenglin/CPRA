#include "train.h"

train::train(BUILDING_METHOD bm):ReadDate()//train/test seperated version intialization
{
	method=bm;
}
train::train(int n,BUILDING_METHOD bm):ReadDate(n)//N_flod version intialization
{
	method=bm;
}
void train::Test_Run()
{
	Monk_Problem_Read();
	CRISPR_Population_Size=0.05*total_num;
	Generate_CRISPR_Population();
	cout<<this->test_num<<endl;
}
void Define_Segment_Length()
{

}
bool train::Generate_CRISPR_Population()
{
	SEGMENT_KIND type_flag;
	if(total_num<=0)
		return false;
	CHead=(CRISPR_Head *)malloc(sizeof(CRISPR_Head)*CRISPR_Population_Size);
	CRISPR_Head *temp=CHead;
	if(method==_entropy)
		type_flag=_static;
	else if(method==_random)
		type_flag=_dynamic;
	else
	{
		Hybird_CRISPR_Generator();
		return true;
	}
	for(int i=0;i<CRISPR_Population_Size;i++)
	{
		temp->Credit_in_Population=0;
		temp->head=NULL;
		temp->length=0;
		temp->type=type_flag;
		temp++;
		if(type_flag==_static)
		{
			int step=0;
			if(CRISPR_Population_Size>max_length/2)
				step=1;
			else
				step=(max_length/2)/CRISPR_Population_Size;
		}
		else //here we could only have 2 kind of type ,hybird jumped out before reaching here
			temp->segment_length=0;
	}
	return true;
}
bool train::Hybird_CRISPR_Generator()//for further versions,not intend to implement recently.
{
	return true;
}