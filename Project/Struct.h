#ifndef STRUCT_H_
#define STRUCT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt> //possible C++11?
#include <fstream>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <Windows.h>
#include <mmsystem.h>
#include <conio.h>

static char* default_year_1;
static wchar_t* default_year_2;
static char* default_semester_1;
static wchar_t* default_semester_2;

struct Account {
	wchar_t* ID;
	wchar_t* Pass;
};

struct Date {
	int Day;
	int Month;
	int Year;
};

struct Time {
	Date date;
	int seconds;
	int minutes;
	int hours;
};

struct Score {
	wchar_t* ID;
	double TotalMark;
	double FinalMark;
	double MidtermMark;
	double OtherMark;
	double GPA;
};

struct Student {
	int ID;
	wchar_t* FirstName;
	wchar_t* LastName;
	wchar_t* Gender;
	Date Birthday;
	int SocialID;
	Account account;
	Score course_1;
	Score course_2;
	Score course_3;
	Score course_4;
	Score course_5;
	int Schedule[4][6];
};

struct Staff {
	int ID;
	wchar_t* FirstName;
	wchar_t* LastName;
	wchar_t* Gender;
	Date Birthday;
	int SocialID;
	Account account;
};

struct Class {
	wchar_t* Name;
	wchar_t* StudentID;
};

struct Timetable {
	int day_of_week;
	int session;
};

struct Course {
	wchar_t* ID;
	wchar_t* Name;
	wchar_t* Teacher_Name;
	int Credit;
	int max_stu = 50;
	int count = 0;
	Timetable ses_1;
	Timetable ses_2;
	wchar_t* StudentID;
};

struct Node_stu {
	Student stu;
	Node_stu* pNext;
};

struct Node_staff {
	Staff staff;
	Node_staff* pNext;
};

struct Node_cla {
	Class cla;
	Node_cla* pNext;
};

struct Node_cou {
	Course cou;
	Node_cou* pNext;
};

struct Node_help_1 {
	wchar_t* data;
	Node_help_1* pNext;
};

struct Node_time_semester {
	Date start;
	Date end;
	Node_time_semester* pNext;
};

#endif // !STRUCT_H_


