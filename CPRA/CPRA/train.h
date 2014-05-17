#include "ReadDate.h"
#include <malloc.h>
enum BUILDING_METHOD{_entropy,_random,_hybird};
enum SEGMENT_KIND {_dynamic,_static};
struct CRISPR_Segment
{
	int _Start;
	int _Length;
	int _Value;
	string content;
	CRISPR_Segment *next;
	CRISPR_Segment& operator =(CRISPR_Segment &value)//copy the values
	{
		_Length=value._Length;
		_Start=value._Start;
		_Value=value._Value;
		content=value.content;
		next=value.next;
	}
};
struct CRISPR_Head
{
	CRISPR_Segment *head;//pointer to the content of an individual CRISPR
	int length;          //the length of the CRISPR
	int Credit_in_Population;//Describe how reliable this CRISPR is
	SEGMENT_KIND type;       //static CRIPSR have same length ,dynamic one has variable length
	int segment_length;  //if the type is _static then this item is accord with the value in CRISPR_Segment _Length 
                         //else segment_length==0 _Length record the length of each segment
};
class train:public ReadDate
{
public:
	train(BUILDING_METHOD);
	train(int n,BUILDING_METHOD);
	~train();
	void Test_Run();
private:
	bool Generate_CRISPR_Population();//need a method to set the population parameter 
	bool Hybird_CRISPR_Generator();//If the population of CRIPSR is a mixture of _static&_dynamic individuals, use this to initialize
	bool Spacer_Adding();
	float Entropy();
	float Information_Gain();
	bool Random_Grap();
	float Credit_For_Spacer();//

	int CRISPR_Population_Size;
	CRISPR_Head *CHead; //pointer to the CRIPSR population,it is the beginning of the set of heads

	BUILDING_METHOD method;//To define different ways to build up the CRISPR array
};