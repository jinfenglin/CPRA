#include <stdio.h>
#include "ReadDate.h"
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define MAX_PATTERN_LENGTH 300
#define MAX_DATE_ITEM 500
#ifdef _LINUX_
#deifne \\ /
#endif
#define DEFAULT_TRAINDATE_PATH "..\\train_date.txt"
#define DEFAULT_TESTDATE_PATH "..\\test_date.txt "