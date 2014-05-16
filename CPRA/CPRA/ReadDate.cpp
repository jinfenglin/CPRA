#include "ReadDate.h"

ReadDate::ReadDate()
{
	ifs_train.open(DEFAULT_TRAINDATE_PATH);
	ifs_test.open(DEFAULT_TESTDATE_PATH);
	if(!(ifs_train||ifs_test))
		cout<<"fail to open train date file with default path!"<<endl;
	else
		cout<<"Initializing...."<<endl;
	train_num=0;
	test_num=0;

}
ReadDate::ReadDate(string train_path,string test_path )
{

}
ReadDate::ReadDate(int n)
{
	ifs_mix.open(DEFAULT_MIXEDDATE_PATH);
	if(!ifs_mix)
		cout<<"fail to open the mixed date file!"<<endl;
	else
		cout<<"Initializing...."<<endl;
	train_num=0;
	test_num=0;
	N_Fold=n;

}
ReadDate::~ReadDate()
{	
	ifs_train.close();
	ifs_test.close();
}
bool ReadDate::Monk_Problem_Read()
{
	//Training date reading
	string str;
	int i=0;
	while(!ifs_train.eof())
	{
		getline(ifs_train,str);
		trim(str,' ');
		if(str.empty())
			break;
		Train_Date_Head[i]._class=str[0];
		Train_Date_Head[i]._content=str.substr(1,6);
		Train_Date_Head[i]._name=str.substr(7);	
		train_num++;
	}
	//Test date reading
	i=0;
	while(!ifs_test.eof())
	{
		getline(ifs_test,str);
		trim(str,' ');
		if(str.empty())
			break;
		Test_Date_Head[i]._class=str[0];
		Test_Date_Head[i]._content=str.substr(1,6);
		Test_Date_Head[i]._name=str.substr(7);
		test_num++;
	}
	int total_num=test_num+train_num;
	return true;
}
bool ReadDate::DNA_Read()
{
	string str_name,str_content;
	int i=0;
	while(!ifs_mix.eof())
	{
		//getline(ifs_mix,str);
		ifs_mix>>str_name>>str_content;
		Temp_Date_Head[i]._class=str_name;
		Temp_Date_Head[i]._content=str_content;
		Temp_Date_Head[i]._name=str_name;
		i++;
	}
	total_num=i;
	return true;
}
bool ReadDate::N_Fold_Seperate()
{
	int Sample_Rate=N_Fold;
	int x=0,y=0;
	for(int i=0;i<total_num;i+=Sample_Rate)
	{
		int Test_Item=RandomInt(Sample_Rate);
		for(int n=0;n<Sample_Rate;n++)
		{
			int temp_locate=i+n;
			if(temp_locate>total_num-1)
				break;

			if(n==Test_Item)//divide into 2 groups
			{
				Test_Date_Head[x]._class=Temp_Date_Head[temp_locate]._class;
				Test_Date_Head[x]._content=Temp_Date_Head[temp_locate]._content;
				Test_Date_Head[x]._name=Temp_Date_Head[temp_locate]._name;
				x++;
			}
			else
			{
				Train_Date_Head[y]._class=Temp_Date_Head[temp_locate]._class;
				Train_Date_Head[y]._content=Temp_Date_Head[temp_locate]._content;
				Train_Date_Head[y]._name=Temp_Date_Head[temp_locate]._name;
				y++;
			}
		}

	}		
	test_num=x;
	train_num=y;
	return true;
}
void ReadDate::Test_Run()
{
	cout<<"Test run!"<<endl;
	//Monk_Problem_Read();
	DNA_Read();
	N_Fold_Seperate();
}