//This file take charge of reading different kinds of date sets and print the results to log 
#ifndef _READDATE_H
#define _READDATE_H
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <malloc.h>
#include "tools.h"
using namespace std;
//#define MAX_PATTERN_LENGTH 15000
#define MAX_DATE_ITEM 1000
#ifdef _LINUX_
#deifne \\ /
#endif
#define DEFAULT_TRAINDATE_PATH "..\\train_date.txt"
#define DEFAULT_TESTDATE_PATH "..\\test_date.txt "
#define DEFAULT_MIXEDDATE_PATH "..\\mixed_date.txt"
struct Standar_Date_Formate
{
	string _name;  //name of the date
	string _class; //pattern it blongs to 
	string _content;
	//char   _content[MAX_PATTERN_LENGTH]; //content of the pattern
};
class ReadData:public tools
{
public:
	ReadData();//Read with default path
	ReadData(int n);//N_fold reading from single file
	ReadData(string train_path,string test_path);//Read with the path given 
	void Test_Run();
	bool Monk_Problem_Read();
	bool DNA_Read(); //read the DNA file 
	bool N_Fold_Seperate();//seperate the datas read from a single file into testing and training data sets
	int Count_Class_Num();//Count how many class do we have in the data
	~ReadData();
protected:
	ifstream ifs_train,ifs_test,ifs_mix;  
	Standar_Date_Formate Train_Data_Head[MAX_DATE_ITEM];//beginning of training date set
	Standar_Date_Formate Test_Data_Head[MAX_DATE_ITEM];//beginning of testing date set
	Standar_Date_Formate Temp_Data_Head[2*MAX_DATE_ITEM];//begining of the date mixed together
	int train_num,test_num;//record the number of the date items
	int total_num;
	int max_length;//record the longest pattern if pattern vary in length
	int N_Fold;
	int class_num;//record the number of class
	string class_index[20];

};
#endif