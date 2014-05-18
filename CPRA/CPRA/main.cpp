#include "CPRA.h"
void main()
{
	ReadData *Rf=new ReadData(5); 
	Rf->Test_Run();
	train *TR=new train(_entropy);
	TR->Test_Run();
}