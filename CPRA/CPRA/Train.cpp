#include "train.h"

train::train(BUILDING_METHOD bm):ReadData()//train/test seperated version intialization
{
	method=bm;
}
train::train(int n,BUILDING_METHOD bm):ReadData(n)//N_flod version intialization
{
	method=bm;
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
				Add_To_Index(i,j);//Add the node i in CHead into the index j
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
} //set the segment_length
float train::Entropy()//entropy is public for a data set
{
	float entropy=0;
	for(int i=0;i<class_num;i++)
	{
		float class_portion=(float)(class_portion_raw[i])/train_num;
		entropy+=-class_portion*log(class_portion)/log(2.0);
	}
	Entropy_S=entropy;
	return entropy;
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
	/*Test information gain*/
	Information_Gain(CHead);
	cout<<this->test_num<<endl;
}
float  train::Information_Gain(CRISPR_Head *CHP)//Information gain is private,decide by the CRISPR&attribute
{
	float Inf_Gain;
	CHP->IG_num=0;
	int c=0;
	for(int i=0;i<Train_Data_Head[0]._content.length();i+=CHP->segment_length)
	{
		CHP->IG_num++;//Calculate how many IG node is contained
		CHP->IG[c].IGS[0].content=Train_Data_Head[0]._content.substr(i,CHP->segment_length);//copy the content to the first IGS
		CHP->IG[c].IGS_num=1;//record how many subnode it contains
		CHP->IG[c].start=i;//record starting point
		c++;
	}
	for(int i=1;i<train_num;i++)
		for(int j=0;j<Train_Data_Head[i]._content.length();j+=CHP->segment_length)
		{
			for(int n=0;n<CHP->IG_num;n++)
			{
				if(CHP->IG[n].start==j)//Address matches then compare the content
				{
					int x=0;
					for(;x<CHP->IG_num;x++)//search the IGS
					{
						if(CHP->IG[n].IGS[x].content==Train_Data_Head[i]._content.substr(j,CHP->segment_length))//content don't matches regist new one
							break;
					}
					if(x==CHP->IG_num)
					{
						CHP->IG[n].IGS[CHP->IG[n].IGS_num].content=Train_Data_Head[i]._content.substr(j,CHP->segment_length);
						CHP->IG[n].IGS_num++;
					}
					if(Train_Data_Head[i]._class==CHP->class_name)//it is positive example
						CHP->IG[n].IGS[x].positive++;
					else                                          //negative example
						CHP->IG[n].IGS[x].negative++;
					break;
				}
			}
		}
	/*string content_register[MAX_SEGMENT_TYPE];//record all the content in a single segment ever appeared.
	int content_num=0;
	int portion_register[MAX_SEGMENT_TYPE][3];//how many kind of value do we have in a single segment.the 2nd 3rd layer record the example is positive or negative
	int portion_num=0;
	for(int i=0;i<train_num;i++)
	{
		for(int j=0;j<Train_Data_Head[i]._content.length();j+=CHP->segment_length)//J is the start point of each segments checked in the sequence
		{
			int end=0;
			if(j+CHP->segment_length>Train_Data_Head[i]._content.length())
				end=Train_Data_Head[i]._content.length();
			else
				end=j+CHP->segment_length-1;
			/*Segment are decided,build the register
			if(content_num==0)//Add the fisrt segment
			{
				content_num++;
				portion_num++;
				content_register[0]=Train_Data_Head[0]._content.substr(j,end);
				portion_register[0][0]=1;
				if(Train_Data_Head[0]._class==CHP->class_name)
				{portion_register[0][1]=1;portion_register[0][2]=0;}
				else
				{portion_register[0][1]=0;portion_register[0][2]=1;}
			}
			else //check out whether the segment is in the register
			{
				for(int n=0;n<content_num;n++)
				{
					if(content_register[n]==Train_Data_Head[i]._content.substr(j,end))//find it in register
						continue;
					else//register it
					{
						content_num++;
						portion_num++;
						content_register[content_num]=Train_Data_Head[i]._content.substr(j,end);
						portion_register[portion_num][0]=1;
						if(Train_Data_Head[i]._class==CHP->class_name)
						{portion_register[portion_num][1]++;}
						else
						{portion_register[portion_num][2]++;}
					}
				}
			}
		} 
	}//end of for with parameter of i*/
	/*registers are built,start to calculate the information gain
	int second_item=Second_Item_IG(portion_register,portion_num);*/
	cout<<"ljk"<<endl;
	//Inf_Gain=CIndex->entropy-second_item;
	return Inf_Gain;
}
/*float train::Second_Item_IG(int portion_register[][3],int num)//num stand for the No of attribute whose IG wanted
{
	float second_item=0;
	float entropy_second_item=0;
	for(int i=0;i<num;i++)//each round calculate one attribute's IG
	{	
		float p1=portion_register[i][1]/portion_register[i][0];
		float p2=portion_register[i][2]/portion_register[i][0];
		//entropy_second_item=p1*log(p1)/log(2)+p2*log(p2)/log(2);
		float portion=(float)portion_register[i][0]/train_num;
		second_item+=portion*entropy_second_item;
	}
	return -secon_item;
}*/