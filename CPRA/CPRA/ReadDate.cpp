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
		train_num=0;
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
		test_num=0;
	}
	return true;
}
void ReadDate::Test_Run()
{
	cout<<"Test run!"<<endl;
	Monk_Problem_Read();
}