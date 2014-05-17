#include "train.h"

train::train():ReadDate()//train/test seperated version intialization
{

}
train::train(int n):ReadDate(n)//N_flod version intialization
{
}
void train::Test_Run()
{
	this->Monk_Problem_Read();
	cout<<this->test_num<<endl;
}