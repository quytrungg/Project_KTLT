#ifndef TIME_H_
#define TIME_H_

#include "Struct.h"

const std::string currentDateTime();
void Get_current_time_to_int(Time& current_time);
bool checkYear(int year);
bool compare2Times(Date& a, Date& b);

#endif // !TIME_H_


