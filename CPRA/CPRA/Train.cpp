#include "train.h"

train::train(BUILDING_METHOD bm):ReadData()//train/test seperated version intialization
{
	method=bm;
}
train::train(int n,BUILDING_METHOD bm):ReadData(n)//N_flod version intialization
{
	method=bm;
}
void train::Test_Run()
{
	Monk_Problem_Read();
	CRISPR_Population_Size=0.05*total_num;
	this->Count_Class_Num();
	Generate_CRISPR_Population();
	Build_CRISPR_Index();
	Set_Range_Random();
	Entropy();
	cout<<this->test_num<<endl;
}
void Define_Segment_Length()
{

}
bool train::Generate_CRISPR_Population()
{
	//seperate class first 
	//Then define the length of each CRISPR's segments according to the {array length,number of CRISPR in this group}
	SEGMENT_KIND type_flag;
	if(total_num<=0)
		return false;
	//CHead=(CRISPR_Head *)malloc(sizeof(CRISPR_Head)*CRISPR_Population_Size);could not intialize the string with malloc
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
	//what if the population is smaller than the class type
	if(CRISPR_Population_Size<class_num)
		cout<<"population is smaller than the class type"<<endl;
	int each_class_num=CRISPR_Population_Size/class_num;
	int cp_each=each_class_num;
	int rest_num=CRISPR_Population_Size%class_num;
	int class_pointer=0;
	for(int i=0;i<CRISPR_Population_Size;i++)
	{
		temp->Credit_in_Population=0;
		temp->head=NULL;
		temp->length=0;
		temp->type=type_flag;
		temp->class_name=class_index[class_pointer];
		cp_each--;
		if(cp_each==0)
		{
			class_pointer++;
			cp_each=each_class_num;
			if(rest_num!=0)//distribute the rest to different class
			{
				rest_num--;
				cp_each++;
			}
		}
		temp++;
	}
	return true;
}
bool train::Hybird_CRISPR_Generator()//for further versions,not intend to implement recently.
{
	return true;
}
bool train::Initialize_CRISPR_Index()
{
	for(int i=0;i<class_num;i++)
	{
		CIndex[i].class_name=class_index[i];
	}
	return true;
}
bool train::Add_To_Index(int CHead_i,int CIndex_j)
{
	int size=CIndex[CIndex_j].size;
	CIndex[CIndex_j].pointer_box[size]=&CHead[CHead_i];
	CIndex[CIndex_j].size++;
	return true;
	
}
bool train::Build_CRISPR_Index()
{
	Initialize_CRISPR_Index();
	for(int i=0;i<CRISPR_Population_Size;i++)
		for(int j=0;j<class_num;j++)
		{
			if(CHead[i].class_name==CIndex[j].class_name)
			{
				Add_To_Index(i,j);
			}
		}
	return true;
}
bool train::Expand_Population(CRISPR_Index *CIP)
{
	int size=++CIP->size;
	int new_one_location=++CRISPR_Population_Size;
	if(new_one_location>MAX_POPULATION_SIZE||size>MAX_POINTER_NUM)
	{
		cout<<"Overflow when expanding population!"<<endl;
		return false;
	}
	CHead[new_one_location].class_name=CIP->class_name;
	switch (method)
	{
	case _entropy:
		CHead[new_one_location].type=_static;
		break;
	case _random:
		CHead[new_one_location].type=_dynamic;
		break;
	case _hybird:
		cout<<"Error:Utilize Expand methods which contain type parameter!"<<endl;
		return false;
	}
	CIP->pointer_box[size]=&CHead[new_one_location];
	return true;
}//Have not tested yet:Expand should be used only after the initialization of CHead and CIndex.
bool train::Set_Range_Random()
{
	for(int i=0;i<CRISPR_Population_Size;i++)
	{
		CHead[i].segment_length=RandomInt(max_length/3*2)+1;
	}
	return true;
}
float train::Entropy()//entropy is public for a data set
{
	float entropy=0;
	float temp;
	for(int i=0;i<class_num;i++)
	{
		float class_portion=(float)(class_portion_raw[i])/train_num;
		entropy+=-class_portion*log(class_portion)/log(2.0);
	}
	Entropy_S=entropy;
	return entropy;
}
float Information_Gain()//Information gain is private,decide by the CRISPR&attribute