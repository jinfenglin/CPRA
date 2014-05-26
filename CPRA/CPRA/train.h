#include "ReadData.h"
#include <malloc.h>
#include <stdlib.h>
#include <cmath>
#define _WITHOUT_CREDIT_TRAIN
#ifdef _WITHOUT_CREDIT_TRAIN
#define SUPER_FLAG true
#else
#define SUPER_FLAG false
#endif
enum BUILDING_METHOD{_entropy,_random,_hybird};
enum SEGMENT_KIND {_dynamic,_static};
#define MAX_POPULATION_SIZE 50
#define MAX_POINTER_NUM 20
#define MAX_SEGMENT_TYPENUM 150
 struct Attribute
 {
	 int _Start;
	int _Length;
	int _Value;
	string content;
	Attribute():content("") 
	{
		_Start=0;
		_Length=0;
		_Value=0;
		//float information_gain;
	}
	friend ostream& operator <<(ostream &out,Attribute value)
	{
		out<<"Start:"<<value._Start<<" Length:"<<value._Length<<" Value:"<<value._Value<<" Content="<<value.content;
		return out;
	}
	friend ofstream& operator<<(ofstream &out,Attribute value)
	{
		out<<"Start:"<<value._Start<<" Length:"<<value._Length<<" Value:"<<value._Value<<" Content="<<value.content;
		return out;
	}
 };
struct CRISPR_Segment
{
	Attribute attr;
	CRISPR_Segment *next;
	CRISPR_Segment& operator =(CRISPR_Segment &value)//copy the values
	{
		attr._Length=value.attr._Length;
		attr._Start=value.attr._Start;
		attr._Value=value.attr._Value;
		attr.content=value.attr.content;
		next=value.next;
		return *this;
	}
	CRISPR_Segment():attr()
	{
		next=NULL;
	}
};
struct Information_Gain_Subnode
{
	string content; 
	int positive;
	int negative;
	Information_Gain_Subnode():content(""),positive(0),negative(0)
	{}
	Information_Gain_Subnode& operator=(Information_Gain_Subnode &value)
	{
		content=value.content;
		negative=value.negative;
		positive=value.positive;
		return *this;
	}
};
struct Information_Gain_Node
{
	float Information_Gain;
	int   start;
	int IGS_num;
	int Positive_sum;
	int Negative_sum;
	Information_Gain_Subnode IGS[MAX_SEGMENT_TYPENUM];
	Information_Gain_Node():start(0),IGS_num(0)
	{
		Positive_sum=0;
		Negative_sum=0;
	}
	Information_Gain_Node& operator=(Information_Gain_Node& IGN)
	{
		for(int i=0;i<IGN.IGS_num;i++)
			IGS[i]=IGN.IGS[i];
		IGS_num=IGN.IGS_num;
		Information_Gain=IGN.Information_Gain;
		Negative_sum=IGN.Negative_sum;
		Positive_sum=IGN.Positive_sum;
		start=IGN.start;
		return *this;

	}
};
struct Vote_Node
{
	int agree;
	int reject;
	int neutral;
};
struct CRISPR_Head
{
	CRISPR_Segment head;//pointer to the content of an individual CRISPR
	int length;          //the length of the CRISPR
	int Credit_in_Population;//Describe how reliable this CRISPR is
	string class_name;
	Information_Gain_Node IG[MAX_SEGMENT_TYPENUM];//Here is a small problem but it works
	int IG_num;//record how many member IG array holds
	SEGMENT_KIND type;       //static CRIPSR have same length ,dynamic one has variable length
	int segment_length;  //if the type is _static then this item is accord with the value in CRISPR_Segment _Length 
                         //else segment_length==0 _Length record the length of each segment
	//clean job required here:make the initial part more tight and consist with other struct,don't seperate it
	CRISPR_Head():class_name("undefined")
	{
	};
};
struct CRISPR_Index
{
	string class_name;
	int size;
	float entropy;
	CRISPR_Head *pointer_box[MAX_POINTER_NUM];
	CRISPR_Index():class_name("undefined"),size(0)
	{
		entropy=0;
	};
};
class train:public ReadData
{
public:
	train(BUILDING_METHOD);
	train(int n,BUILDING_METHOD);
	~train();
	void Test_Run();
protected:
	bool Generate_CRISPR_Population();//need a method to set the population parameter 
	bool Hybird_CRISPR_Generator();//If the population of CRIPSR is a mixture of _static&_dynamic individuals, use this to initialize
	bool Spacer_Adding();
	float Entropy();
	/*2 ways to add */
	bool Information_Gain(CRISPR_Head *CHP);
	bool Random_Grap();
	float Credit_For_Spacer();
	bool Build_CRISPR_Index();
	bool Initialize_CRISPR_Index();
	bool Add_To_Index(int CHead_i,int CIndex_j);
	bool Expand_Population(CRISPR_Index *CIP);
	bool Set_Range_Random();
	bool Get_IG(CRISPR_Head *CHP);
	bool Build_CRISPR(CRISPR_Head *CHP);
	bool Sort(CRISPR_Head *CHP);
	bool CRISPR_Add(CRISPR_Head &CHP,int i,int j);
	bool Sort(Information_Gain_Node &IGN);
	bool Train_Credit(int i,int j);
	bool Reset_Board();
	bool Prune_CRIPSR_Array();
	bool affinity(CRISPR_Segment CH,Standar_Data_Formate data);
	float Revised_Value(int value ,int length,int digit_posb_num);
	CRISPR_Segment* Add_To_Tail(CRISPR_Segment &CHH,CRISPR_Segment *temp);
	int CRISPR_Population_Size;
	CRISPR_Head CHead[MAX_POPULATION_SIZE]; //pointer to the CRIPSR population,it is the beginning of the set of heads
	CRISPR_Index CIndex[MAX_CLASS_NUM];
	float Entropy_S;
	Vote_Node vote_board[MAX_CLASS_NUM];//record each class's affinity to the new pattern
	float match_board[MAX_CLASS_NUM];
	BUILDING_METHOD method;//To define different ways to build up the CRISPR array
};