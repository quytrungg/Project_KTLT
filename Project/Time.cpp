#include "Struct.h"
#include "Time.h"
#include "Help.h"

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	//tstruct = *localtime(&now);
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}

void Get_current_time_to_int(Time& current_time) {
	std::string str = currentDateTime();
	int begin = 0;
	int end = str.find("-", begin + 1);
	char* a = new char[end - begin + 1];
	str.copy(a, end - begin, begin);
	current_time.date.Year = Convert_char_to_int(a, end - begin);
	delete[] a;

	begin = end + 1;
	end = str.find("-", begin + 1);
	a = new char[end - begin + 1];
	str.copy(a, end - begin, begin);
	current_time.date.Month = Convert_char_to_int(a, end - begin);
	delete[] a;

	begin = end + 1;
	end = str.find(".", begin + 1);
	a = new char[end - begin + 1];
	str.copy(a, end - begin, begin);
	current_time.date.Day = Convert_char_to_int(a, end - begin);
	delete[] a;

	begin = end + 1;
	end = str.find(":", begin + 1);
	a = new char[end - begin + 1];
	str.copy(a, end - begin, begin);
	current_time.hours = Convert_char_to_int(a, end - begin);
	delete[] a;

	begin = end + 1;
	end = str.find(":", begin + 1);
	a = new char[end - begin + 1];
	str.copy(a, end - begin, begin);
	current_time.minutes = Convert_char_to_int(a, end - begin);
	delete[] a;

	begin = end + 1;
	end = str.length();
	a = new char[end - begin + 1];
	str.copy(a, end - begin, begin);
	current_time.seconds = Convert_char_to_int(a, end - begin);
	delete[] a;
}

bool checkYear(int year)
{
	if (year % 400 == 0)
		return true;

	if (year % 4 == 0 && year % 100 != 0)
		return true;

	return false;
}

bool compare2Times(Date& a, Date& b) {//true khi b>a
	if (a.Year > b.Year)
	{
		return false;
	}
	if (a.Year == b.Year)
	{
		if (a.Month > b.Month)
		{
			return false;
		}
		if (a.Month == b.Month)
		{
			if (a.Day >= b.Day) return false;
		}
	}
	return true;
}