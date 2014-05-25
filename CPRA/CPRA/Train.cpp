#include "train.h"

train::train(BUILDING_METHOD bm):ReadData()//train/test seperated version intialization
{
	method=bm;
}
train::train(int n,BUILDING_METHOD bm):ReadData(n)//N_flod version intialization
{
	method=bm;
}
train::~train()
{}
bool train::affinity(CRISPR_Segment CH,Standar_Data_Formate data)//calculate the affinity between data and segments in the array
{
	int start=CH.attr._Start;
	int length=CH.attr._Length;
	if(CH.attr.content==data._content.substr(start,length))
		return true;
	else 
		return false;
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
	int each_class_num=CRISPR_Population_Size/class_num;//average population size in each class
	int cp_each=each_class_num;
	int rest_num=CRISPR_Population_Size%class_num;//if it could not be divided totally
	int class_pointer=0;
	for(int i=0;i<CRISPR_Population_Size;i++)
	{
		temp->Credit_in_Population=0;
		temp->head.next=NULL;
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
bool train::Add_To_Index(int CHead_i,int CIndex_j)// link the i th array in CHead to the CIndex's box
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
bool train::Set_Range_Random()//set the segment_length randomly decide the length
{
	 int limited_length=max_length/3*2;// parameter
	 //int limited_length=max_length; 
	for(int i=0;i<CRISPR_Population_Size;i++)
	{
		CHead[i].segment_length=RandomInt(limited_length)+1;//the length should not longer than the limited length
	}
	return true;
} 
float train::Entropy()//entropy is public for a data set
{
	float entropy=0;
	for(int i=0;i<class_num;i++)
	{
		float class_portion=(float)(class_portion_raw[i])/train_num;
		entropy+=-class_portion*log(class_portion)/log(2.0);
	}
	Entropy_S=entropy;
	CIndex->entropy=entropy;
	return entropy;
}
void train::Test_Run()
{
	cout<<"Training....."<<endl;
	Monk_Problem_Read();
	CRISPR_Population_Size=0.05*total_num;//Population size
	Count_Class_Num();//count how many class type it has
	Generate_CRISPR_Population();
	Build_CRISPR_Index();
	Set_Range_Random();//each CRISPR have a random range,but within a CRISPR array the range is same.It is different with the random methods.
	Entropy();
	for(int i=0;i<CRISPR_Population_Size;i++)
	{
		Information_Gain(&CHead[i]);
		Build_CRISPR(&CHead[i]);
	}
	int iteration=1; //how many times the iteration goes to see if this helps to improve the performance
	for(int x=0;x<iteration;x++)
		for(int i=0;i<train_num;i++)
		{
			for(int j=0;j<class_num;j++)
			{
				//Train_Credit(j,i);//set the j th class's credit with i th data 
			                  //This part take the most of time of training
			}
			cout<<"Processing Date No."<<i<<endl;
		}
		cout<<"Training finished."<<endl;
}
bool  train::Information_Gain(CRISPR_Head *CHP)//Information gain is private for CRISPR array&attribute
{
	//Here CHP is a pointer refer to a single array
	float Inf_Gain;
	CHP->IG_num=0;
	int c=0;
	for(int i=0;i<Train_Data_Head[0]._content.length();i+=CHP->segment_length)// we defaultly consider first segments' starting point is 0
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
					for(;x<CHP->IG[n].IGS_num;x++)//search the IGS
					{
						if(CHP->IG[n].IGS[x].content==Train_Data_Head[i]._content.substr(j,CHP->segment_length))//content don't matches regist new one
							break;
					}
					if(x==CHP->IG[n].IGS_num)
					{
						CHP->IG[n].IGS[CHP->IG[n].IGS_num].content=Train_Data_Head[i]._content.substr(j,CHP->segment_length);
						CHP->IG[n].IGS_num++;
					}
					if(Train_Data_Head[i]._class==CHP->class_name)//it is positive example
					{
						CHP->IG[n].IGS[x].positive++;
						CHP->IG[n].Positive_sum++;
					}
					else                                          //negative example
					{
						CHP->IG[n].IGS[x].negative++;
						CHP->IG[n].Negative_sum++;
					}
					break;
				}
			}
		}
		Get_IG(CHP);
	return true;
}
bool train::Get_IG(CRISPR_Head *CHP)//'num' stands for the No of attribute,whose IG wanted
{
	int IG_number=CHP->IG_num;
	
	for(int n=0;n<IG_number;n++)
	{
		float second_item=0;
		float entropy_for_subnode=0;
		for(int i=0;i<CHP->IG[n].IGS_num;i++)
		{
			int positive=CHP->IG[n].IGS[i].positive;
			int negative=CHP->IG[n].IGS[i].negative;
			int pn_sum=positive+negative;
			float portion=(float)pn_sum/total_num;
			double p1=(double)positive/pn_sum;
			double p2=(double)negative/pn_sum;
			if(p1==0||p2==0)
				entropy_for_subnode=0;
			else
				entropy_for_subnode=p1*log(p1)/log(2.0)+p2*log(p2)/log(2.0);
			second_item+=-portion*entropy_for_subnode;
		}
		CHP->IG[n].Information_Gain=CIndex->entropy-second_item; //got the final IG of each attribute and store them in the array
	}
	return true;
}
bool train::Build_CRISPR(CRISPR_Head *CHP)//After getting the IG,use IG as guid to build up the CRISPR array
{
	//This is one of the methods to build the array
	//Idea:static CRISPR length,transcedent aborbing rate
	//IG decide which attribute picked first
	Sort(CHP);//Sort according to the IG value
	float transcedent=1.0; //we don't know how many spacers are enough
	float drop_step=0.8;
	for(int i=0;i<CHP->IG_num;i++)//It is sorted thus from 0->IG_num, IG decrease
	{
		int absorb=CHP->IG[i].IGS_num*transcedent;
		if(absorb==0)
			absorb=1; //at least take 1 attribute from each attribute
		Sort(CHP->IG[i]);//Sort the options accroding to the difference of positive&negative
		for(int j=0;j<absorb;j++)//go through the avilable options
		{
			CRISPR_Add(*CHP,i,j);
			CHP->length++;
		}
		transcedent*=drop_step;
	}
	return true;
}
bool train::CRISPR_Add(CRISPR_Head &CHP,int i,int j)//i is the NO of attribtue j is the No of avilable option.This function add the jth IGS of i th IG in to the Array
{                                                  //Transfer this option into the segment and add to the CHP->head part
	Information_Gain_Subnode IGS=CHP.IG[i].IGS[j];//thsi variable is just for short
	CRISPR_Segment *temp=new CRISPR_Segment();    //Creat new entity and give value to it,stored in temp
	temp->attr.content=IGS.content;               
	temp->attr._Start=CHP.IG[i].start;
	temp->attr._Length=CHP.segment_length;
	temp->attr._Value=IGS.positive-IGS.negative;
	temp->next=NULL;
	Add_To_Tail(CHP.head,temp);//got the pointer at the end of head
	return true;
}
CRISPR_Segment* train::Add_To_Tail(CRISPR_Segment &CHH,CRISPR_Segment *temp)
{
	CRISPR_Segment *CSP=&CHH;
	while(CSP->next!=NULL)
		CSP=CSP->next;
	CSP->next=temp;
	return CSP;
}
bool train::Sort(CRISPR_Head *CHP)//arrange the CRISPR array from high IG to low IG
{
	Information_Gain_Node *IGbox=CHP->IG;
	int size=CHP->IG_num;
	for(int i=size-1;i>=0;i--)
		for(int j=0;j<=i-1;j++)
		{
			if(IGbox[j].Information_Gain<IGbox[j+1].Information_Gain)
			{
				Information_Gain_Node temp;
				temp=IGbox[j];
				IGbox[j]=IGbox[j+1];
				IGbox[j+1]=IGbox[j];
			}
		}
	return true;
}
bool train::Sort(Information_Gain_Node &IGN)//arrange the segments in IG array from high abs(Value) to low abs(Value)
{
	int size=IGN.IGS_num;
	for(int i=size-1;i>=0;i--)
		for(int j=0;j<=i-1;j++)
		{
			int dif_j1=abs(IGN.IGS[j].positive-IGN.IGS[j].negative);
			int dif_j2=abs(IGN.IGS[j+1].positive-IGN.IGS[j+1].negative);
			if(dif_j1<dif_j2)
			{
				Information_Gain_Subnode temp;
				temp=IGN.IGS[j];
				IGN.IGS[j]=IGN.IGS[j+1];
				IGN.IGS[j+1]=temp;
			}
		}
		return true;
}
float train::Revised_Value(int value ,int length,int digit_posb_num)//scale the value according to the length of the array
{
	float value_cp=value;
	value_cp*=1-1/pow((float)digit_posb_num,length);
	return value_cp;
}
bool train::Reset_Board()
{
	for(int i=0;i<class_num;i++)
	{
		vote_board[i].agree=0;
		vote_board[i].neutral=0;
		vote_board[i].reject=0;
		match_board[i]=0;
	}
	return true;
}
bool train::Train_Credit(int i,int j)//set the credit for each CRISPR array
{
	CRISPR_Index CPI=CIndex[i];
    Standar_Data_Formate Train_Data=Train_Data_Head[j];
	
	for(int x=0;x<CPI.size;x++)
	{
		CRISPR_Head Array=*CPI.pointer_box[x];
		CRISPR_Segment *Seg_Pointer=Array.head.next;
		float match=0;
		
		for(int y=0;y<Array.length;y++)
		{
			float Credite=Revised_Value(Seg_Pointer->attr._Value,Seg_Pointer->attr._Length,D_num);//scale the value with length to compensate long array,but the effect too small
			if(affinity(*Seg_Pointer,Train_Data))//If it segment doesn't match means it is not recognized,when it is recognized if the match is positive add match score else decrease it.
			{
				match+=Credite*Seg_Pointer->attr._Length/Train_Data._content.length();//value is positive + match else minus
			}
			Seg_Pointer=Seg_Pointer->next;
		}
		if(match>0)
			if(Train_Data._class==CPI.class_name)
				CPI.pointer_box[x]->Credit_in_Population++;
			else
				CPI.pointer_box[x]->Credit_in_Population--;
		else if(match<0)
			if(Train_Data._class==CPI.class_name)
				CPI.pointer_box[x]->Credit_in_Population--;
			else
				CPI.pointer_box[x]->Credit_in_Population++;
	}
	return true;
}