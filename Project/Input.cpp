#include "Struct.h"
#include "Staff.h"
#include "Help.h"
#include "Read.h"
#include "Input.h"
#include "Time.h"
#include "Save.h"

void Input_one_student_by_file(std::wstring str, Node_stu* pCur) {
	// ID
	int begin = str.find(',', 0) + 1;
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

	// Account password
	pCur->stu.account.Pass = new wchar_t[9];
	int count = 0;

	// Birthday day
	begin = end + 1;
	end = str.find('/', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	for (int i = 0; i < end - begin; i++) {
		pCur->stu.account.Pass[count] = a[i];
		count++;
	}
	if (count == 1) {
		pCur->stu.account.Pass[count] = pCur->stu.account.Pass[count - 1];
		pCur->stu.account.Pass[0] = L'0';
		count++;
	}
	pCur->stu.Birthday.Day = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Birthday month
	begin = end + 1;
	end = str.find('/', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	for (int i = 0; i < end - begin; i++) {
		pCur->stu.account.Pass[count] = a[i];
		count++;
	}
	if (count == 3) {
		pCur->stu.account.Pass[count] = pCur->stu.account.Pass[count - 1];
		pCur->stu.account.Pass[count - 1] = L'0';
		count++;
	}
	pCur->stu.Birthday.Month = Convert_wchart_to_int(a, end - begin);
	delete[] a;

	// Birthday year
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	for (int i = 0; i < end - begin; i++) {
		pCur->stu.account.Pass[count] = a[i];
		count++;
	}
	pCur->stu.account.Pass[count] = L'\0';
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

	// Course 1
	pCur->stu.course_1.ID = new wchar_t[2];
	pCur->stu.course_1.ID[0] = L'0';
	pCur->stu.course_1.ID[1] = L'\0';
	pCur->stu.course_1.FinalMark = 0;
	pCur->stu.course_1.MidtermMark = 0;
	pCur->stu.course_1.OtherMark = 0;
	pCur->stu.course_1.TotalMark = 0;
	pCur->stu.course_1.GPA = 0;

	// Course 2
	pCur->stu.course_2.ID = new wchar_t[2];
	pCur->stu.course_2.ID[0] = L'0';
	pCur->stu.course_2.ID[1] = L'\0';
	pCur->stu.course_2.FinalMark = 0;
	pCur->stu.course_2.MidtermMark = 0;
	pCur->stu.course_2.OtherMark = 0;
	pCur->stu.course_2.TotalMark = 0;
	pCur->stu.course_2.GPA = 0;

	// Course 3
	pCur->stu.course_3.ID = new wchar_t[2];
	pCur->stu.course_3.ID[0] = L'0';
	pCur->stu.course_3.ID[1] = L'\0';
	pCur->stu.course_3.FinalMark = 0;
	pCur->stu.course_3.MidtermMark = 0;
	pCur->stu.course_3.OtherMark = 0;
	pCur->stu.course_3.TotalMark = 0;
	pCur->stu.course_3.GPA = 0;

	// Course 4
	pCur->stu.course_4.ID = new wchar_t[2];
	pCur->stu.course_4.ID[0] = L'0';
	pCur->stu.course_4.ID[1] = L'\0';
	pCur->stu.course_4.FinalMark = 0;
	pCur->stu.course_4.MidtermMark = 0;
	pCur->stu.course_4.OtherMark = 0;
	pCur->stu.course_4.TotalMark = 0;
	pCur->stu.course_4.GPA = 0;

	// Course 5
	pCur->stu.course_5.ID = new wchar_t[2];
	pCur->stu.course_5.ID[0] = L'0';
	pCur->stu.course_5.ID[1] = L'\0';
	pCur->stu.course_5.FinalMark = 0;
	pCur->stu.course_5.MidtermMark = 0;
	pCur->stu.course_5.OtherMark = 0;
	pCur->stu.course_5.TotalMark = 0;
	pCur->stu.course_5.GPA = 0;

	// Schedule
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			pCur->stu.Schedule[i][j] = 0;
		}
	}
}

void Input_student(std::wstring str, Node_stu*& pHead) {
	pHead = new Node_stu;
	Node_stu* pCur = pHead;
	std::wifstream fin(str);
	std::wstring a;
	if (!fin) {
		std::wcout << L"Không thể đọc file \n";
	}
	else {
		fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin.eof()) {
			std::getline(fin, a);
			pCur->pNext = new Node_stu;
			fin.ignore();
			Input_one_student_by_file(a, pCur->pNext);
			pCur = pCur->pNext;
			pCur->pNext = nullptr;
		}
		if (pHead->pNext == nullptr) {
			delete pHead;
			pHead = nullptr;
		}
		else {
			Node_stu* pTemp = pHead;
			pHead = pHead->pNext;
			delete pTemp;
		}
	}
	fin.close();
}

void Input_one_class(std::wstring str, Node_cla* pCur_cla, Node_stu* pHead_stu) {
	// Class name
	int  k = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == L'\\')	k++;
	}
	int begin = 0;
	int end = -1;
	for (int i = 0; i < k; i++) {
		begin = end + 1;
		end = str.find('\\', begin + 1);
	}
	begin = end + 1;
	end = str.find('.', begin + 1);
	pCur_cla->cla.Name = new wchar_t[end - begin + 1];
	str.copy(pCur_cla->cla.Name, end - begin, begin);
	pCur_cla->cla.Name[end - begin] = L'\0';

	// Student ID
	Node_stu* pCur_stu = pHead_stu;
	int count = 0;
	while (pCur_stu != nullptr) {
		count++;
		pCur_stu = pCur_stu->pNext;
	}
	pCur_cla->cla.StudentID = new wchar_t[count * 9 + 1];
	pCur_stu = pHead_stu;
	k = 0;
	for (int i = 0; i < count; i++) {
		int n = pCur_stu->stu.ID;
		int m = 10000000;
		for (int i = 0; i < 8; i++) {
			int r = n / m;
			n = n - r * m;
			m = m / 10;
			pCur_cla->cla.StudentID[k] = wchar_t(r + '0');
			k++;
		}
		pCur_cla->cla.StudentID[k] = L',';
		k++;
		pCur_stu = pCur_stu->pNext;
	}
	pCur_cla->cla.StudentID[count * 9] = L'\0';
}

void Input_student_data(Node_stu*& pHead_stu, Node_cla*& pHead_cla, wchar_t* file_login) {
	system("cls");
	std::wstring str_1;
	std::wifstream fin(L"Default_time.txt");
	fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin, str_1);
	fin.close();
	char* current_year = new char[str_1.length() + 1];
	for (int i = 0; i < str_1.length(); i++) {
		current_year[i] = str_1[i];
	}
	current_year[str_1.length()] = L'\0';
	int x;
	pHead_cla = new Node_cla;
	Node_cla* pCur_cla = pHead_cla;
	std::wstring str;
	std::wcout << "Please input the total number of classes in the school year: ";
	std::wcin >> x;
	std::wcin.ignore();
	for (int i = 0; i < x; i++) {
		pCur_cla->pNext = new Node_cla;
		std::wcout << "Please input the link: ";
		std::getline(std::wcin, str);
		Input_student(str, pHead_stu);
		Input_one_class(str, pCur_cla->pNext, pHead_stu);
		Save_stu_to_test(pHead_stu, Create_second_folder("Student", current_year));
		Delete_Node_stu(pHead_stu);
		pCur_cla = pCur_cla->pNext;
		pCur_cla->pNext = nullptr;
	}
	if (pHead_cla->pNext == nullptr) {
		delete pHead_cla;
		pHead_cla = nullptr;
	}
	else {
		Node_cla* pTemp = pHead_cla;
		pHead_cla = pHead_cla->pNext;
		delete pTemp;
	}
	Save_name_class(pHead_cla, current_year);
	Save_cla_to_test(pHead_cla, Create_second_folder("Class", current_year));
	Delete_Node_cla(pHead_cla);
	system("cls");
	std::wcout << "Input success" << std::endl;
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_staff(file_login);
	}
}

void Input_one_course_direct(Node_cou* pCur) {
	system("cls");

	// ID
	std::wstring str;
	std::wcin.ignore();
	std::wcout << "Please input the course id: ";
	std::getline(std::wcin, str);
	pCur->cou.ID = new wchar_t[str.length() + 1];
	str.copy(pCur->cou.ID, str.length(), 0);
	pCur->cou.ID[str.length()] = L'\0';

	// Course Name
	std::wcout << "Please input the course name: ";
	std::getline(std::wcin, str);
	pCur->cou.Name = new wchar_t[str.length() + 1];
	str.copy(pCur->cou.Name, str.length(), 0);
	pCur->cou.Name[str.length()] = L'\0';

	// Teacher Name
	std::wcout << "Please input the teacher name: ";
	std::getline(std::wcin, str);
	pCur->cou.Teacher_Name = new wchar_t[str.length() + 1];
	str.copy(pCur->cou.Teacher_Name, str.length(), 0);
	pCur->cou.Teacher_Name[str.length()] = L'\0';

	// Credit
	std::wcout << "Please input how many credits in this course: ";
	std::wcin >> pCur->cou.Credit;

	// Timetable
	std::wcout << "Please input the timetable: " << std::endl;
	std::wcout << "Session 1:";

	ShowCur(0);
	std::wstring menu_1[] = { L"MON",L"TUE",L"WED",L"THU",L"FRI", L"SAT"};
	int pointer = 0;
	int color = 0;
	int Max_List_Menu = 6;
	while (1) {
		//in menu ra man hinh
		GotoXY(11, 5);
		std::wcout << menu_1[pointer] << std::endl;
		char key;
		while (1) {
			if (_kbhit()) {
				key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer > 0) {
						pointer--;
					}
					else {
						pointer = Max_List_Menu - 1;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer < Max_List_Menu - 1) {
						pointer++;
					}
					else {
						pointer = 0;
					}
					break;
				}
				if (key == 13) {
					switch (pointer) {
					case 0:
						pCur->cou.ses_1.day_of_week = 0;
						break;
					case 1:
						pCur->cou.ses_1.day_of_week = 1;
						break;
					case 2:
						pCur->cou.ses_1.day_of_week = 2;
						break;
					case 3:
						pCur->cou.ses_1.day_of_week = 3;
						break;
					case 4:
						pCur->cou.ses_1.day_of_week = 4;
						break;
					case 5:
						pCur->cou.ses_1.day_of_week = 5;
						break;
					default:
						std::wcout << "Erorr" << std::endl;
					}
					break;
				}
			}
		}
		if (key == 13) {
			break;
		}
	}
	GotoXY(17, 5);
	std::wcout << "Time:";
	std::wstring menu_2[] = { L"S1 (07:30)",L"S2 (09:30)",L"S3 (13:30)",L"S4 (15:30)" };
	pointer = 0;
	Max_List_Menu = 4;
	while (1) {
		//in menu ra man hinh
		GotoXY(23, 5);
		std::wcout << menu_2[pointer] << std::endl;
		char key;
		while (1) {
			if (_kbhit()) {
				key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer > 0) {
						pointer--;
					}
					else {
						pointer = Max_List_Menu - 1;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer < Max_List_Menu - 1) {
						pointer++;
					}
					else {
						pointer = 0;
					}
					break;
				}
				if (key == 13) {
					switch (pointer) {
					case 0:
						pCur->cou.ses_1.session = 0;
						break;
					case 1:
						pCur->cou.ses_1.session = 1;
						break;
					case 2:
						pCur->cou.ses_1.session = 2;
						break;
					case 3:
						pCur->cou.ses_1.session = 3;
						break;
					default:
						std::wcout << "Erorr" << std::endl;
					}
					break;
				}
			}
		}
		if (key == 13) {
			break;
		}
	}

	GotoXY(0, 6);
	std::wcout << "Session 1:";

	std::wstring menu_3[] = { L"MON",L"TUE",L"WED",L"THU",L"FRI", L"SAT" };
	pointer = 0;
	Max_List_Menu = 6;
	while (1) {
		//in menu ra man hinh
		GotoXY(11, 6);
		std::wcout << menu_3[pointer] << std::endl;
		char key;
		while (1) {
			if (_kbhit()) {
				key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer > 0) {
						pointer--;
					}
					else {
						pointer = Max_List_Menu - 1;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer < Max_List_Menu - 1) {
						pointer++;
					}
					else {
						pointer = 0;
					}
					break;
				}
				if (key == 13) {
					switch (pointer) {
					case 0:
						pCur->cou.ses_2.day_of_week = 0;
						break;
					case 1:
						pCur->cou.ses_2.day_of_week = 1;
						break;
					case 2:
						pCur->cou.ses_2.day_of_week = 2;
						break;
					case 3:
						pCur->cou.ses_2.day_of_week = 3;
						break;
					case 4:
						pCur->cou.ses_2.day_of_week = 4;
						break;
					case 5:
						pCur->cou.ses_2.day_of_week = 5;
						break;
					default:
						std::wcout << "Erorr" << std::endl;
					}
					break;
				}
			}
		}
		if (key == 13) {
			break;
		}
	}
	GotoXY(17, 6);
	std::wcout << "Time:";
	std::wstring menu_4[] = { L"S1 (07:30)",L"S2 (09:30)",L"S3 (13:30)",L"S4 (15:30)" };
	pointer = 0;
	Max_List_Menu = 4;
	while (1) {
		//in menu ra man hinh
		GotoXY(23, 6);
		std::wcout << menu_4[pointer] << std::endl;
		char key;
		while (1) {
			if (_kbhit()) {
				key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer > 0) {
						pointer--;
					}
					else {
						pointer = Max_List_Menu - 1;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer < Max_List_Menu - 1) {
						pointer++;
					}
					else {
						pointer = 0;
					}
					break;
				}
				if (key == 13) {
					switch (pointer) {
					case 0:
						pCur->cou.ses_2.session = 0;
						break;
					case 1:
						pCur->cou.ses_2.session = 1;
						break;
					case 2:
						pCur->cou.ses_2.session = 2;
						break;
					case 3:
						pCur->cou.ses_2.session = 3;
						break;
					default:
						std::wcout << "Erorr" << std::endl;
					}
					break;
				}
			}
		}
		if (key == 13) {
			break;
		}
	}
	pCur->cou.StudentID = new wchar_t[2];
	pCur->cou.StudentID[0] = L'0';
	pCur->cou.StudentID[1] = L'\0';
}

void Input_one_course_by_file(std::wstring str, Node_cou* pCur) {
	wchar_t* a;

	// ID
	int begin = 0;
	int end = str.find(',', begin + 1);
	pCur->cou.ID = new wchar_t[end - begin + 1];
	str.copy(pCur->cou.ID, end - begin, begin);
	pCur->cou.ID[end - begin] = L'\0';

	// Course Name
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

	// Count student in class
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

	pCur->cou.StudentID = new wchar_t[2];
	pCur->cou.StudentID[0] = L'0';
	pCur->cou.StudentID[1] = L'\0';
}

void Input_course_direct(Node_cou*& pHead_cou, wchar_t* file_login) {
	std::wstring str_1;
	std::wstring str_2;
	std::wifstream fin(L"Default_time.txt");
	fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin, str_1);
	std::getline(fin, str_2);
	fin.close();
	char* current_year = new char[str_1.length() + 1];
	for (int i = 0; i < str_1.length(); i++) {
		current_year[i] = str_1[i];
	}
	current_year[str_1.length()] = L'\0';
	char* current_semester = new char[str_2.length() + 1];
	for (int i = 0; i < str_2.length(); i++) {
		current_semester[i] = str_2[i];
	}
	current_semester[str_2.length()] = L'\0';
	system("cls");
	int x;
	pHead_cou = new Node_cou;
	Node_cou* pCur_cou = pHead_cou;
	std::wcout << "Please input the total number of course do you want to input: ";
	std::wcin >> x;
	for (int i = 0; i < x; i++) {
		pCur_cou->pNext = new Node_cou;
		Input_one_course_direct(pCur_cou->pNext);
		pCur_cou = pCur_cou->pNext;
		pCur_cou->pNext = nullptr;
	}
	if (pHead_cou->pNext == nullptr) {
		delete pHead_cou;
		pHead_cou = nullptr;
	}
	else {
		Node_cou* pTemp = pHead_cou;
		pHead_cou = pHead_cou->pNext;
		delete pTemp;
	}
	Save_cou_to_test(pHead_cou, current_semester);
	Save_name_course(pHead_cou,current_semester);

	system("cls");
	Delete_Node_cou(pHead_cou);
	std::wcout << "Input success" << std::endl;
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_cou_staff(file_login);
	}
}

void Input_course_by_file(Node_cou*& pHead_cou,wchar_t* file_login) {
	std::wstring str_1;
	std::wstring str_2;
	std::wifstream fin(L"Default_time.txt");
	fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin, str_1);
	std::getline(fin, str_2);
	fin.close();
	char* current_year = new char[str_1.length() + 1];
	for (int i = 0; i < str_1.length(); i++) {
		current_year[i] = str_1[i];
	}
	current_year[str_1.length()] = L'\0';
	char* current_semester = new char[str_2.length() + 1];
	for (int i = 0; i < str_2.length(); i++) {
		current_semester[i] = str_2[i];
	}
	current_semester[str_2.length()] = L'\0';
	system("cls");
	pHead_cou = new Node_cou;
	Node_cou* pCur_cou = pHead_cou;
	std::wstring str;
	std::wstring a;
	std::wcout << "Please input the link: ";
	std::getline(std::wcin, str);
	std::wifstream fin_1(str);
	if (!fin_1) {
		std::wcout << L"Không thể đọc file \n";
	}
	else {
		fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin_1.eof()) {
			std::getline(fin_1, a);
			pCur_cou->pNext = new Node_cou;
			Input_one_course_by_file(a, pCur_cou->pNext);
			pCur_cou = pCur_cou->pNext;
			pCur_cou->pNext = nullptr;
		}
		if (pHead_cou->pNext == nullptr) {
			delete pHead_cou;
			pHead_cou = nullptr;
		}
		else {
			Node_cou* pTemp = pHead_cou;
			pHead_cou = pHead_cou->pNext;
			delete pTemp;
		}
	}
	fin_1.close();
	Save_cou_to_test(pHead_cou, current_semester);
	Save_name_course(pHead_cou, current_semester);

	system("cls");
	Delete_Node_cou(pHead_cou);
	std::wcout << "Input success" << std::endl;
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_cou_staff(file_login);
	}
}

void Input_course_data(Node_cou*& pHead_cou, wchar_t* file_login) {
	int Max_List_Menu = 3;
	int flag = 0;
	SetColor(15, 0);
	std::wstring menu[] = { L"Input course by file",L"Input course by direct",L"Exit" };
	int pointer = 0;
	while (1) {
		//xoa man hinh
		ShowCur(0);
		system("cls");
		//in menu ra man hinh
		for (int i = 0; i < Max_List_Menu; i++)
		{
			if (pointer == i) {
				SetColor(15, 4);
				GotoXY(50, 20 + i);
				std::wcout << "    " << menu[i] << std::endl;
			}
			else {
				SetColor(15, 3);
				GotoXY(50, 20 + i);
				std::wcout << "    " << menu[i] << std::endl;
			}

		}
		while (1) {
			if (_kbhit()) {
				char key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer > 0) {
						pointer--;
					}
					else {
						pointer = Max_List_Menu - 1;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer < Max_List_Menu - 1) {
						pointer++;
					}
					else {
						pointer = 0;
					}
					break;
				}
				if (key == 13) {
					switch (pointer) {
					case 0:
						Input_course_by_file(pHead_cou,file_login);
						Sleep(100000);
						break;
					case 1:
						Input_course_direct(pHead_cou,file_login);
						Sleep(100000);
						break;
					case 2:
						Sub_menu_cou_staff(file_login);
						break;
					}
					break;
				}
				if (key == 27) {
					Sub_menu_cou_staff(file_login);
				}
			}
		}
		if (flag == -1) {

			break;
		}
		Sleep(100);
	}
}

void Input_one_score_student(std::wstring str, Node_stu* pCur, wchar_t* Course_ID) {
	std::wstring str_1;
	std::wstring str_2;
	std::wifstream fin(L"Default_time.txt");
	fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin, str_1);
	std::getline(fin, str_2);
	fin.close();
	char* current_year = new char[str_1.length() + 1];
	for (int i = 0; i < str_1.length(); i++) {
		current_year[i] = str_1[i];
	}
	current_year[str_1.length()] = L'\0';
	char* current_semester = new char[str_2.length() + 1];
	for (int i = 0; i < str_2.length(); i++) {
		current_semester[i] = str_2[i];
	}
	current_semester[str_2.length()] = L'\0';

	Score b;

	// ID
	int begin = str.find(',', 0) + 1;
	int end = str.find(',', begin + 1);
	wchar_t* a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	pCur->stu.ID = Convert_wchart_to_int(a, end - begin);
	delete[] a;

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

	// Total Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	b.TotalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Fianal Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	b.FinalMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Midterm Mark
	begin = end + 1;
	end = str.find(',', begin + 1);
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	b.MidtermMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	// Other mark
	begin = end + 1;
	end = str.length();
	a = new wchar_t[end - begin + 1];
	str.copy(a, end - begin, begin);
	a[end - begin] = L'\0';
	b.OtherMark = Conver_wchart_to_double(a, end - begin);
	delete[] a;

	std::wstring str_4;
	wchar_t* file_2 = Convert_int_to_wchart(pCur->stu.ID);
	wchar_t* file_3 = Create_file_2(file_2, Create_second_folder("Student", current_year), ".txt");
	std::wifstream fin_2(file_3);
	fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin_2, str_4);
	begin = str_4.find(',', 0) + 1;
	end = str_4.length();
	pCur->stu.account.Pass = new wchar_t[end - begin + 1];
	str_4.copy(pCur->stu.account.Pass, end - begin, begin);
	pCur->stu.account.Pass[end - begin] = L'\0';
	std::getline(fin_2, str_4);
	Read_file_stu(str_4, pCur);
	std::getline(fin_2, str_4);
	Read_course_1(str_4, pCur);
	std::getline(fin_2, str_4);
	Read_course_2(str_4, pCur);
	std::getline(fin_2, str_4);
	Read_course_3(str_4, pCur);
	std::getline(fin_2, str_4);
	Read_course_4(str_4, pCur);
	std::getline(fin_2, str_4);
	Read_course_5(str_4, pCur);
	std::getline(fin_2, str_4);
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			pCur->stu.Schedule[i][j] = str_4[count] - int('0');
			count++;
		}
	}
	fin_2.close();

	if (wcscmp(Course_ID, pCur->stu.course_1.ID) == 0) {
		pCur->stu.course_1.FinalMark = b.FinalMark;
		pCur->stu.course_1.MidtermMark = b.MidtermMark;
		pCur->stu.course_1.OtherMark = b.OtherMark;
		pCur->stu.course_1.TotalMark = b.TotalMark;
	}
	else if (wcscmp(Course_ID, pCur->stu.course_2.ID) == 0) {
		pCur->stu.course_2.FinalMark = b.FinalMark;
		pCur->stu.course_2.MidtermMark = b.MidtermMark;
		pCur->stu.course_2.OtherMark = b.OtherMark;
		pCur->stu.course_2.TotalMark = b.TotalMark;
	}
	else if (wcscmp(Course_ID, pCur->stu.course_3.ID) == 0) {
		pCur->stu.course_3.FinalMark = b.FinalMark;
		pCur->stu.course_3.MidtermMark = b.MidtermMark;
		pCur->stu.course_3.OtherMark = b.OtherMark;
		pCur->stu.course_3.TotalMark = b.TotalMark;
	}
	else if (wcscmp(Course_ID, pCur->stu.course_4.ID) == 0) {
		pCur->stu.course_4.FinalMark = b.FinalMark;
		pCur->stu.course_4.MidtermMark = b.MidtermMark;
		pCur->stu.course_4.OtherMark = b.OtherMark;
		pCur->stu.course_4.TotalMark = b.TotalMark;
	}
	else if (wcscmp(Course_ID, pCur->stu.course_5.ID) == 0) {
		pCur->stu.course_5.FinalMark = b.FinalMark;
		pCur->stu.course_5.MidtermMark = b.MidtermMark;
		pCur->stu.course_5.OtherMark = b.OtherMark;
		pCur->stu.course_5.TotalMark = b.TotalMark;
	}

	_wremove(file_3);
	std::wofstream fout_1(file_3);
	fout_1.imbue(std::locale(fout_1.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	fout_1 << pCur->stu.account.ID << L"," << pCur->stu.account.Pass << std::endl;
	fout_1 << pCur->stu.ID << L"," << pCur->stu.FirstName << L"," << pCur->stu.LastName << L"," << pCur->stu.Gender << L"," << pCur->stu.Birthday.Day << L"/" << pCur->stu.Birthday.Month << L"/" << pCur->stu.Birthday.Year << L"," << pCur->stu.SocialID << std::endl;
	fout_1 << pCur->stu.course_1.ID << L"," << pCur->stu.course_1.TotalMark << L"," << pCur->stu.course_1.FinalMark << L"," << pCur->stu.course_1.MidtermMark << L"," << pCur->stu.course_1.OtherMark << L"," << pCur->stu.course_1.GPA << std::endl;
	fout_1 << pCur->stu.course_2.ID << L"," << pCur->stu.course_2.TotalMark << L"," << pCur->stu.course_2.FinalMark << L"," << pCur->stu.course_2.MidtermMark << L"," << pCur->stu.course_2.OtherMark << L"," << pCur->stu.course_2.GPA << std::endl;
	fout_1 << pCur->stu.course_3.ID << L"," << pCur->stu.course_3.TotalMark << L"," << pCur->stu.course_3.FinalMark << L"," << pCur->stu.course_3.MidtermMark << L"," << pCur->stu.course_3.OtherMark << L"," << pCur->stu.course_3.GPA << std::endl;
	fout_1 << pCur->stu.course_4.ID << L"," << pCur->stu.course_4.TotalMark << L"," << pCur->stu.course_4.FinalMark << L"," << pCur->stu.course_4.MidtermMark << L"," << pCur->stu.course_4.OtherMark << L"," << pCur->stu.course_4.GPA << std::endl;
	fout_1 << pCur->stu.course_5.ID << L"," << pCur->stu.course_5.TotalMark << L"," << pCur->stu.course_5.FinalMark << L"," << pCur->stu.course_5.MidtermMark << L"," << pCur->stu.course_5.OtherMark << L"," << pCur->stu.course_5.GPA << std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			fout_1 << pCur->stu.Schedule[i][j];
		}
	}
	fout_1.close();
}

void Input_score(Node_cou* pCur_cou, wchar_t* file_login) {
	std::wstring str_1;
	std::wstring str_2;
	std::wifstream fin(L"Default_time.txt");
	fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin, str_1);
	std::getline(fin, str_2);
	fin.close();
	char* current_year = new char[str_1.length() + 1];
	for (int i = 0; i < str_1.length(); i++) {
		current_year[i] = str_1[i];
	}
	current_year[str_1.length()] = L'\0';
	char* current_semester = new char[str_2.length() + 1];
	for (int i = 0; i < str_2.length(); i++) {
		current_semester[i] = str_2[i];
	}
	current_semester[str_2.length()] = L'\0';

	system("cls");
	Node_stu* pHead_stu = new Node_stu;
	Node_stu* pCur_stu = pHead_stu;
	std::wstring str_3;
	std::wstring str_4;
	std::wcout << "Please input the link: ";
	std::getline(std::wcin, str_3);
	std::wifstream fin_1(str_3);
	fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
	while (!fin_1.eof()) {
		std::getline(fin_1, str_4);
		pCur_stu->pNext = new Node_stu;
		fin_1.ignore();
		Input_one_score_student(str_4, pCur_stu, pCur_cou->cou.ID);
		pCur_stu = pCur_stu->pNext;
		pCur_stu->pNext = nullptr;
	}
	if (pHead_stu->pNext == nullptr) {
		delete pHead_stu;
		pHead_stu = nullptr;
	}
	else {
		Node_stu* pTemp = pHead_stu;
		pHead_stu = pHead_stu->pNext;
		delete pTemp;
	}
	fin_1.close();
	Delete_Node_stu(pHead_stu);
	std::wcout << "Input success" << std::endl;
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_course_score(pCur_cou,file_login);
	}
}