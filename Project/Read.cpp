#include "Struct.h"
#include "Staff.h"
#include "Help.h"
#include "Read.h"

void Read_file_staff(std::wstring str, Node_staff* pCur) {
	// ID
	int begin = 0;
	int end = str.find(',', begin + 1);
	wchar_t* a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->staff.ID = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Account name
	pCur->staff.account.ID = new wchar_t[end - begin + 1];
	str.copy(pCur->staff.account.ID, end - begin, begin);
	pCur->staff.account.ID[end - begin] = L'\0';

	// First Name
	begin = end + 1;
	end = str.find(',', begin + 1);
	pCur->staff.FirstName = new wchar_t[end - begin + 1];
	str.copy(pCur->staff.FirstName, end - begin, begin);
	pCur->staff.FirstName[end - begin] = L'\0';

	// Last Name
	begin = end + 1;
	end = str.find(',', begin + 1);
	pCur->staff.LastName = new wchar_t[end - begin + 1];
	str.copy(pCur->staff.LastName, end - begin, begin);
	pCur->staff.LastName[end - begin] = L'\0';

	// Gender
	begin = end + 1;
	end = str.find(',', begin + 1);
	pCur->staff.Gender = new wchar_t[end - begin + 1];
	str.copy(pCur->staff.Gender, end - begin, begin);
	pCur->staff.Gender[end - begin] = L'\0';

	// Birthday day
	begin = end + 1;
	end = str.find('/', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->staff.Birthday.Day = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Birthday month
	begin = end + 1;
	end = str.find('/', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->staff.Birthday.Month = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Birthday year
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->staff.Birthday.Year = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Social ID
	begin = end + 1;
	end = str.length();
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->staff.SocialID = Convert_wchart_to_int(a, end - begin);
	delete[] a;
}

void Read_file_stu(std::wstring str, Node_stu* pCur) {
	// ID
	int begin = 0;
	int end = str.find(',', begin + 1);
	wchar_t* a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.ID = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Account name
	pCur->stu.account.ID = new wchar_t[end - begin + 1];
	str.copy(pCur->stu.account.ID, end - begin, begin);
	pCur->stu.account.ID[end - begin] = L'\0';

	// First Name
	begin = end + 1;
	end = str.find(',', begin + 1);
	pCur->stu.FirstName = new wchar_t[end - begin + 1];
	str.copy(pCur->stu.FirstName, end - begin, begin);
	pCur->stu.FirstName[end - begin] = L'\0';

	// Last Name
	begin = end + 1;
	end = str.find(',', begin + 1);
	pCur->stu.LastName = new wchar_t[end - begin + 1];
	str.copy(pCur->stu.LastName, end - begin, begin);
	pCur->stu.LastName[end - begin] = L'\0';

	// Gender
	begin = end + 1;
	end = str.find(',', begin + 1);
	pCur->stu.Gender = new wchar_t[end - begin + 1];
	str.copy(pCur->stu.Gender, end - begin, begin);
	pCur->stu.Gender[end - begin] = L'\0';

	// Birthday day
	begin = end + 1;
	end = str.find('/', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.Birthday.Day = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Birthday month
	begin = end + 1;
	end = str.find('/', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.Birthday.Month = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Birthday year
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.Birthday.Year = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Social ID
	begin = end + 1;
	end = str.length();
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.SocialID = Convert_wchart_to_int(a, end - begin);
	delete[] a;
}

void Read_course_1(std::wstring str, Node_stu* pCur) {
	// ID
	int begin = 0;
	int end = str.find(',', begin + 1);
	pCur->stu.course_1.ID = new wchar_t[end - begin + 1];
	str.copy(pCur->stu.course_1.ID, end - begin, begin);
	pCur->stu.course_1.ID[end - begin] = L'\0';

	wchar_t* a;
	// Total Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_1.TotalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Fianal Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_1.FinalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Midterm Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_1.MidtermMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Other mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_1.OtherMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// GPA
	begin = end + 1;
	end = str.length();
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_1.GPA = Conver_wchart_to_double(a, end - begin);
	delete[] a;
}

void Read_course_2(std::wstring str, Node_stu* pCur) {
	// ID
	int begin = 0;
	int end = str.find(',', begin + 1);
	pCur->stu.course_2.ID = new wchar_t[end - begin + 1];
	str.copy(pCur->stu.course_2.ID, end - begin, begin);
	pCur->stu.course_2.ID[end - begin] = L'\0';

	wchar_t* a;
	// Total Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_2.TotalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Fianal Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_2.FinalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Midterm Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_2.MidtermMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Other mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_2.OtherMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// GPA
	begin = end + 1;
	end = str.length();
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_2.GPA = Conver_wchart_to_double(a, end - begin);
	delete[] a;
}

void Read_course_3(std::wstring str, Node_stu* pCur) {
	// ID
	int begin = 0;
	int end = str.find(',', begin + 1);
	pCur->stu.course_3.ID = new wchar_t[end - begin + 1];
	str.copy(pCur->stu.course_3.ID, end - begin, begin);
	pCur->stu.course_3.ID[end - begin] = L'\0';

	wchar_t* a;
	// Total Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_3.TotalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Fianal Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_3.FinalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Midterm Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_3.MidtermMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Other mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_3.OtherMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// GPA
	begin = end + 1;
	end = str.length();
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_3.GPA = Conver_wchart_to_double(a, end - begin);
	delete[] a;
}

void Read_course_4(std::wstring str, Node_stu* pCur) {
	// ID
	int begin = 0;
	int end = str.find(',', begin + 1);
	pCur->stu.course_4.ID = new wchar_t[end - begin + 1];
	str.copy(pCur->stu.course_4.ID, end - begin, begin);
	pCur->stu.course_4.ID[end - begin] = L'\0';

	wchar_t* a;
	// Total Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_4.TotalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Fianal Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_4.FinalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Midterm Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_4.MidtermMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Other mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_4.OtherMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// GPA
	begin = end + 1;
	end = str.length();
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_4.GPA = Conver_wchart_to_double(a, end - begin);
	delete[] a;
}

void Read_course_5(std::wstring str, Node_stu* pCur) {
	// ID
	int begin = 0;
	int end = str.find(',', begin + 1);
	pCur->stu.course_5.ID = new wchar_t[end - begin + 1];
	str.copy(pCur->stu.course_5.ID, end - begin, begin);
	pCur->stu.course_5.ID[end - begin] = L'\0';

	wchar_t* a;
	// Total Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_5.TotalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Fianal Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_5.FinalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Midterm Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_5.MidtermMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Other mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_5.OtherMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// GPA
	begin = end + 1;
	end = str.length();
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.course_5.GPA = Conver_wchart_to_double(a, end - begin);
	delete[] a;
}

void Read_file_cou(std::wstring str, Node_cou* pCur) {
	wchar_t* a;
	// ID
	int begin = 0;
	int end = str.find(',', begin + 1);
	pCur->cou.ID = new wchar_t[end - begin + 1];
	str.copy(pCur->cou.ID, end - begin, begin);
	pCur->cou.ID[end - begin] = L'\0';

	// Coure Name
	begin = end + 1;
	end = str.find(',', begin + 1);
	pCur->cou.Name = new wchar_t[end - begin + 1];
	str.copy(pCur->cou.Name, end - begin, begin);
	pCur->cou.Name[end - begin] = L'\0';

	// Teacher Name
	begin = end + 1;
	end = str.find(',', begin + 1);
	pCur->cou.Teacher_Name = new wchar_t[end - begin + 1];
	str.copy(pCur->cou.Teacher_Name, end - begin, begin);
	pCur->cou.Teacher_Name[end - begin] = L'\0';

	// Credit
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->cou.Credit = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Max student = 50
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->cou.max_stu = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Count student
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->cou.count = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Session 1
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->cou.ses_1.day_of_week = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->cou.ses_1.session = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Session 2
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->cou.ses_2.day_of_week = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	begin = end + 1;
	end = str.length();
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->cou.ses_2.session = Convert_wchart_to_int(a, end - begin);
	delete[] a;
}