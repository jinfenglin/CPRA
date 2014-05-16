//This file take charge of reading different kinds of date sets and print the results to log 
#ifndef _READDATE_H
#define _READDATE_H
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <malloc.h>
using namespace std;
#define MAX_PATTERN_LENGTH 300
#define MAX_DATE_ITEM 500
#ifdef _LINUX_
#deifne \\ /
#endif
#define DEFAULT_TRAINDATE_PATH "..\\train_date.txt"
#define DEFAULT_TESTDATE_PATH "..\\test_date.txt "
struct Standar_Date_Formate
{
	string _name;  //name of the date
	string _class; //pattern it blongs to 
	string _content;
	//char   _content[MAX_PATTERN_LENGTH]; //content of the pattern
};
class ReadDate
{
public:
	ReadDate();//Read with default path
	ReadDate(string train_path,string test_path);//Read with the path given 
	void Test_Run();
	bool Monk_Problem_Read();
	~ReadDate();
private:
	ifstream ifs_train,ifs_test;  
	Standar_Date_Formate Train_Date_Head[MAX_DATE_ITEM];//beginning of training date set
	Standar_Date_Formate Test_Date_Head[MAX_DATE_ITEM];//beginning of testing date set
	int train_num,test_num;//record the number of the date items
};
#endif