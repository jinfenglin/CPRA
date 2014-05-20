#include "ReadData.h"
ReadData::ReadData()
{
	ifs_train.open(DEFAULT_TRAINDATE_PATH);
	ifs_test.open(DEFAULT_TESTDATE_PATH);
	if(!(ifs_train||ifs_test))
		cout<<"fail to open train date file with default path!"<<endl;
	else
		cout<<"Initializing...."<<endl;
	train_num=0;
	test_num=0;
	total_num=0;
	max_length=0;
	class_num=0;

}
ReadData::ReadData(string train_path,string test_path )
{

}
ReadData::ReadData(int n)
{
	ifs_mix.open(DEFAULT_MIXEDDATE_PATH);
	if(!ifs_mix)
		cout<<"fail to open the mixed date file!"<<endl;
	else
		cout<<"Initializing...."<<endl;
	train_num=0;
	test_num=0;
	N_Fold=n;
	total_num=0;
	max_length=0;
	class_num=0;

}
ReadData::~ReadData()
{	
	ifs_train.close();
	ifs_test.close();
}
bool ReadData::Monk_Problem_Read()
{
	//Training date reading
	D_num=4;
	string str;
	int i=0;
	while(!ifs_train.eof())
	{
		getline(ifs_train,str);
		trim(str,' ');
		if(str.empty())
			break;
		Train_Data_Head[i]._class=str[0];
		Train_Data_Head[i]._content=str.substr(1,6);
		Train_Data_Head[i]._name=str.substr(7);	
		i++;
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
		Test_Data_Head[i]._class=str[0];
		Test_Data_Head[i]._content=str.substr(1,6);
		Test_Data_Head[i]._name=str.substr(7);
		i++;
		test_num++;
	}
	max_length=Test_Data_Head[0]._content.length();
	total_num=test_num+train_num;
	return true;
}
bool ReadData::DNA_Read()
{
	D_num=4;
	string str_name,str_content;
	if(N_Fold==0)
	{
		cout<<"error in initialization,parameter N is required!";
			return false;
	}
	int i=0;
	while(!ifs_mix.eof())
	{
		//getline(ifs_mix,str);
		ifs_mix>>str_name>>str_content;
		Temp_Data_Head[i]._class=str_name;
		Temp_Data_Head[i]._content=str_content;
		Temp_Data_Head[i]._name=str_name;
		i++;
		if(Temp_Data_Head[i]._content.length()>max_length)
			max_length=Temp_Data_Head[i]._content.length();
	}
	total_num=i;
	return true;
}
bool ReadData::N_Fold_Seperate()
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
				Test_Data_Head[x]._class=Temp_Data_Head[temp_locate]._class;
				Test_Data_Head[x]._content=Temp_Data_Head[temp_locate]._content;
				Test_Data_Head[x]._name=Temp_Data_Head[temp_locate]._name;
				x++;
			}
			else
			{
				Train_Data_Head[y]._class=Temp_Data_Head[temp_locate]._class;
				Train_Data_Head[y]._content=Temp_Data_Head[temp_locate]._content;
				Train_Data_Head[y]._name=Temp_Data_Head[temp_locate]._name;
				y++;
			}
		}

	}		
	test_num=x;
	train_num=y;
	return true;
}
void ReadData::Test_Run()
{
	cout<<"Test run!"<<endl;
	//Monk_Problem_Read();
	DNA_Read();
	N_Fold_Seperate();
	Count_Class_Num();
}
int  ReadData::Count_Class_Num()//by the way calculate the protion of each kind of data
{
	int count_number=1;
	class_index[0]=Train_Data_Head[0]._class;
	class_portion_raw[0]=1;
	for(int i=1;i<train_num;i++)
	{
		int j=0;
		for(;j<count_number;j++)
		{
			if(Train_Data_Head[i]._class==class_index[j])
			{
				class_portion_raw[j]++;//count the number of this kind of class			
				break;
			}
		}
		if(j==count_number)//regist new class
		{
			class_portion_raw[j]=1; 
			class_index[count_number]=Train_Data_Head[i]._class;
			count_number++;	
		}
	}
	for(int i=0;i<test_num;i++)
	{
				int j=0;
		for(;j<count_number;j++)
		{
			if(Test_Data_Head[i]._class==class_index[j])
				break;
		}
		if(j==count_number)
		{
			class_index[count_number]=Test_Data_Head[i]._class;
			count_number++;	
		}
	}
	
	class_num=count_number;
	return count_number;

}