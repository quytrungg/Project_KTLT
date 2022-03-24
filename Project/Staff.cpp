#include "Struct.h"
#include "Staff.h"
#include "Help.h"
#include "Read.h"
#include<string>
#include "Time.h"
#include "Input.h"
#include "Save.h"
#include "Student.h"

wchar_t* Login_staff() {
	std::wstring str;
	wchar_t* pass = new wchar_t[1];
	pass[0] = L'\0';
	wchar_t* input = new wchar_t[1];
	input[0] = L'\0';
	wchar_t* filename = new wchar_t[1];
	filename[0] = L'\0';
	wchar_t* file = new wchar_t[1];
	file[0] = L'\0';
	int check = 0;
	do {
		system("cls");
		std::wcout << "Input the username: ";
		std::getline(std::wcin, str);
		delete[] filename;
		delete[] file;
		filename = new wchar_t[str.length() + 1];
		str.copy(filename, str.length(), 0);
		filename[str.length()] = L'\0';
		file = Create_file_3(filename, "Staff", ".txt");
		std::wifstream fin(file);
		if (!fin) {
			std::wcout << L"Error username \n";
			Sleep(100);
			check = 0;
		}
		else {
			fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin, str);
			delete[] pass;
			delete[] input;
			int begin = str.find(',', 0) + 1;
			int end = str.length();
			pass = new wchar_t[end - begin + 1];
			str.copy(pass, end - begin, begin);
			pass[end - begin] = L'\0';
			std::wcout << "Input the password: ";
			std::getline(std::wcin, str);
			input = new wchar_t[str.length() + 1];
			str.copy(input, str.length(), 0);
			input[str.length()] = L'\0';
			check = Check_pass(pass, input);
			if (check) {
				std::wcout << "Input success" << std::endl;
			}
			else {
				std::wcout << "Error password" << std::endl;
				Sleep(200);
			}
			fin.close();
		}
	} while (check != 1);
	delete[] pass;
	delete[] input;
	delete[] filename;
	return file;
}

void Screen_inf_to_console_staff(wchar_t* file) {
	system("cls");
	SetColor(15, 0);
	Node_staff* pHead_staff = new Node_staff;
	std::wstring str;
	std::wifstream fin(file);
	fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin, str);
	std::getline(fin, str);
	Read_file_staff(str, pHead_staff);
	fin.close();
	std::wcout << L"Staff ID: " << pHead_staff->staff.ID << std::endl;
	std::wcout << L"Staff Name: " << pHead_staff->staff.FirstName << L" " << pHead_staff->staff.LastName << std::endl;
	std::wcout << L"Gender: " << pHead_staff->staff.Gender << std::endl;
	std::wcout << L"Birthday: " << pHead_staff->staff.Birthday.Day << L"/" << pHead_staff->staff.Birthday.Month << L"/" << pHead_staff->staff.Birthday.Year << std::endl;
	std::wcout << L"Social ID: " << pHead_staff->staff.SocialID << std::endl;
	pHead_staff->pNext = nullptr;
	Delete_Node_staff(pHead_staff);
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_staff(file);
	}
}

void Change_pass_staff(wchar_t* file) {
	Node_staff* pHead_staff = new Node_staff;
	std::wstring str;
	std::wifstream fin(file);
	fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin, str);
	int begin = str.find(',', 0) + 1;
	int end = str.length();
	wchar_t* Older_pass = new wchar_t[end - begin + 1];
	str.copy(Older_pass, end - begin, begin);
	Older_pass[end - begin] = L'\0';
	std::getline(fin, str);
	Read_file_staff(str, pHead_staff);
	fin.close();

	int check = 0;
	do {
		system("cls");
		SetColor(15, 0);
		std::wcout << L"Please input the older password: ";
		std::getline(std::wcin, str);
		wchar_t* Input_older_pass = new wchar_t[str.length() + 1];
		str.copy(Input_older_pass, str.length(), 0);
		Input_older_pass[str.length()] = L'\0';
		check = Check_pass(Older_pass, Input_older_pass);
		if (check) {
			std::wcout << "Input the new password: ";
			std::getline(std::wcin, str);
			pHead_staff->staff.account.Pass = new wchar_t[str.length() + 1];
			str.copy(pHead_staff->staff.account.Pass, str.length(), 0);
			pHead_staff->staff.account.Pass[str.length()] = L'\0';
			std::wofstream fout(file);
			fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
			fout << pHead_staff->staff.account.ID << L"," << pHead_staff->staff.account.Pass << std::endl;
			fout << pHead_staff->staff.ID << L"," << pHead_staff->staff.FirstName << L"," << pHead_staff->staff.LastName << L"," << pHead_staff->staff.Gender << L"," << pHead_staff->staff.Birthday.Day << L"/" << pHead_staff->staff.Birthday.Month << L"/" << pHead_staff->staff.Birthday.Year << L"," << pHead_staff->staff.SocialID << std::endl;
			fout.close();
			pHead_staff->pNext = nullptr;
			Delete_Node_staff(pHead_staff);
			std::wcout << "Change success" << std::endl;
		}
		else {
			std::wcout << "Older pass not correct" << std::endl;
			Sleep(200);
		}
		delete[] Input_older_pass;
	} while (check != 1);
	delete[] Older_pass;
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_staff(file);
	}
}

void Create_school_year(wchar_t* file_login) {
	system("cls");
	SetColor(15, 0);
	int n1, n2,r,m;
	Time current_time;
	wchar_t* school_year_1 = new wchar_t[2];
	school_year_1[0] = L'0';
	school_year_1[1] = L'\0';
	Get_current_time_to_int(current_time);
	wchar_t** year = new wchar_t*[11];
	for (int i = 0; i < 11; i++) {
		year[i] = new wchar_t[10];
	}
	for (int i = 0; i < 11; i++) {
		n1 = current_time.date.Year - 5 + i;
		n2 = current_time.date.Year - 4 + i;
		int count = 0;
		m = 1000;
		for (int j = n1; j > 0; j = j / 10) {
			r = n1 / m;
			n1 = n1 - r * m;
			m = m / 10;
			year[i][count] = r + '0';
			count++;
		}
		year[i][count] = L'-';
		m = 1000;
		count++;
		for (int j = n2; j > 0; j = j / 10) {
			r = n2 / m;
			n2 = n2 - r * m;
			m = m / 10;
			year[i][count] = r + '0';
			count++;
		}
		year[i][count] = L'\0';
	}
	std::wstring str_1;
	std::wcout << "Please input the school year you want to create: ";
	int pointer = 5;
	int Max_List_Menu = 11;
	while (1) {
		//in menu ra man hinh
		GotoXY(50, 0);
		ShowCur(0);
		std::wcout << year[pointer] << std::endl;
		char key;
		while (1) {
			if (_kbhit()) {
				key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer < Max_List_Menu - 1) {
						pointer++;
					}
					else {
						pointer = 0;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer > 0) {
						pointer--;
					}
					else {
						pointer = Max_List_Menu - 1;
					}
					break;
				}
				if (key == 13) {
					school_year_1 = year[pointer];
					break;
				}
				if (key == 27) {
					Sub_menu_time_staff(file_login);
				}
			}
		}
		if (key == 13) {
			break;
		}
	}	
	std::wstring str_2;
	int check = 1;
	if (checkFileWithFstream_wstring(L"School_year.txt")) {
		Node_help_1* pHead_help_1 = new Node_help_1;
		Node_help_1* pCur_help_1 = pHead_help_1;
		std::wifstream fin("School_year.txt");
		fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin.eof()) {
			pCur_help_1->pNext = new Node_help_1;
			std::getline(fin, str_2);
			pCur_help_1->pNext->data = new wchar_t[str_2.length() + 1];
			str_2.copy(pCur_help_1->pNext->data, str_2.length(), 0);
			pCur_help_1->pNext->data[str_2.length()] = L'\0';
			pCur_help_1 = pCur_help_1->pNext;
			pCur_help_1->pNext = nullptr;
		}
		if (pHead_help_1->pNext == nullptr) {
			delete pHead_help_1;
			pHead_help_1 = nullptr;
		}
		else {
			Node_help_1* pTemp = pHead_help_1;
			pHead_help_1 = pHead_help_1->pNext;
			delete pTemp;
		}
		fin.close();

		pCur_help_1 = pHead_help_1;
		while (pCur_help_1 != nullptr) {
			if (wcscmp(pCur_help_1->data, school_year_1) == 0) {
				check = 0;
				break;
			}
			pCur_help_1 = pCur_help_1->pNext;
		}
	}
	if (check == 1) {
		char* school_year = new char[wcslen(year[pointer]) + 1];
		for (int i = 0; i < wcslen(year[pointer]); i++) {
			school_year[i] = school_year_1[i];
		}
		school_year[wcslen(year[pointer])] = '\0';
		_mkdir(school_year);
		_mkdir(Create_second_folder("Student", school_year));
		_mkdir(Create_second_folder("Semester", school_year));
		_mkdir(Create_second_folder("Class", school_year));
		wchar_t* file = Create_file_4("Time", Create_second_folder("Semester", school_year), ".txt");
		std::wofstream fout(file);
		fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		fout << 0 << std::endl;
		fout << 0 << std::endl;
		fout << 0 << std::endl;
		fout.close();


		if (checkFileWithFstream_wstring(L"School_year.txt")) {
			Node_help_1* pHead_help = new Node_help_1;
			Node_help_1* pCur_help = pHead_help;
			std::wifstream fin("School_year.txt");
			fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
			while (!fin.eof()) {
				pCur_help->pNext = new Node_help_1;
				std::getline(fin, str_2);
				pCur_help->pNext->data = new wchar_t[str_2.length() + 1];
				str_2.copy(pCur_help->pNext->data, str_2.length(), 0);
				pCur_help->pNext->data[str_2.length()] = L'\0';
				pCur_help = pCur_help->pNext;
				pCur_help->pNext = nullptr;
			}
			if (pHead_help->pNext == nullptr) {
				delete pHead_help;
				pHead_help = nullptr;
			}
			else {
				Node_help_1* pTemp = pHead_help;
				pHead_help = pHead_help->pNext;
				delete pTemp;
			}
			fin.close();

			pCur_help = pHead_help;
			_wremove(L"School_year.txt");
			std::wofstream fout_1(L"School_year.txt");
			fout_1.imbue(std::locale(fout_1.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
			while (pCur_help->pNext != nullptr) {
				fout_1 << pCur_help->data << std::endl;
				pCur_help = pCur_help->pNext;
			}
			fout_1 << school_year_1 << std::endl;
			fout_1.close();
			Delete_Node_help_1(pHead_help);
		}
		else {
			std::wofstream fout_2(L"School_year.txt");
			fout_2.imbue(std::locale(fout_2.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
			fout_2 << school_year << std::endl;
			fout_2.close();
		}
		std::wcout << "Input success" << std::endl;
	}
	else {
		std::wcout << "School year had been created" << std::endl;
	}
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_time_staff(file_login);
	}
}

void Create_semester_1(wchar_t* file_login) {
	std::wstring str_2;
	if (checkFileWithFstream_wstring(L"School_year.txt")) {
		int count = 0;
		Node_help_1* pHead_help = new Node_help_1;
		Node_help_1* pCur_help = pHead_help;
		std::wifstream fin("School_year.txt");
		fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin.eof()) {
			pCur_help->pNext = new Node_help_1;
			std::getline(fin, str_2);
			pCur_help->pNext->data = new wchar_t[str_2.length() + 1];
			str_2.copy(pCur_help->pNext->data, str_2.length(), 0);
			pCur_help->pNext->data[str_2.length()] = L'\0';
			pCur_help = pCur_help->pNext;
			pCur_help->pNext = nullptr;
			count++;
		}
		if (pHead_help->pNext == nullptr) {
			delete pHead_help;
			pHead_help = nullptr;
		}
		else {
			Node_help_1* pTemp = pHead_help;
			pHead_help = pHead_help->pNext;
			delete pTemp;
		}
		count--;
		fin.close();
		int x = 0;
		int check = 0;
		pCur_help = pHead_help;
		while (pCur_help != nullptr) {
			x++;
			pCur_help = pCur_help->pNext;
		}
		x--;
		int pointer = 0;
		while (1) {
			ShowCur(0);
			system("cls");
			pCur_help = pHead_help;
			int count = 0;
			while (pCur_help->pNext != nullptr) {
				if (count == pointer) {
					SetColor(15, 4);
					GotoXY(50, 20 + count);
					std::wcout << pCur_help->data;
				}
				else {
					SetColor(15, 3);
					GotoXY(50, 20 + count);
					std::wcout << pCur_help->data;
				}
				count++;
				pCur_help = pCur_help->pNext;
			}
			while (1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer > 0) {
							pointer--;
						}
						else {
							pointer = x - 1;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer < x - 1) {
							pointer++;
						}
						else {
							pointer = 0;
						}
						break;
					}
					if (key == 13) {
						pCur_help = pHead_help;
						if (pointer == -1) {

						}
						else{
							for (int i = 0; i < pointer; i++) {
								pCur_help = pCur_help->pNext;
							}
							check = 1;
							break;
						}
					}
					if (key == 27) {
						Sub_menu_time_staff(file_login);
					}
				}
			}
			if (check == 1) {
				break;
			}
		}

		char* folder = new char[wcslen(pCur_help->data) + 1];
		for (int i = 0; i < wcslen(pCur_help->data); i++) {
			folder[i] = pCur_help->data[i];
		}
		folder[wcslen(pCur_help->data)] = '\0';
		wchar_t* file = Create_file_4("Time", Create_second_folder("Semester", folder), ".txt");

		Create_semester_2(file,folder, file_login);
		delete[] file;
		delete[] folder;
		Delete_Node_help_1(pHead_help);
	}
	else {
		std::wcout << "Don't have any school year had been created" << std::endl;
	}
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_time_staff(file_login);
	}
}

void Create_semester_2(wchar_t* file, char* folder, wchar_t* file_login) {
	Node_help_1* pHead_help_1 = new Node_help_1;
	Node_help_1* pCur_help_1 = pHead_help_1;
	Node_time_semester* pHead_time = new Node_time_semester;
	Node_time_semester* pCur_time = pHead_time;
	std::wifstream fin_1(file);
	fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
	std::wstring kt = L"0";
	std::wstring kt1 = L"";
	std::wstring str_2;
	wchar_t* a;
	SetColor(15, 0);
	while (!fin_1.eof()) {
		pCur_help_1->pNext = new Node_help_1;
		pCur_time->pNext = new Node_time_semester;
		std::getline(fin_1, str_2);
		if (kt.compare(str_2) == 0) {
			pCur_help_1->pNext->data = new wchar_t[str_2.length() + 1];
			str_2.copy(pCur_help_1->pNext->data, str_2.length(), 0);
			pCur_help_1->pNext->data[str_2.length()] = L'\0';
		}
		else if (kt1.compare(str_2) != 0) {
			pCur_help_1->pNext->data = new wchar_t[2];
			pCur_help_1->pNext->data[0] = L'1';
			pCur_help_1->pNext->data[1] = L'\0';
			int begin = 0;
			int end = str_2.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->start.Day = Convert_wchart_to_int(a, end - begin);
			delete[] a;

			begin = end + 1;
			end = str_2.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->start.Month = Convert_wchart_to_int(a, end - begin);
			delete[] a;

			begin = end + 1;
			end = str_2.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->start.Year = Convert_wchart_to_int(a, end - begin);
			delete[] a;

			begin = end + 1;
			end = str_2.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->end.Day = Convert_wchart_to_int(a, end - begin);
			delete[] a;

			begin = end + 1;
			end = str_2.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->end.Month = Convert_wchart_to_int(a, end - begin);
			delete[] a;

			begin = end + 1;
			end = str_2.length();
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->end.Year = Convert_wchart_to_int(a, end - begin);
			delete[] a;
		}
		pCur_help_1 = pCur_help_1->pNext;
		pCur_help_1->pNext = nullptr;
		pCur_time = pCur_time->pNext;
		pCur_time->pNext = nullptr;
	}
	if (pHead_help_1->pNext == nullptr) {
		delete pHead_help_1;
		pHead_help_1 = nullptr;
	}
	else {
		Node_help_1* pTemp_1 = pHead_help_1;
		pHead_help_1 = pHead_help_1->pNext;
		delete pTemp_1;
	}
	if (pHead_time->pNext == nullptr) {
		delete pHead_time;
		pHead_time = nullptr;
	}
	else {
		Node_time_semester* pTemp_2 = pHead_time;
		pHead_time = pHead_time->pNext;
		delete pTemp_2;
	}
	fin_1.close();



	pCur_help_1 = pHead_help_1;
	int x = 0;
	while (pCur_help_1 != nullptr) {
		x++;
		pCur_help_1 = pCur_help_1->pNext;
	}
	x--;
	int pointer = 0;
	int check = 0;
	a = new wchar_t[2];
	a[0] = L'0';
	a[1] = L'\0';
	while (1) {
		ShowCur(0);
		system("cls");
		pCur_help_1 = pHead_help_1;
		pCur_time = pHead_time;
		int count = 0;
		while (pCur_help_1->pNext != nullptr && pCur_time->pNext != nullptr) {
			if (count == pointer) {
				SetColor(15, 4);
				GotoXY(50, 20 + count);
				std::wcout << count + 1 << ".";
				if (wcscmp(a, pCur_help_1->data) == 0) {
					std::wcout << "Not create";
				}
				else {
					std::wcout << pCur_time->start.Day << L'//' << pCur_time->start.Month << L'//' << pCur_time->start.Year << L',' << pCur_time->end.Day << L'//' << pCur_time->end.Month << L'//' << pCur_time->end.Year;
				}
			}
			else {
				SetColor(15, 3);
				GotoXY(50, 20 + count);
				std::wcout << count + 1 << ".";
				if (wcscmp(a, pCur_help_1->data) == 0) {
					std::wcout << "Not create";
				}
				else {
					std::wcout << pCur_time->start.Day << L'//' << pCur_time->start.Month << L'//' << pCur_time->start.Year << L',' << pCur_time->end.Day << L'//' << pCur_time->end.Month << L'//' << pCur_time->end.Year;
				}
			}
			count++;
			pCur_help_1 = pCur_help_1->pNext;
			pCur_time = pCur_time->pNext;
		}
		while (1) {
			if (_kbhit()) {
				char key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer > 0) {
						pointer--;
					}
					else {
						pointer = x - 1;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer < x - 1) {
						pointer++;
					}
					else {
						pointer = 0;
					}
					break;
				}
				if (key == 13) {
					pCur_help_1 = pHead_help_1;
					pCur_time = pHead_time;
					if (pointer == -1) {

					}
					else {
						for (int i = 0; i < pointer; i++) {
							pCur_help_1 = pCur_help_1->pNext;
						}
						for (int i = 0; i < pointer; i++) {
							pCur_time = pCur_time->pNext;
						}
						check = 1;
						break;
					}
				}
				if (key == 27) {
					Create_semester_1(file_login);
				}
			}
		}
		if (check == 1) {
			break;
		}
	}

	system("cls");
	if (wcscmp(a, pCur_help_1->data) != 0) {
		std::wcout << "Semester had been created" << std::endl;
	}
	else {
		Time current_time;
		Get_current_time_to_int(current_time);
		int* year = new int[11];
		int* month = new int[12];
		int* day_1 = new int[31];
		int* day_2 = new int[30];
		int* day_3 = new int[29];
		int* day_4 = new int[28];
		for (int i = 0; i < 11; i++) {
			year[i] = current_time.date.Year - 5 + i;
		}
		for (int i = 0; i < 12; i++) {
			month[i] = i + 1;
		}
		for (int i = 0; i < 31; i++) {
			day_1[i] = i + 1;
		}
		for (int i = 0; i < 30; i++) {
			day_2[i] = i + 1;
		}
		for (int i = 0; i < 29; i++) {
			day_3[i] = i + 1;
		}
		for (int i = 0; i < 28; i++) {
			day_4[i] = i + 1;
		}
		std::wcout << "Start date:" << std::endl;
		std::wcout << "Year: ";
		int pointer_1 = 5;
		int Max_List_Menu = 11;
		while (1) {
			//in menu ra man hinh
			GotoXY(7, 1);
			ShowCur(0);
			std::wcout << year[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->start.Year = year[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
		GotoXY(13, 1);
		std::wcout << "Month: ";
		pointer_1 = 0;
		Max_List_Menu = 12;
		while (1) {
			//in menu ra man hinh
			GotoXY(22, 1);
			ShowCur(0);
			if (month[pointer_1] < 10) {
				std::wcout << 0;
			}
			std::wcout << month[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->start.Month = month[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
		GotoXY(26, 1);
		std::wcout << "Day: ";
		if (pCur_time->start.Month == 1 || pCur_time->start.Month == 3 || pCur_time->start.Month == 5 || pCur_time->start.Month == 7 || pCur_time->start.Month == 8 || pCur_time->start.Month == 10 || pCur_time->start.Month == 12) {
			pointer_1 = 0;
			Max_List_Menu = 31;
			while (1) {
				//in menu ra man hinh
				GotoXY(33, 1);
				ShowCur(0);
				if (day_1[pointer_1] < 10) {
					std::wcout << 0;
				}
				std::wcout << day_1[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->start.Day = day_1[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
		}
		else if (pCur_time->start.Month != 2) {
			pointer_1 = 0;
			Max_List_Menu = 30;
			while (1) {
				//in menu ra man hinh
				GotoXY(33, 1);
				ShowCur(0);
				if (day_2[pointer_1] < 10) {
					std::wcout << 0;
				}
				std::wcout << day_2[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->start.Day = day_2[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
		}
		else if (checkYear(pCur_time->start.Year)) {
			pointer_1 = 0;
			Max_List_Menu = 29;
			while (1) {
				//in menu ra man hinh
				GotoXY(33, 1);
				ShowCur(0);
				if (day_3[pointer_1] < 10) {
					std::wcout << 0;
				}
				std::wcout << day_3[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->start.Day = day_3[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
		}
		else {
			pointer_1 = 0;
			Max_List_Menu = 28;
			while (1) {
				//in menu ra man hinh
				GotoXY(33, 1);
				ShowCur(0);
				if (day_4[pointer_1] < 10) {
					std::wcout << 0;
				}
				std::wcout << day_4[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->start.Day = day_4[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
		}

		GotoXY(0, 2);
		std::wcout << "End date:" << std::endl;
		std::wcout << "Year: ";
		pointer_1 = 5;
		Max_List_Menu = 11;
		while (1) {
			//in menu ra man hinh
			GotoXY(7, 3);
			ShowCur(0);
			std::wcout << year[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->end.Year = year[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
		GotoXY(13, 3);
		std::wcout << "Month: ";
		pointer_1 = 0;
		Max_List_Menu = 12;
		while (1) {
			//in menu ra man hinh
			GotoXY(22, 3);
			ShowCur(0);
			if (month[pointer_1] < 10) {
				std::wcout << 0;
			}
			std::wcout << month[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->end.Month = month[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
		GotoXY(26, 3);
		std::wcout << "Day: ";
		if (pCur_time->end.Month == 1 || pCur_time->end.Month == 3 || pCur_time->end.Month == 5 || pCur_time->end.Month == 7 || pCur_time->end.Month == 8 || pCur_time->end.Month == 10 || pCur_time->end.Month == 12) {
			pointer_1 = 0;
			Max_List_Menu = 31;
			while (1) {
				//in menu ra man hinh
				GotoXY(33, 3);
				ShowCur(0);
				if (day_1[pointer_1] < 10) {
					std::wcout << 0;
				}
				std::wcout << day_1[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->end.Day = day_1[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
		}
		else if (pCur_time->end.Month != 2) {
			pointer_1 = 0;
			Max_List_Menu = 30;
			while (1) {
				//in menu ra man hinh
				GotoXY(33, 3);
				ShowCur(0);
				if (day_2[pointer_1] < 10) {
					std::wcout << 0;
				}
				std::wcout << day_2[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->end.Day = day_2[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
		}
		else if (checkYear(pCur_time->end.Year)) {
			pointer_1 = 0;
			Max_List_Menu = 29;
			while (1) {
				//in menu ra man hinh
				GotoXY(33, 3);
				ShowCur(0);
				if (day_3[pointer_1] < 10) {
					std::wcout << 0;
				}
				std::wcout << day_3[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->end.Day = day_3[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
		}
		else {
			pointer_1 = 0;
			Max_List_Menu = 28;
			while (1) {
				//in menu ra man hinh
				GotoXY(33, 3);
				ShowCur(0);
				if (day_4[pointer_1] < 10) {
					std::wcout << 0;
				}
				std::wcout << day_4[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->end.Day = day_4[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
		}

		delete[] year;
		delete[] month;
		delete[] day_1;
		delete[] day_2;
		delete[] day_3;
		delete[] day_4;

		if (compare2Times(pCur_time->start, pCur_time->end)) {
			delete pCur_help_1->data;
			pCur_help_1->data = new wchar_t[2];
			pCur_help_1->data[0] = L'1';
			pCur_help_1->data[1] = L'\0';
			if (pointer == 0) {
				_mkdir(Create_third_folder("1", Create_second_folder("Semester", folder)));
			}
			else if (pointer == 1) {
				_mkdir(Create_third_folder("2", Create_second_folder("Semester", folder)));
			}
			else if (pointer == 2) {
				_mkdir(Create_third_folder("3", Create_second_folder("Semester", folder)));
			}
			std::wcout << "Input success" << std::endl;
		}
		else {
			std::wcout << "End date is smaller than start date. Input wrong" << std::endl;
		}
	}
	_wremove(file);
	a = new wchar_t[2];
	a[0] = L'0';
	a[1] = L'\0';
	pCur_help_1 = pHead_help_1;
	pCur_time = pHead_time;
	std::wofstream fout(file);
	fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	while (pCur_help_1->pNext != nullptr) {
		if (wcscmp(a, pCur_help_1->data) == 0) {
			fout << pCur_help_1->data << std::endl;
		}
		else {
			fout << pCur_time->start.Day << L"," << pCur_time->start.Month << L"," << pCur_time->start.Year << L"," << pCur_time->end.Day << L"," << pCur_time->end.Month << L"," << pCur_time->end.Year << std::endl;
		}
		pCur_help_1 = pCur_help_1->pNext;
		pCur_time = pCur_time->pNext;
	}
	fout.close();
	Delete_Node_time_semester(pHead_time);
	Delete_Node_help_1(pHead_help_1);
	delete[] a;

	char key = toupper(_getch());
	if (key == 27)
	{
		Create_semester_1(file_login);
	}
}

void Choose_default_time_1(wchar_t* file_login, int n) {
	std::wstring str_2;
	if (checkFileWithFstream_wstring(L"Default_time.txt") && n == 0) {
		system("cls");
		std::wcout << "The default time had been choosed. You want to do it again ?" << std::endl;
		std::wcout << "Y to continue or N to exit" << std::endl;
		char key = _getch();
		if (key == 'N' || key == 'n' || key == 27)
		{
			Sub_menu_time_staff(file_login);
		}
		else if (key == 'Y' || key == 'y') {
			if (checkFileWithFstream_wstring(L"School_year.txt")) {
				int count = 0;
				Node_help_1* pHead_help = new Node_help_1;
				Node_help_1* pCur_help = pHead_help;
				std::wifstream fin("School_year.txt");
				fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
				while (!fin.eof()) {
					pCur_help->pNext = new Node_help_1;
					std::getline(fin, str_2);
					pCur_help->pNext->data = new wchar_t[str_2.length() + 1];
					str_2.copy(pCur_help->pNext->data, str_2.length(), 0);
					pCur_help->pNext->data[str_2.length()] = L'\0';
					pCur_help = pCur_help->pNext;
					pCur_help->pNext = nullptr;
					count++;
				}
				if (pHead_help->pNext == nullptr) {
					delete pHead_help;
					pHead_help = nullptr;
				}
				else {
					Node_help_1* pTemp = pHead_help;
					pHead_help = pHead_help->pNext;
					delete pTemp;
				}
				count--;
				fin.close();
				int x = 0;
				int check = 0;
				pCur_help = pHead_help;
				while (pCur_help != nullptr) {
					x++;
					pCur_help = pCur_help->pNext;
				}
				x--;
				int pointer = 0;
				while (1) {
					ShowCur(0);
					system("cls");
					pCur_help = pHead_help;
					int count = 0;
					while (pCur_help->pNext != nullptr) {
						if (count == pointer) {
							SetColor(15, 4);
							GotoXY(50, 20 + count);
							std::wcout << pCur_help->data;
						}
						else {
							SetColor(15, 3);
							GotoXY(50, 20 + count);
							std::wcout << pCur_help->data;
						}
						count++;
						pCur_help = pCur_help->pNext;
					}
					while (1) {
						if (_kbhit()) {
							char key = _getch();
							if (key == 72 || key == 'w' || key == 'W') {
								if (pointer > 0) {
									pointer--;
								}
								else {
									pointer = x - 1;
								}
								break;
							}
							if (key == 80 || key == 's' || key == 'S') {
								if (pointer < x - 1) {
									pointer++;
								}
								else {
									pointer = 0;
								}
								break;
							}
							if (key == 13) {
								pCur_help = pHead_help;
								if (pointer == -1) {

								}
								else {
									for (int i = 0; i < pointer; i++) {
										pCur_help = pCur_help->pNext;
									}
									check = 1;
									break;
								}
							}
							if (key == 27) {
								Sub_menu_time_staff(file_login);
							}
						}
					}
					if (check == 1) {
						break;
					}
				}

				char* folder = new char[wcslen(pCur_help->data) + 1];
				for (int i = 0; i < wcslen(pCur_help->data); i++) {
					folder[i] = pCur_help->data[i];
				}
				folder[wcslen(pCur_help->data)] = '\0';
				default_year_1 = folder;
				default_year_2 = new wchar_t[wcslen(pCur_help->data) + 1];
				for (int i = 0; i < wcslen(pCur_help->data); i++) {
					default_year_2[i] = default_year_1[i];
				}
				default_year_2[wcslen(pCur_help->data)] = L'\0';
				wchar_t* file = Create_file_4("Time", Create_second_folder("Semester", folder), ".txt");
				Choose_default_time_2(file, folder, file_login, default_year_1, default_year_2);
				Delete_Node_help_1(pHead_help);
			}
			else {
				std::wcout << "School year not created" << std::endl;
			}
			char key = toupper(_getch());
			if (key == 27)
			{
				Sub_menu_time_staff(file_login);
			}
		}
	}
	else {
	if (checkFileWithFstream_wstring(L"School_year.txt")) {
		int count = 0;
		Node_help_1* pHead_help = new Node_help_1;
		Node_help_1* pCur_help = pHead_help;
		std::wifstream fin("School_year.txt");
		fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin.eof()) {
			pCur_help->pNext = new Node_help_1;
			std::getline(fin, str_2);
			pCur_help->pNext->data = new wchar_t[str_2.length() + 1];
			str_2.copy(pCur_help->pNext->data, str_2.length(), 0);
			pCur_help->pNext->data[str_2.length()] = L'\0';
			pCur_help = pCur_help->pNext;
			pCur_help->pNext = nullptr;
			count++;
		}
		if (pHead_help->pNext == nullptr) {
			delete pHead_help;
			pHead_help = nullptr;
		}
		else {
			Node_help_1* pTemp = pHead_help;
			pHead_help = pHead_help->pNext;
			delete pTemp;
		}
		count--;
		fin.close();
		int x = 0;
		int check = 0;
		pCur_help = pHead_help;
		while (pCur_help != nullptr) {
			x++;
			pCur_help = pCur_help->pNext;
		}
		x--;
		int pointer = 0;
		while (1) {
			ShowCur(0);
			system("cls");
			pCur_help = pHead_help;
			int count = 0;
			while (pCur_help->pNext != nullptr) {
				if (count == pointer) {
					SetColor(15, 4);
					GotoXY(50, 20 + count);
					std::wcout << pCur_help->data;
				}
				else {
					SetColor(15, 3);
					GotoXY(50, 20 + count);
					std::wcout << pCur_help->data;
				}
				count++;
				pCur_help = pCur_help->pNext;
			}
			while (1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer > 0) {
							pointer--;
						}
						else {
							pointer = x - 1;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer < x - 1) {
							pointer++;
						}
						else {
							pointer = 0;
						}
						break;
					}
					if (key == 13) {
						pCur_help = pHead_help;
						if (pointer == -1) {

						}
						else {
							for (int i = 0; i < pointer; i++) {
								pCur_help = pCur_help->pNext;
							}
							check = 1;
							break;
						}
					}
					if (key == 27) {
						Sub_menu_time_staff(file_login);
					}
				}
			}
			if (check == 1) {
				break;
			}
		}

		char* folder = new char[wcslen(pCur_help->data) + 1];
		for (int i = 0; i < wcslen(pCur_help->data); i++) {
			folder[i] = pCur_help->data[i];
		}
		folder[wcslen(pCur_help->data)] = '\0';
		default_year_1 = folder;
		default_year_2 = new wchar_t[wcslen(pCur_help->data) + 1];
		for (int i = 0; i < wcslen(pCur_help->data); i++) {
			default_year_2[i] = default_year_1[i];
		}
		default_year_2[wcslen(pCur_help->data)] = L'\0';
		wchar_t* file = Create_file_4("Time", Create_second_folder("Semester", folder), ".txt");
		Choose_default_time_2(file, folder, file_login, default_year_1, default_year_2);
		Delete_Node_help_1(pHead_help);
	}
	else {
		std::wcout << "School year not created" << std::endl;
	}
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_time_staff(file_login);
	}
	}
}

void Choose_default_time_2(wchar_t* file, char* folder, wchar_t* file_login, char* default_year_1, wchar_t* default_year_2) {
	std::wstring str_2;
	Node_help_1* pHead_help_1 = new Node_help_1;
	Node_help_1* pCur_help_1 = pHead_help_1;
	Node_time_semester* pHead_time = new Node_time_semester;
	Node_time_semester* pCur_time = pHead_time;
	std::wifstream fin_1(file);
	fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
	std::wstring kt = L"0";
	std::wstring kt1 = L"";
	wchar_t* a;
	while (!fin_1.eof()) {
		pCur_help_1->pNext = new Node_help_1;
		pCur_time->pNext = new Node_time_semester;
		std::getline(fin_1, str_2);
		if (kt.compare(str_2) == 0) {
			pCur_help_1->pNext->data = new wchar_t[str_2.length() + 1];
			str_2.copy(pCur_help_1->pNext->data, str_2.length(), 0);
			pCur_help_1->pNext->data[str_2.length()] = L'\0';
		}
		else if (kt1.compare(str_2) != 0) {
			pCur_help_1->pNext->data = new wchar_t[2];
			pCur_help_1->pNext->data[0] = L'1';
			pCur_help_1->pNext->data[1] = L'\0';
			int begin = 0;
			int end = str_2.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->start.Day = Convert_wchart_to_int(a, end - begin);
			delete[] a;

			begin = end + 1;
			end = str_2.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->start.Month = Convert_wchart_to_int(a, end - begin);
			delete[] a;

			begin = end + 1;
			end = str_2.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->start.Year = Convert_wchart_to_int(a, end - begin);
			delete[] a;

			begin = end + 1;
			end = str_2.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->end.Day = Convert_wchart_to_int(a, end - begin);
			delete[] a;

			begin = end + 1;
			end = str_2.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->end.Month = Convert_wchart_to_int(a, end - begin);
			delete[] a;

			begin = end + 1;
			end = str_2.length();
			a = new wchar_t[end - begin + 1];
			str_2.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_time->pNext->end.Year = Convert_wchart_to_int(a, end - begin);
			delete[] a;
		}
		pCur_help_1 = pCur_help_1->pNext;
		pCur_help_1->pNext = nullptr;
		pCur_time = pCur_time->pNext;
		pCur_time->pNext = nullptr;
	}
	if (pHead_help_1->pNext == nullptr) {
		delete pHead_help_1;
		pHead_help_1 = nullptr;
	}
	else {
		Node_help_1* pTemp_1 = pHead_help_1;
		pHead_help_1 = pHead_help_1->pNext;
		delete pTemp_1;
	}
	if (pHead_time->pNext == nullptr) {
		delete pHead_time;
		pHead_time = nullptr;
	}
	else {
		Node_time_semester* pTemp_2 = pHead_time;
		pHead_time = pHead_time->pNext;
		delete pTemp_2;
	}
	fin_1.close();

	pCur_help_1 = pHead_help_1;
	int x = 0;
	while (pCur_help_1 != nullptr) {
		x++;
		pCur_help_1 = pCur_help_1->pNext;
	}
	x--;
	int pointer = 0;
	int check = 0;
	a = new wchar_t[2];
	a[0] = L'0';
	a[1] = L'\0';
	while (1) {
		ShowCur(0);
		system("cls");
		pCur_help_1 = pHead_help_1;
		pCur_time = pHead_time;
		int count = 0;
		while (pCur_help_1->pNext != nullptr) {
			if (count == pointer) {
				SetColor(15, 4);
				GotoXY(50, 20 + count);
				std::wcout << count + 1 << ".";
				if (wcscmp(a, pCur_help_1->data) == 0) {
					std::wcout << "Not create";
				}
				else {
					std::wcout << pCur_time->start.Day << L'//' << pCur_time->start.Month << L'//' << pCur_time->start.Year << L',' << pCur_time->end.Day << L'//' << pCur_time->end.Month << L'//' << pCur_time->end.Year;
				}
			}
			else {
				SetColor(15, 3);
				GotoXY(50, 20 + count);
				std::wcout << count + 1 << ".";
				if (wcscmp(a, pCur_help_1->data) == 0) {
					std::wcout << "Not create";
				}
				else {
					std::wcout << pCur_time->start.Day << L'//' << pCur_time->start.Month << L'//' << pCur_time->start.Year << L',' << pCur_time->end.Day << L'//' << pCur_time->end.Month << L'//' << pCur_time->end.Year;
				}
			}
			count++;
			pCur_help_1 = pCur_help_1->pNext;
			pCur_time = pCur_time->pNext;
		}
		while (1) {
			if (_kbhit()) {
				char key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer > 0) {
						pointer--;
					}
					else {
						pointer = x - 1;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer < x - 1) {
						pointer++;
					}
					else {
						pointer = 0;
					}
					break;
				}
				if (key == 13) {
					pCur_help_1 = pHead_help_1;
					pCur_time = pHead_time;
					if (pointer == -1) {

					}
					else {
						for (int i = 0; i < pointer; i++) {
							pCur_help_1 = pCur_help_1->pNext;
						}
						for (int i = 0; i < pointer; i++) {
							pCur_time = pCur_time->pNext;
						}
						check = 1;
						break;
					}
				}
				if (key == 27) {
					Choose_default_time_1(file_login,1);
				}
			}
		}
		if (check == 1) {
			break;
		}
	}
	Time current_time;
	Get_current_time_to_int(current_time);
	if (wcscmp(a, pCur_help_1->data) == 0) {
		system("cls");
		std::wcout << "Semester has not been created. You can not choose" << std::endl;
	}
	else {
		if (compare2Times(current_time.date, pCur_time->end)) {
			if (pointer == 0) {
				default_semester_1 = Create_third_folder("1", Create_second_folder("Semester", default_year_1));
			}
			else if (pointer == 1) {
				default_semester_1 = Create_third_folder("2", Create_second_folder("Semester", default_year_1));
			}
			else {
				default_semester_1 = Create_third_folder("3", Create_second_folder("Semester", default_year_1));
			}
			default_semester_2 = new wchar_t[strlen(default_semester_1) + 1];
			for (int i = 0; i < strlen(default_semester_1); i++) {
				default_semester_2[i] = default_semester_1[i];
			}
			default_semester_2[strlen(default_semester_1)] = L'\0';
			_wremove(L"Default_time.txt");
			std::wofstream fout(L"Default_time.txt");
			fout << default_year_1 << std::endl;
			fout << default_semester_1 << std::endl;
			fout.close();
			Delete_Node_help_1(pHead_help_1);
			Delete_Node_time_semester(pHead_time);
			delete[] file;
			delete[] folder;
			delete[] default_semester_1;
			delete[] default_semester_2;
			delete[] default_year_1;
			delete[] default_year_2;
			system("cls");
			std::wcout << "Choose success" << std::endl;
			char key = toupper(_getch());
			if (key == 27)
			{
				Sub_menu_time_staff(file_login);
			}
		}
		else {
			system("cls");
			std::wcout << "Semester had been ended. Choose fail" << std::endl;
			delete[] default_semester_1;
			delete[] default_semester_2;
			delete[] default_year_1;
			delete[] default_year_2;
		}
	}
	Delete_Node_help_1(pHead_help_1);
	Delete_Node_time_semester(pHead_time);
	delete[] file;
	delete[] folder;
	

	char key = toupper(_getch());
	if (key == 27)
	{
		Choose_default_time_1(file_login,1);
	}
}

void View_list_of_class(wchar_t* file) {
	Node_cla* pHead_cla;
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
	system("cls");
	if (checkFileWithFstream_wstring(Create_file_4("Class", Create_second_folder("Class", current_year), ".txt"))) {
		pHead_cla = new Node_cla;
		Node_cla* pCur_cla = pHead_cla;
		std::wstring str;
		int x = 0;
		std::wifstream fin(Create_file_4("Class", Create_second_folder("Class", current_year), ".txt"));
		fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin.eof()) {
			pCur_cla->pNext = new Node_cla;
			std::getline(fin, str);
			pCur_cla->pNext->cla.Name = new wchar_t[str.length() + 1];
			str.copy(pCur_cla->pNext->cla.Name, str.length(), 0);
			pCur_cla->pNext->cla.Name[str.length()] = L'\0';
			pCur_cla = pCur_cla->pNext;
			pCur_cla->pNext = nullptr;
			x++;
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
		x--;
		int pointer = 0;
		int check = 0;
		while (1) {
			ShowCur(0);
			system("cls");
			pCur_cla = pHead_cla;
			int count = 0;
			while (pCur_cla->pNext != nullptr) {
				if (count == pointer) {
					SetColor(15, 4);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cla->cla.Name;
				}
				else {
					SetColor(15, 3);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cla->cla.Name;
				}
				count++;
				pCur_cla = pCur_cla->pNext;
			}
			while (1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer > 0) {
							pointer--;
						}
						else {
							pointer = x - 1;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer < x - 1) {
							pointer++;
						}
						else {
							pointer = 0;
						}
						break;
					}
					if (key == 13) {
						pCur_cla = pHead_cla;
						if (pointer == -1) {

						}
						else {
							for (int i = 0; i < pointer; i++) {
								pCur_cla = pCur_cla->pNext;
							}
							check = 1;
							break;
						}
					}
					if (key == 27) {
						Sub_menu_stu_staff(file);
					}
				}
			}
			if (check == 1) {
				break;
			}
		}
		View_list_of_student_class(pCur_cla->cla.Name, current_year,file);
	}
	else {
		system("cls");
		std::wcout << "No class had been added" << std::endl;
	}
	delete[] current_year;
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_stu_staff(file);
	}
}

void View_list_of_student_class(wchar_t* cla, char* current_year, wchar_t* file) {
	Node_stu* pHead_stu = new Node_stu;
	Node_stu* pCur_stu = pHead_stu;
	std::wstring str_1;
	std::wifstream fin(Create_file_3(cla, Create_second_folder("Class", current_year), ".txt"));
	fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin, str_1);
	std::getline(fin, str_1);
	fin.close();
	int loop = str_1.length() / 9;
	int begin = 0;
	int end = -1;
	wchar_t* a;
	for (int i = 0; i < loop; i++) {
		pCur_stu->pNext = new Node_stu;
		begin = end + 1;
		end = str_1.find(',', begin);
		a = new wchar_t[end - begin + 1];
		str_1.copy(a, end - begin, begin);
		a[end - begin] = L'\0';
		pCur_stu->pNext->stu.ID = Convert_wchart_to_int(a, end - begin);
		delete[] a;
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
	pCur_stu = pHead_stu;
	for (int i = 0; i < loop; i++) {
		wchar_t* file_1 = Convert_int_to_wchart(pCur_stu->stu.ID);
		wchar_t* file_2 = Create_file_2(file_1, Create_second_folder("Student", current_year), ".txt");
		std::wifstream fin(file_2);
		fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
		std::getline(fin, str_1);
		std::getline(fin, str_1);
		Read_file_stu(str_1, pCur_stu);
		fin.close();
		pCur_stu = pCur_stu->pNext;
	}
	system("cls");
	SetColor(15, 0);
	std::wcout << cla << std::endl;
	pCur_stu = pHead_stu;
	for (int i = 0; i < loop; i++) {
		std::wcout << i + 1 << L"," << pCur_stu->stu.ID << L"," << pCur_stu->stu.FirstName << L" " << pCur_stu->stu.LastName << L"," << pCur_stu->stu.Gender << L"," << pCur_stu->stu.Birthday.Day << L"/" << pCur_stu->stu.Birthday.Month << L"/" << pCur_stu->stu.Birthday.Year << L"," << pCur_stu->stu.SocialID << std::endl;
		pCur_stu = pCur_stu->pNext;
	}
	Delete_Node_stu(pHead_stu);
	char key = toupper(_getch());
	if (key == 27)
	{
		View_list_of_class(file);
	}
}

void View_list_of_course(wchar_t* file_login) {
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
	if (checkFileWithFstream_wstring(Create_file_4("Course", current_semester, ".txt"))) {
		std::wstring str_3;
		Node_cou* pHead_cou = new Node_cou;
		Node_cou* pCur_cou = pHead_cou;
		int x = 0;
		std::wifstream fin_1(Create_file_4("Course", current_semester, ".txt"));
		fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin_1.eof()) {
			pCur_cou->pNext = new Node_cou;
			std::getline(fin_1, str_3);
			pCur_cou->pNext->cou.ID = new wchar_t[str_3.length() + 1];
			str_3.copy(pCur_cou->pNext->cou.ID, str_3.length(), 0);
			pCur_cou->pNext->cou.ID[str_3.length()] = L'\0';
			pCur_cou = pCur_cou->pNext;
			pCur_cou->pNext = nullptr;
			x++;
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
		fin_1.close();
		x--;
		pCur_cou = pHead_cou;
		for (int i = 0; i < x; i++) {
			wchar_t* file_1 = Create_file_2(pCur_cou->cou.ID, current_semester, ".txt");
			std::wifstream fin_2(file_1);
			fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_2, str_1);
			Read_file_cou(str_1, pCur_cou);
			fin_2.close();
			pCur_cou = pCur_cou->pNext;
		}
		int pointer = 0;
		int check = 0;
		while (1) {
			ShowCur(0);
			system("cls");
			pCur_cou = pHead_cou;
			int count = 0;
			while (pCur_cou->pNext != nullptr) {
				if (count == pointer) {
					SetColor(15, 4);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cou->cou.ID << "." << pCur_cou->cou.Name;
				}
				else {
					SetColor(15, 3);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cou->cou.ID << "." << pCur_cou->cou.Name;
				}
				count++;
				pCur_cou = pCur_cou->pNext;
			}
			while (1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer > 0) {
							pointer--;
						}
						else {
							pointer = x - 1;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer < x - 1) {
							pointer++;
						}
						else {
							pointer = 0;
						}
						break;
					}
					if (key == 13) {
						pCur_cou = pHead_cou;
						if (pointer == -1) {

						}
						else {
							for (int i = 0; i < pointer; i++) {
								pCur_cou = pCur_cou->pNext;
							}
							check = 1;
							break;
						}
					}
					if (key == 27) {
						Sub_menu_cou_staff(file_login);
					}
				}
			}
			if (check == 1) {
				break;
			}
		}
		Menu_view_cou_staff(pCur_cou, file_login);
		Delete_Node_cou(pHead_cou);
	}
	else {
		system("cls");
		std::wcout << "No course had been created" << std::endl;
	}
	delete[] current_year;
	delete[] current_semester;
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_cou_staff(file_login);
	}
}

void Cout_day_of_week(int n) {
	switch (n) {
	case 0:
	{
		std::wcout << L"MON";
		break;
	}
	case 1:
	{
		std::wcout << L"TUE";
		break;
	}
	case 2:
	{
		std::wcout << L"WED";
		break;
	}
	case 3:
	{
		std::wcout << L"THU";
		break;
	}
	case 4:
	{
		std::wcout << L"FRI";
		break;
	}
	case 5:
	{
		std::wcout << L"SAT";
		break;
	}
	}
}

void Print_inf_cou_console(Node_cou* pCur_cou, wchar_t* file_login) {
	system("cls");
	SetColor(15, 0);
	std::wcout << L"Course ID: " << pCur_cou->cou.ID << std::endl;;
	std::wcout << L"Course Name: " << pCur_cou->cou.Name << std::endl;
	std::wcout << L"Teacher Name: " << pCur_cou->cou.Teacher_Name << std::endl;
	std::wcout << L"Number of credits: " << pCur_cou->cou.Credit << std::endl;
	std::wcout << L"Registered students / Max student of course: " << pCur_cou->cou.count << L"/" << pCur_cou->cou.max_stu << std::endl;
	std::wcout << L"Session 1: ";
	Cout_day_of_week(pCur_cou->cou.ses_1.day_of_week);
	std::wcout << L" - S" << pCur_cou->cou.ses_1.session + 1 << std::endl;
	std::wcout << L"Session 2: ";
	Cout_day_of_week(pCur_cou->cou.ses_2.day_of_week);
	std::wcout << L" - S" << pCur_cou->cou.ses_2.session + 1 << std::endl;
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_view_cou_staff(pCur_cou, file_login);
	}
}

void View_list_of_student_course(Node_cou* pCur_cou, wchar_t* file_login) {
	system("cls");
	if (pCur_cou->cou.count != 0) {
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
		std::wstring str_3;
		wchar_t* file_1 = Create_file_2(pCur_cou->cou.ID, current_semester, ".txt");
		std::wifstream fin_1(file_1);
		fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
		std::getline(fin_1, str_3);
		std::getline(fin_1, str_3);
		fin_1.close();
		Node_stu* pHead_stu = new Node_stu;
		Node_stu* pCur_stu = pHead_stu;
		int begin = 0;
		int end = -1;
		wchar_t* a;
		for (int i = 0; i < pCur_cou->cou.count; i++) {
			pCur_stu->pNext = new Node_stu;
			begin = end + 1;
			end = str_3.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_3.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_stu->pNext->stu.ID = Convert_wchart_to_int(a, end - begin);
			delete[] a;
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
		std::wstring str_4;
		pCur_stu = pHead_stu;
		for (int i = 0; i < pCur_cou->cou.count; i++) {
			wchar_t* file_2 = Convert_int_to_wchart(pCur_stu->stu.ID);
			wchar_t* file_3 = Create_file_2(file_2, Create_second_folder("Student", current_year), ".txt");
			std::wifstream fin_2(file_3);
			fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_2, str_4);
			std::getline(fin_2, str_4);
			Read_file_stu(str_4, pCur_stu);
			fin_2.close();
			pCur_stu = pCur_stu->pNext;
		}
		system("cls");
		SetColor(15, 0);
		std::wcout << pCur_cou->cou.ID << L"." << pCur_cou->cou.Name << std::endl;
		pCur_stu = pHead_stu;
		for (int i = 0; i < pCur_cou->cou.count; i++) {
			std::wcout << i + 1 << L"," << pCur_stu->stu.ID << L"," << pCur_stu->stu.FirstName << L" " << pCur_stu->stu.LastName << L"," << pCur_stu->stu.Gender << L"," << pCur_stu->stu.Birthday.Day << L"/" << pCur_stu->stu.Birthday.Month << L"/" << pCur_stu->stu.Birthday.Year << L"," << pCur_stu->stu.SocialID << std::endl;
			pCur_stu = pCur_stu->pNext;
		}
		delete[] current_year;
		delete[] current_semester;
		Delete_Node_stu(pHead_stu);
	}
	else {
		system("cls");
		std::wcout << "No students registered this course" << std::endl;
	}
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_view_cou_staff(pCur_cou, file_login);
	}
}

void Export_list_of_student_course(Node_cou* pCur_cou, wchar_t* file_login) {
	system("cls");
	if (pCur_cou->cou.count != 0) {
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
		std::wstring str_3;
		wchar_t* file_1 = Create_file_2(pCur_cou->cou.ID, current_semester, ".txt");
		std::wifstream fin_1(file_1);
		fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
		std::getline(fin_1, str_3);
		std::getline(fin_1, str_3);
		fin_1.close();
		Node_stu* pHead_stu = new Node_stu;
		Node_stu* pCur_stu = pHead_stu;
		int begin = 0;
		int end = -1;
		wchar_t* a;
		for (int i = 0; i < pCur_cou->cou.count; i++) {
			pCur_stu->pNext = new Node_stu;
			begin = end + 1;
			end = str_3.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_3.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_stu->pNext->stu.ID = Convert_wchart_to_int(a, end - begin);
			delete[] a;
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
		std::wstring str_4;
		pCur_stu = pHead_stu;
		for (int i = 0; i < pCur_cou->cou.count; i++) {
			wchar_t* file_2 = Convert_int_to_wchart(pCur_stu->stu.ID);
			wchar_t* file_3 = Create_file_2(file_2, Create_second_folder("Student", current_year), ".txt");
			std::wifstream fin_2(file_3);
			fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_2, str_4);
			std::getline(fin_2, str_4);
			Read_file_stu(str_4, pCur_stu);
			fin_2.close();
			pCur_stu = pCur_stu->pNext;
		}
		system("cls");
		SetColor(15, 0);
		std::wofstream fout(L"Output.csv");
		fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		fout << wchar_t(0xfeff);
		pCur_stu = pHead_stu;
		for (int i = 0; i < pCur_cou->cou.count; i++) {
			fout << i + 1 << L"," << pCur_stu->stu.ID << L"," << pCur_stu->stu.FirstName << L" " << pCur_stu->stu.LastName << L"," << pCur_stu->stu.Gender << L"," << pCur_stu->stu.Birthday.Day << L"/" << pCur_stu->stu.Birthday.Month << L"/" << pCur_stu->stu.Birthday.Year << L"," << pCur_stu->stu.SocialID << std::endl;
			pCur_stu = pCur_stu->pNext;
		}
		fout.close();
		std::wcout << "Export success" << std::endl;
		delete[] current_year;
		delete[] current_semester;
		Delete_Node_stu(pHead_stu);
	}
	else {
		system("cls");
		std::wcout << "No students registered this course" << std::endl;
	}
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_view_cou_staff(pCur_cou, file_login);
	}
}

void Menu_view_cou_staff(Node_cou* pCur_cou, wchar_t* file_login) {
	int Max_List_Menu = 4;
	int flag = 0;
	int pointer = 0;
	SetColor(15, 0);
	std::wstring menu[] = { L"Information Course",L"View List Of Student Course",L"Export to csv", L"Exit" };
	while (1) {
		//xoa man hinh
		ShowCur(0);
		system("cls");
		GotoXY(54, 18);
		SetColor(15, 0);
		std::wcout << pCur_cou->cou.ID << L"." << pCur_cou->cou.Name;
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
						Print_inf_cou_console(pCur_cou,file_login);
						Sleep(100000);
						break;
					case 1:
						View_list_of_student_course(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 2:
						Export_list_of_student_course(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 3:
						View_list_of_course(file_login);
						Sleep(100000);
						break;
					}
					break;
				}
				if (key == 27) {
					View_list_of_course(file_login);
					break;
				}
			}
		}
		Sleep(100);
	}
}

void Choose_cou_regis_time(wchar_t* file_login) {
	system("cls");
	Node_cla* pHead_cla;
	std::wstring str_1;
	std::wifstream fin(L"Default_time.txt");
	fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin, str_1);
	std::getline(fin, str_1);
	fin.close();
	char* current_semester = new char[str_1.length() + 1];
	for (int i = 0; i < str_1.length(); i++) {
		current_semester[i] = str_1[i];
	}
	current_semester[str_1.length()] = L'\0';
	if (checkFileWithFstream_wstring(Create_file_4("Time", current_semester, ".txt"))) {
		system("cls");
		std::wcout << "The default time had been choosed. You want to do it again ?" << std::endl;
		std::wcout << "Y to continue or N to exit" << std::endl;
		char key = _getch();
		if (key == 'N' || key == 'n' || key == 27)
		{
			Sub_menu_cou_staff(file_login);
		}
		else if (key == 'Y' || key == 'y') {
			_wremove(Create_file_4("Time", current_semester, ".txt"));
			Node_time_semester* pHead_time = new Node_time_semester;
			Node_time_semester* pCur_time = pHead_time;
			Time current_time;
			Get_current_time_to_int(current_time);
			int* year = new int[11];
			int* month = new int[12];
			int* day_1 = new int[31];
			int* day_2 = new int[30];
			int* day_3 = new int[29];
			int* day_4 = new int[28];
			for (int i = 0; i < 11; i++) {
				year[i] = current_time.date.Year - 5 + i;
			}
			for (int i = 0; i < 12; i++) {
				month[i] = i + 1;
			}
			for (int i = 0; i < 31; i++) {
				day_1[i] = i + 1;
			}
			for (int i = 0; i < 30; i++) {
				day_2[i] = i + 1;
			}
			for (int i = 0; i < 29; i++) {
				day_3[i] = i + 1;
			}
			for (int i = 0; i < 28; i++) {
				day_4[i] = i + 1;
			}
			std::wcout << "Start date:" << std::endl;
			std::wcout << "Year: ";
			int pointer_1 = 5;
			int Max_List_Menu = 11;
			while (1) {
				//in menu ra man hinh
				GotoXY(7, 1);
				ShowCur(0);
				std::wcout << year[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->start.Year = year[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
			GotoXY(13, 1);
			std::wcout << "Month: ";
			pointer_1 = 0;
			Max_List_Menu = 12;
			while (1) {
				//in menu ra man hinh
				GotoXY(22, 1);
				ShowCur(0);
				if (month[pointer_1] < 10) {
					std::wcout << 0;
				}
				std::wcout << month[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->start.Month = month[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
			GotoXY(26, 1);
			std::wcout << "Day: ";
			if (pCur_time->start.Month == 1 || pCur_time->start.Month == 3 || pCur_time->start.Month == 5 || pCur_time->start.Month == 7 || pCur_time->start.Month == 8 || pCur_time->start.Month == 10 || pCur_time->start.Month == 12) {
				pointer_1 = 0;
				Max_List_Menu = 31;
				while (1) {
					//in menu ra man hinh
					GotoXY(33, 1);
					ShowCur(0);
					if (day_1[pointer_1] < 10) {
						std::wcout << 0;
					}
					std::wcout << day_1[pointer_1] << std::endl;
					char key;
					while (1) {
						if (_kbhit()) {
							key = _getch();
							if (key == 72 || key == 'w' || key == 'W') {
								if (pointer_1 < Max_List_Menu - 1) {
									pointer_1++;
								}
								else {
									pointer_1 = 0;
								}
								break;
							}
							if (key == 80 || key == 's' || key == 'S') {
								if (pointer_1 > 0) {
									pointer_1--;
								}
								else {
									pointer_1 = Max_List_Menu - 1;
								}
								break;
							}
							if (key == 13) {
								pCur_time->start.Day = day_1[pointer_1];
								break;
							}
						}
					}
					if (key == 13) {
						break;
					}
				}
			}
			else if (pCur_time->start.Month != 2) {
				pointer_1 = 0;
				Max_List_Menu = 30;
				while (1) {
					//in menu ra man hinh
					GotoXY(33, 1);
					ShowCur(0);
					if (day_2[pointer_1] < 10) {
						std::wcout << 0;
					}
					std::wcout << day_2[pointer_1] << std::endl;
					char key;
					while (1) {
						if (_kbhit()) {
							key = _getch();
							if (key == 72 || key == 'w' || key == 'W') {
								if (pointer_1 < Max_List_Menu - 1) {
									pointer_1++;
								}
								else {
									pointer_1 = 0;
								}
								break;
							}
							if (key == 80 || key == 's' || key == 'S') {
								if (pointer_1 > 0) {
									pointer_1--;
								}
								else {
									pointer_1 = Max_List_Menu - 1;
								}
								break;
							}
							if (key == 13) {
								pCur_time->start.Day = day_2[pointer_1];
								break;
							}
						}
					}
					if (key == 13) {
						break;
					}
				}
			}
			else if (checkYear(pCur_time->start.Year)) {
				pointer_1 = 0;
				Max_List_Menu = 29;
				while (1) {
					//in menu ra man hinh
					GotoXY(33, 1);
					ShowCur(0);
					if (day_3[pointer_1] < 10) {
						std::wcout << 0;
					}
					std::wcout << day_3[pointer_1] << std::endl;
					char key;
					while (1) {
						if (_kbhit()) {
							key = _getch();
							if (key == 72 || key == 'w' || key == 'W') {
								if (pointer_1 < Max_List_Menu - 1) {
									pointer_1++;
								}
								else {
									pointer_1 = 0;
								}
								break;
							}
							if (key == 80 || key == 's' || key == 'S') {
								if (pointer_1 > 0) {
									pointer_1--;
								}
								else {
									pointer_1 = Max_List_Menu - 1;
								}
								break;
							}
							if (key == 13) {
								pCur_time->start.Day = day_3[pointer_1];
								break;
							}
						}
					}
					if (key == 13) {
						break;
					}
				}
			}
			else {
				pointer_1 = 0;
				Max_List_Menu = 28;
				while (1) {
					//in menu ra man hinh
					GotoXY(33, 1);
					ShowCur(0);
					if (day_4[pointer_1] < 10) {
						std::wcout << 0;
					}
					std::wcout << day_4[pointer_1] << std::endl;
					char key;
					while (1) {
						if (_kbhit()) {
							key = _getch();
							if (key == 72 || key == 'w' || key == 'W') {
								if (pointer_1 < Max_List_Menu - 1) {
									pointer_1++;
								}
								else {
									pointer_1 = 0;
								}
								break;
							}
							if (key == 80 || key == 's' || key == 'S') {
								if (pointer_1 > 0) {
									pointer_1--;
								}
								else {
									pointer_1 = Max_List_Menu - 1;
								}
								break;
							}
							if (key == 13) {
								pCur_time->start.Day = day_4[pointer_1];
								break;
							}
						}
					}
					if (key == 13) {
						break;
					}
				}
			}

			GotoXY(0, 2);
			std::wcout << "End date:" << std::endl;
			std::wcout << "Year: ";
			pointer_1 = 5;
			Max_List_Menu = 11;
			while (1) {
				//in menu ra man hinh
				GotoXY(7, 3);
				ShowCur(0);
				std::wcout << year[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->end.Year = year[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
			GotoXY(13, 3);
			std::wcout << "Month: ";
			pointer_1 = 0;
			Max_List_Menu = 12;
			while (1) {
				//in menu ra man hinh
				GotoXY(22, 3);
				ShowCur(0);
				if (month[pointer_1] < 10) {
					std::wcout << 0;
				}
				std::wcout << month[pointer_1] << std::endl;
				char key;
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == 72 || key == 'w' || key == 'W') {
							if (pointer_1 < Max_List_Menu - 1) {
								pointer_1++;
							}
							else {
								pointer_1 = 0;
							}
							break;
						}
						if (key == 80 || key == 's' || key == 'S') {
							if (pointer_1 > 0) {
								pointer_1--;
							}
							else {
								pointer_1 = Max_List_Menu - 1;
							}
							break;
						}
						if (key == 13) {
							pCur_time->end.Month = month[pointer_1];
							break;
						}
					}
				}
				if (key == 13) {
					break;
				}
			}
			GotoXY(26, 3);
			std::wcout << "Day: ";
			if (pCur_time->end.Month == 1 || pCur_time->end.Month == 3 || pCur_time->end.Month == 5 || pCur_time->end.Month == 7 || pCur_time->end.Month == 8 || pCur_time->end.Month == 10 || pCur_time->end.Month == 12) {
				pointer_1 = 0;
				Max_List_Menu = 31;
				while (1) {
					//in menu ra man hinh
					GotoXY(33, 3);
					ShowCur(0);
					if (day_1[pointer_1] < 10) {
						std::wcout << 0;
					}
					std::wcout << day_1[pointer_1] << std::endl;
					char key;
					while (1) {
						if (_kbhit()) {
							key = _getch();
							if (key == 72 || key == 'w' || key == 'W') {
								if (pointer_1 < Max_List_Menu - 1) {
									pointer_1++;
								}
								else {
									pointer_1 = 0;
								}
								break;
							}
							if (key == 80 || key == 's' || key == 'S') {
								if (pointer_1 > 0) {
									pointer_1--;
								}
								else {
									pointer_1 = Max_List_Menu - 1;
								}
								break;
							}
							if (key == 13) {
								pCur_time->end.Day = day_1[pointer_1];
								break;
							}
						}
					}
					if (key == 13) {
						break;
					}
				}
			}
			else if (pCur_time->end.Month != 2) {
				pointer_1 = 0;
				Max_List_Menu = 30;
				while (1) {
					//in menu ra man hinh
					GotoXY(33, 3);
					ShowCur(0);
					if (day_2[pointer_1] < 10) {
						std::wcout << 0;
					}
					std::wcout << day_2[pointer_1] << std::endl;
					char key;
					while (1) {
						if (_kbhit()) {
							key = _getch();
							if (key == 72 || key == 'w' || key == 'W') {
								if (pointer_1 < Max_List_Menu - 1) {
									pointer_1++;
								}
								else {
									pointer_1 = 0;
								}
								break;
							}
							if (key == 80 || key == 's' || key == 'S') {
								if (pointer_1 > 0) {
									pointer_1--;
								}
								else {
									pointer_1 = Max_List_Menu - 1;
								}
								break;
							}
							if (key == 13) {
								pCur_time->end.Day = day_2[pointer_1];
								break;
							}
						}
					}
					if (key == 13) {
						break;
					}
				}
			}
			else if (checkYear(pCur_time->end.Year)) {
				pointer_1 = 0;
				Max_List_Menu = 29;
				while (1) {
					//in menu ra man hinh
					GotoXY(33, 3);
					ShowCur(0);
					if (day_3[pointer_1] < 10) {
						std::wcout << 0;
					}
					std::wcout << day_3[pointer_1] << std::endl;
					char key;
					while (1) {
						if (_kbhit()) {
							key = _getch();
							if (key == 72 || key == 'w' || key == 'W') {
								if (pointer_1 < Max_List_Menu - 1) {
									pointer_1++;
								}
								else {
									pointer_1 = 0;
								}
								break;
							}
							if (key == 80 || key == 's' || key == 'S') {
								if (pointer_1 > 0) {
									pointer_1--;
								}
								else {
									pointer_1 = Max_List_Menu - 1;
								}
								break;
							}
							if (key == 13) {
								pCur_time->end.Day = day_3[pointer_1];
								break;
							}
						}
					}
					if (key == 13) {
						break;
					}
				}
			}
			else {
				pointer_1 = 0;
				Max_List_Menu = 28;
				while (1) {
					//in menu ra man hinh
					GotoXY(33, 3);
					ShowCur(0);
					if (day_4[pointer_1] < 10) {
						std::wcout << 0;
					}
					std::wcout << day_4[pointer_1] << std::endl;
					char key;
					while (1) {
						if (_kbhit()) {
							key = _getch();
							if (key == 72 || key == 'w' || key == 'W') {
								if (pointer_1 < Max_List_Menu - 1) {
									pointer_1++;
								}
								else {
									pointer_1 = 0;
								}
								break;
							}
							if (key == 80 || key == 's' || key == 'S') {
								if (pointer_1 > 0) {
									pointer_1--;
								}
								else {
									pointer_1 = Max_List_Menu - 1;
								}
								break;
							}
							if (key == 13) {
								pCur_time->end.Day = day_4[pointer_1];
								break;
							}
						}
					}
					if (key == 13) {
						break;
					}
				}
			}

			delete[] year;
			delete[] month;
			delete[] day_1;
			delete[] day_2;
			delete[] day_3;
			delete[] day_4;

			std::wofstream fout(Create_file_4("Time", current_semester, ".txt"));
			fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
			fout << pCur_time->start.Day << L"," << pCur_time->start.Month << L"," << pCur_time->start.Year << L"," << pCur_time->end.Day << L"," << pCur_time->end.Month << L"," << pCur_time->end.Year << std::endl;
			fout.close();
			std::wcout << "Choose success" << std::endl;
			pCur_time->pNext = nullptr;
			Delete_Node_time_semester(pHead_time);
		}
	}
	else {
	Node_time_semester* pHead_time = new Node_time_semester;
	Node_time_semester* pCur_time = pHead_time;
	Time current_time;
	Get_current_time_to_int(current_time);
	int* year = new int[11];
	int* month = new int[12];
	int* day_1 = new int[31];
	int* day_2 = new int[30];
	int* day_3 = new int[29];
	int* day_4 = new int[28];
	for (int i = 0; i < 11; i++) {
		year[i] = current_time.date.Year - 5 + i;
	}
	for (int i = 0; i < 12; i++) {
		month[i] = i + 1;
	}
	for (int i = 0; i < 31; i++) {
		day_1[i] = i + 1;
	}
	for (int i = 0; i < 30; i++) {
		day_2[i] = i + 1;
	}
	for (int i = 0; i < 29; i++) {
		day_3[i] = i + 1;
	}
	for (int i = 0; i < 28; i++) {
		day_4[i] = i + 1;
	}
	std::wcout << "Start date:" << std::endl;
	std::wcout << "Year: ";
	int pointer_1 = 5;
	int Max_List_Menu = 11;
	while (1) {
		//in menu ra man hinh
		GotoXY(7, 1);
		ShowCur(0);
		std::wcout << year[pointer_1] << std::endl;
		char key;
		while (1) {
			if (_kbhit()) {
				key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer_1 < Max_List_Menu - 1) {
						pointer_1++;
					}
					else {
						pointer_1 = 0;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer_1 > 0) {
						pointer_1--;
					}
					else {
						pointer_1 = Max_List_Menu - 1;
					}
					break;
				}
				if (key == 13) {
					pCur_time->start.Year = year[pointer_1];
					break;
				}
			}
		}
		if (key == 13) {
			break;
		}
	}
	GotoXY(13, 1);
	std::wcout << "Month: ";
	pointer_1 = 0;
	Max_List_Menu = 12;
	while (1) {
		//in menu ra man hinh
		GotoXY(22, 1);
		ShowCur(0);
		if (month[pointer_1] < 10) {
			std::wcout << 0;
		}
		std::wcout << month[pointer_1] << std::endl;
		char key;
		while (1) {
			if (_kbhit()) {
				key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer_1 < Max_List_Menu - 1) {
						pointer_1++;
					}
					else {
						pointer_1 = 0;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer_1 > 0) {
						pointer_1--;
					}
					else {
						pointer_1 = Max_List_Menu - 1;
					}
					break;
				}
				if (key == 13) {
					pCur_time->start.Month = month[pointer_1];
					break;
				}
			}
		}
		if (key == 13) {
			break;
		}
	}
	GotoXY(26, 1);
	std::wcout << "Day: ";
	if (pCur_time->start.Month == 1 || pCur_time->start.Month == 3 || pCur_time->start.Month == 5 || pCur_time->start.Month == 7 || pCur_time->start.Month == 8 || pCur_time->start.Month == 10 || pCur_time->start.Month == 12) {
		pointer_1 = 0;
		Max_List_Menu = 31;
		while (1) {
			//in menu ra man hinh
			GotoXY(33, 1);
			ShowCur(0);
			if (day_1[pointer_1] < 10) {
				std::wcout << 0;
			}
			std::wcout << day_1[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->start.Day = day_1[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
	}
	else if (pCur_time->start.Month != 2) {
		pointer_1 = 0;
		Max_List_Menu = 30;
		while (1) {
			//in menu ra man hinh
			GotoXY(33, 1);
			ShowCur(0);
			if (day_2[pointer_1] < 10) {
				std::wcout << 0;
			}
			std::wcout << day_2[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->start.Day = day_2[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
	}
	else if (checkYear(pCur_time->start.Year)) {
		pointer_1 = 0;
		Max_List_Menu = 29;
		while (1) {
			//in menu ra man hinh
			GotoXY(33, 1);
			ShowCur(0);
			if (day_3[pointer_1] < 10) {
				std::wcout << 0;
			}
			std::wcout << day_3[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->start.Day = day_3[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
	}
	else {
		pointer_1 = 0;
		Max_List_Menu = 28;
		while (1) {
			//in menu ra man hinh
			GotoXY(33, 1);
			ShowCur(0);
			if (day_4[pointer_1] < 10) {
				std::wcout << 0;
			}
			std::wcout << day_4[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->start.Day = day_4[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
	}

	GotoXY(0, 2);
	std::wcout << "End date:" << std::endl;
	std::wcout << "Year: ";
	pointer_1 = 5;
	Max_List_Menu = 11;
	while (1) {
		//in menu ra man hinh
		GotoXY(7, 3);
		ShowCur(0);
		std::wcout << year[pointer_1] << std::endl;
		char key;
		while (1) {
			if (_kbhit()) {
				key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer_1 < Max_List_Menu - 1) {
						pointer_1++;
					}
					else {
						pointer_1 = 0;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer_1 > 0) {
						pointer_1--;
					}
					else {
						pointer_1 = Max_List_Menu - 1;
					}
					break;
				}
				if (key == 13) {
					pCur_time->end.Year = year[pointer_1];
					break;
				}
			}
		}
		if (key == 13) {
			break;
		}
	}
	GotoXY(13, 3);
	std::wcout << "Month: ";
	pointer_1 = 0;
	Max_List_Menu = 12;
	while (1) {
		//in menu ra man hinh
		GotoXY(22, 3);
		ShowCur(0);
		if (month[pointer_1] < 10) {
			std::wcout << 0;
		}
		std::wcout << month[pointer_1] << std::endl;
		char key;
		while (1) {
			if (_kbhit()) {
				key = _getch();
				if (key == 72 || key == 'w' || key == 'W') {
					if (pointer_1 < Max_List_Menu - 1) {
						pointer_1++;
					}
					else {
						pointer_1 = 0;
					}
					break;
				}
				if (key == 80 || key == 's' || key == 'S') {
					if (pointer_1 > 0) {
						pointer_1--;
					}
					else {
						pointer_1 = Max_List_Menu - 1;
					}
					break;
				}
				if (key == 13) {
					pCur_time->end.Month = month[pointer_1];
					break;
				}
			}
		}
		if (key == 13) {
			break;
		}
	}
	GotoXY(26, 3);
	std::wcout << "Day: ";
	if (pCur_time->end.Month == 1 || pCur_time->end.Month == 3 || pCur_time->end.Month == 5 || pCur_time->end.Month == 7 || pCur_time->end.Month == 8 || pCur_time->end.Month == 10 || pCur_time->end.Month == 12) {
		pointer_1 = 0;
		Max_List_Menu = 31;
		while (1) {
			//in menu ra man hinh
			GotoXY(33, 3);
			ShowCur(0);
			if (day_1[pointer_1] < 10) {
				std::wcout << 0;
			}
			std::wcout << day_1[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->end.Day = day_1[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
	}
	else if (pCur_time->end.Month != 2) {
		pointer_1 = 0;
		Max_List_Menu = 30;
		while (1) {
			//in menu ra man hinh
			GotoXY(33, 3);
			ShowCur(0);
			if (day_2[pointer_1] < 10) {
				std::wcout << 0;
			}
			std::wcout << day_2[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->end.Day = day_2[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
	}
	else if (checkYear(pCur_time->end.Year)) {
		pointer_1 = 0;
		Max_List_Menu = 29;
		while (1) {
			//in menu ra man hinh
			GotoXY(33, 3);
			ShowCur(0);
			if (day_3[pointer_1] < 10) {
				std::wcout << 0;
			}
			std::wcout << day_3[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->end.Day = day_3[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
	}
	else {
		pointer_1 = 0;
		Max_List_Menu = 28;
		while (1) {
			//in menu ra man hinh
			GotoXY(33, 3);
			ShowCur(0);
			if (day_4[pointer_1] < 10) {
				std::wcout << 0;
			}
			std::wcout << day_4[pointer_1] << std::endl;
			char key;
			while (1) {
				if (_kbhit()) {
					key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer_1 < Max_List_Menu - 1) {
							pointer_1++;
						}
						else {
							pointer_1 = 0;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer_1 > 0) {
							pointer_1--;
						}
						else {
							pointer_1 = Max_List_Menu - 1;
						}
						break;
					}
					if (key == 13) {
						pCur_time->end.Day = day_4[pointer_1];
						break;
					}
				}
			}
			if (key == 13) {
				break;
			}
		}
	}

	delete[] year;
	delete[] month;
	delete[] day_1;
	delete[] day_2;
	delete[] day_3;
	delete[] day_4;

	std::wofstream fout(Create_file_4("Time", current_semester, ".txt"));
	fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	fout << pCur_time->start.Day << L"," << pCur_time->start.Month << L"," << pCur_time->start.Year << L"," << pCur_time->end.Day << L"," << pCur_time->end.Month << L"," << pCur_time->end.Year << std::endl;
	fout.close();
	std::wcout << "Choose success" << std::endl;
	pCur_time->pNext = nullptr;
	Delete_Node_time_semester(pHead_time);
	delete[] current_semester;
	}
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_cou_staff(file_login);
	}
}

void Update_course(wchar_t* file_login) {
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
	if (checkFileWithFstream_wstring(Create_file_4("Course", current_semester, ".txt"))) {
		std::wstring str_3;
		Node_cou* pHead_cou = new Node_cou;
		Node_cou* pCur_cou = pHead_cou;
		int x = 0;
		std::wifstream fin_1(Create_file_4("Course", current_semester, ".txt"));
		fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin_1.eof()) {
			pCur_cou->pNext = new Node_cou;
			std::getline(fin_1, str_3);
			pCur_cou->pNext->cou.ID = new wchar_t[str_3.length() + 1];
			str_3.copy(pCur_cou->pNext->cou.ID, str_3.length(), 0);
			pCur_cou->pNext->cou.ID[str_3.length()] = L'\0';
			pCur_cou = pCur_cou->pNext;
			pCur_cou->pNext = nullptr;
			x++;
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
		fin_1.close();
		x--;
		pCur_cou = pHead_cou;
		for (int i = 0; i < x; i++) {
			wchar_t* file_1 = Create_file_2(pCur_cou->cou.ID, current_semester, ".txt");
			std::wifstream fin_2(file_1);
			fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_2, str_1);
			Read_file_cou(str_1, pCur_cou);
			std::getline(fin_2, str_1);
			pCur_cou->cou.StudentID = new wchar_t[str_1.length() + 1];
			str_1.copy(pCur_cou->cou.StudentID, str_1.length(), 0);
			pCur_cou->cou.StudentID[str_1.length()] = L'\0';
			fin_2.close();
			pCur_cou = pCur_cou->pNext;
		}
		int pointer = 0;
		int check = 0;
		while (1) {
			ShowCur(0);
			system("cls");
			pCur_cou = pHead_cou;
			int count = 0;
			while (pCur_cou->pNext != nullptr) {
				if (count == pointer) {
					SetColor(15, 4);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cou->cou.ID << "." << pCur_cou->cou.Name;
				}
				else {
					SetColor(15, 3);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cou->cou.ID << "." << pCur_cou->cou.Name;
				}
				count++;
				pCur_cou = pCur_cou->pNext;
			}
			while (1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer > 0) {
							pointer--;
						}
						else {
							pointer = x - 1;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer < x - 1) {
							pointer++;
						}
						else {
							pointer = 0;
						}
						break;
					}
					if (key == 13) {
						pCur_cou = pHead_cou;
						if (pointer == -1) {

						}
						else {
							for (int i = 0; i < pointer; i++) {
								pCur_cou = pCur_cou->pNext;
							}
							check = 1;
							break;
						}
					}
					if (key == 27) {
						Sub_menu_cou_staff(file_login);
					}
				}
			}
			if (check == 1) {
				break;
			}
		}
		Menu_update_course(pCur_cou, file_login);
		Delete_Node_cou(pHead_cou);
	}
	else {
		system("cls");
		std::wcout << "No course had been created" << std::endl;
	}
	delete[] current_year;
	delete[] current_semester;
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_cou_staff(file_login);
	}
}

void Change_name_course(Node_cou* pCur_cou, wchar_t* file_login) {
	system("cls");
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
	std::wstring str;
	std::wcout << "Input the new name course: ";
	std::getline(std::wcin, str);
	delete pCur_cou->cou.Name;
	pCur_cou->cou.Name = new wchar_t[str.length() + 1];
	str.copy(pCur_cou->cou.Name, str.length(), 0);
	pCur_cou->cou.Name[str.length()] = L'\0';
	_wremove(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	std::wofstream fout(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	fout << pCur_cou->cou.ID << L',' << pCur_cou->cou.Name << L',' << pCur_cou->cou.Teacher_Name << L',' << pCur_cou->cou.Credit << L',' << pCur_cou->cou.max_stu << L',' << pCur_cou->cou.count << L',';
	fout << pCur_cou->cou.ses_1.day_of_week << L',' << pCur_cou->cou.ses_1.session << L',' << pCur_cou->cou.ses_2.day_of_week << L',' << pCur_cou->cou.ses_2.session << std::endl;
	fout << pCur_cou->cou.StudentID << std::endl;
	fout.close();
	std::wcout << "Change success" << std::endl;
	delete[] current_year;
	delete[] current_semester;
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_update_course(pCur_cou, file_login);
	}
}

void Change_teacher_name_course(Node_cou* pCur_cou, wchar_t* file_login) {
	system("cls");
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
	std::wstring str;
	std::wcout << "Input the new teacher name: ";
	std::getline(std::wcin, str);
	delete pCur_cou->cou.Teacher_Name;
	pCur_cou->cou.Teacher_Name = new wchar_t[str.length() + 1];
	str.copy(pCur_cou->cou.Teacher_Name, str.length(), 0);
	pCur_cou->cou.Teacher_Name[str.length()] = L'\0';
	_wremove(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	std::wofstream fout(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	fout << pCur_cou->cou.ID << L',' << pCur_cou->cou.Name << L',' << pCur_cou->cou.Teacher_Name << L',' << pCur_cou->cou.Credit << L',' << pCur_cou->cou.max_stu << L',' << pCur_cou->cou.count << L',';
	fout << pCur_cou->cou.ses_1.day_of_week << L',' << pCur_cou->cou.ses_1.session << L',' << pCur_cou->cou.ses_2.day_of_week << L',' << pCur_cou->cou.ses_2.session << std::endl;
	fout << pCur_cou->cou.StudentID << std::endl;
	fout.close();
	std::wcout << "Change success" << std::endl;
	delete[] current_year;
	delete[] current_semester;
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_update_course(pCur_cou, file_login);
	}
}

void Change_number_of_credit(Node_cou* pCur_cou, wchar_t* file_login) {
	system("cls");
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
	std::wstring str;
	std::wcout << "Input the new number of credits: ";
	std::wcin >> pCur_cou->cou.Credit;
	_wremove(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	std::wofstream fout(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	fout << pCur_cou->cou.ID << L',' << pCur_cou->cou.Name << L',' << pCur_cou->cou.Teacher_Name << L',' << pCur_cou->cou.Credit << L',' << pCur_cou->cou.max_stu << L',' << pCur_cou->cou.count << L',';
	fout << pCur_cou->cou.ses_1.day_of_week << L',' << pCur_cou->cou.ses_1.session << L',' << pCur_cou->cou.ses_2.day_of_week << L',' << pCur_cou->cou.ses_2.session << std::endl;
	fout << pCur_cou->cou.StudentID << std::endl;
	fout.close();
	std::wcout << "Change success" << std::endl;
	delete[] current_year;
	delete[] current_semester;
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_update_course(pCur_cou, file_login);
	}
}

void Change_max_student_course(Node_cou* pCur_cou, wchar_t* file_login) {
	system("cls");
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
	std::wstring str;
	std::wcout << "Input the new number of max students: ";
	std::wcin >> pCur_cou->cou.max_stu;
	_wremove(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	std::wofstream fout(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	fout << pCur_cou->cou.ID << L',' << pCur_cou->cou.Name << L',' << pCur_cou->cou.Teacher_Name << L',' << pCur_cou->cou.Credit << L',' << pCur_cou->cou.max_stu << L',' << pCur_cou->cou.count << L',';
	fout << pCur_cou->cou.ses_1.day_of_week << L',' << pCur_cou->cou.ses_1.session << L',' << pCur_cou->cou.ses_2.day_of_week << L',' << pCur_cou->cou.ses_2.session << std::endl;
	fout << pCur_cou->cou.StudentID << std::endl;
	fout.close();
	std::wcout << "Change success" << std::endl;
	delete[] current_year;
	delete[] current_semester;
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_update_course(pCur_cou, file_login);
	}
}

void Change_session_1(Node_cou* pCur_cou, wchar_t* file_login) {
	system("cls");
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
	std::wcout << "Session 1:";
	ShowCur(0);
	std::wstring menu_1[] = { L"MON",L"TUE",L"WED",L"THU",L"FRI", L"SAT" };
	int pointer = 0;
	int color = 0;
	int Max_List_Menu = 6;
	while (1) {
		//in menu ra man hinh
		GotoXY(11, 0);
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
						pCur_cou->cou.ses_1.day_of_week = 0;
						break;
					case 1:
						pCur_cou->cou.ses_1.day_of_week = 1;
						break;
					case 2:
						pCur_cou->cou.ses_1.day_of_week = 2;
						break;
					case 3:
						pCur_cou->cou.ses_1.day_of_week = 3;
						break;
					case 4:
						pCur_cou->cou.ses_1.day_of_week = 4;
						break;
					case 5:
						pCur_cou->cou.ses_1.day_of_week = 5;
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
	GotoXY(17, 0);
	std::wcout << "Time:";
	std::wstring menu_2[] = { L"S1 (07:30)",L"S2 (09:30)",L"S3 (13:30)",L"S4 (15:30)" };
	pointer = 0;
	Max_List_Menu = 4;
	while (1) {
		//in menu ra man hinh
		GotoXY(23, 0);
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
						pCur_cou->cou.ses_1.session = 0;
						break;
					case 1:
						pCur_cou->cou.ses_1.session = 1;
						break;
					case 2:
						pCur_cou->cou.ses_1.session = 2;
						break;
					case 3:
						pCur_cou->cou.ses_1.session = 3;
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
	_wremove(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	std::wofstream fout(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	fout << pCur_cou->cou.ID << L',' << pCur_cou->cou.Name << L',' << pCur_cou->cou.Teacher_Name << L',' << pCur_cou->cou.Credit << L',' << pCur_cou->cou.max_stu << L',' << pCur_cou->cou.count << L',';
	fout << pCur_cou->cou.ses_1.day_of_week << L',' << pCur_cou->cou.ses_1.session << L',' << pCur_cou->cou.ses_2.day_of_week << L',' << pCur_cou->cou.ses_2.session << std::endl;
	fout << pCur_cou->cou.StudentID << std::endl;
	fout.close();
	std::wcout << "Change success" << std::endl;
	delete[] current_year;
	delete[] current_semester;
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_update_course(pCur_cou, file_login);
	}
}

void Change_session_2(Node_cou* pCur_cou, wchar_t* file_login) {
	system("cls");
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
	std::wcout << "Session 2:";
	ShowCur(0);
	std::wstring menu_1[] = { L"MON",L"TUE",L"WED",L"THU",L"FRI", L"SAT" };
	int pointer = 0;
	int color = 0;
	int Max_List_Menu = 6;
	while (1) {
		//in menu ra man hinh
		GotoXY(11, 0);
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
						pCur_cou->cou.ses_2.day_of_week = 0;
						break;
					case 1:
						pCur_cou->cou.ses_2.day_of_week = 1;
						break;
					case 2:
						pCur_cou->cou.ses_2.day_of_week = 2;
						break;
					case 3:
						pCur_cou->cou.ses_2.day_of_week = 3;
						break;
					case 4:
						pCur_cou->cou.ses_2.day_of_week = 4;
						break;
					case 5:
						pCur_cou->cou.ses_2.day_of_week = 5;
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
	GotoXY(17, 0);
	std::wcout << "Time:";
	std::wstring menu_2[] = { L"S1 (07:30)",L"S2 (09:30)",L"S3 (13:30)",L"S4 (15:30)" };
	pointer = 0;
	Max_List_Menu = 4;
	while (1) {
		//in menu ra man hinh
		GotoXY(23, 0);
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
						pCur_cou->cou.ses_2.session = 0;
						break;
					case 1:
						pCur_cou->cou.ses_2.session = 1;
						break;
					case 2:
						pCur_cou->cou.ses_2.session = 2;
						break;
					case 3:
						pCur_cou->cou.ses_2.session = 3;
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
	_wremove(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	std::wofstream fout(Create_file_2(pCur_cou->cou.ID, current_semester, ".txt"));
	fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	fout << pCur_cou->cou.ID << L',' << pCur_cou->cou.Name << L',' << pCur_cou->cou.Teacher_Name << L',' << pCur_cou->cou.Credit << L',' << pCur_cou->cou.max_stu << L',' << pCur_cou->cou.count << L',';
	fout << pCur_cou->cou.ses_1.day_of_week << L',' << pCur_cou->cou.ses_1.session << L',' << pCur_cou->cou.ses_2.day_of_week << L',' << pCur_cou->cou.ses_2.session << std::endl;
	fout << pCur_cou->cou.StudentID << std::endl;
	fout.close();
	std::wcout << "Change success" << std::endl;
	delete[] current_year;
	delete[] current_semester;
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_update_course(pCur_cou, file_login);
	}
}

void Change_timetable(Node_cou* pCur_cou, wchar_t* file_login) {
	int Max_List_Menu = 3;
	int flag = 0;
	int pointer = 0;
	SetColor(15, 0);
	std::wstring menu[] = { L"Session 1",L"Session 2", L"Exit" };
	while (1) {
		//xoa man hinh
		ShowCur(0);
		system("cls");
		GotoXY(54, 18);
		SetColor(15, 0);
		std::wcout << pCur_cou->cou.ID << L"." << pCur_cou->cou.Name;
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
						Change_session_1(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 1:
						Change_session_2(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 3:
						Menu_update_course(pCur_cou,file_login);
						Sleep(100000);
						break;
					}
					break;
				}
				if (key == 27) {
					Menu_update_course(pCur_cou,file_login);
					break;
				}
			}
		}
		Sleep(100);
	}
	system("cls");
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_cou_staff(file_login);
	}
}

void Menu_update_course(Node_cou* pCur_cou, wchar_t* file_login) {
	int Max_List_Menu = 6;
	int flag = 0;
	int pointer = 0;
	SetColor(15, 0);
	std::wstring menu[] = { L"Name Course",L"Teacher Name", L"Number of Credits", L"Max student of course", L"Timetable", L"Exit" };
	while (1) {
		//xoa man hinh
		ShowCur(0);
		system("cls");
		GotoXY(54, 18);
		SetColor(15, 0);
		std::wcout << pCur_cou->cou.ID << L"." << pCur_cou->cou.Name;
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
						Change_name_course(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 1:
						Change_teacher_name_course(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 2:
						Change_number_of_credit(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 3:
						Change_max_student_course(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 4:
						Change_timetable(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 5:
						Update_course(file_login);
						Sleep(100000);
						break;
					}
					break;
				}
				if (key == 27) {
					Update_course(file_login);
					break;
				}
			}
		}
		Sleep(100);
	}
}

void Delete_one_course(Node_cou*& pHead_cou, int pointer, wchar_t* file_login) {
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
	
	Node_cou* pDummy = new Node_cou;
	pDummy->pNext = pHead_cou;
	Node_cou* pCur_cou = pDummy;
	for (int i = 0; i < pointer; i++) {
		pCur_cou = pCur_cou->pNext;
	}


	std::wstring str_3;
	wchar_t* file_1 = Create_file_2(pCur_cou->pNext->cou.ID, current_semester, ".txt");
	std::wifstream fin_1(file_1);
	fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin_1, str_3);
	Read_file_cou(str_3, pCur_cou->pNext);
	std::getline(fin_1, str_3);
	pCur_cou->pNext->cou.StudentID = new wchar_t[str_3.length() + 1];
	str_1.copy(pCur_cou->pNext->cou.StudentID, str_3.length(), 0);
	pCur_cou->pNext->cou.StudentID[str_3.length()] = L'\0';
	fin_1.close();

	if (pCur_cou->pNext->cou.count == 0) {
		_wremove(file_1);
		Node_cou* pTemp = pCur_cou->pNext;
		pCur_cou->pNext = pCur_cou->pNext->pNext;
		delete pTemp;
		pHead_cou = pDummy->pNext;
		pCur_cou = pHead_cou;
		delete pDummy;
		_wremove(Create_file_4("Course", current_semester, ".txt"));
		std::wofstream fout(Create_file_4("Course", current_semester, ".txt"));
		fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		while (pCur_cou->pNext != nullptr) {
			fout << pCur_cou->cou.ID << std::endl;
			pCur_cou = pCur_cou->pNext;
		}
		fout.close();
	}
	else {
		Node_stu* pHead_stu = new Node_stu;
		Node_stu* pCur_stu = pHead_stu;
		int begin = 0;
		int end = -1;
		wchar_t* a;
		for (int i = 0; i < pCur_cou->pNext->cou.count; i++) {
			pCur_stu->pNext = new Node_stu;
			begin = end + 1;
			end = str_3.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_3.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_stu->pNext->stu.ID = Convert_wchart_to_int(a, end - begin);
			delete[] a;
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
		pCur_stu = pHead_stu;
		std::wstring str_4;
		for (int i = 0; i < pCur_cou->pNext->cou.count; i++) {
			wchar_t* file_2 = Convert_int_to_wchart(pCur_stu->stu.ID);
			wchar_t* file_3 = Create_file_2(file_2, Create_second_folder("Student", current_year), ".txt");
			std::wifstream fin_2(file_3);
			fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_2, str_4);
			begin = str_4.find(',', 0) + 1;
			end = str_4.length();
			pCur_stu->stu.account.Pass = new wchar_t[end - begin + 1];
			str_4.copy(pCur_stu->stu.account.Pass, end - begin, begin);
			pCur_stu->stu.account.Pass[end - begin] = L'\0';
			std::getline(fin_2, str_4);
			Read_file_stu(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_1(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_2(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_3(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_4(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_5(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			int count = 0;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 6; j++) {
					pCur_stu->stu.Schedule[i][j] = str_4[count] - int('0');
					count++;
				}
			}
			fin_2.close();


			if (wcscmp(pCur_cou->pNext->cou.ID, pCur_stu->stu.course_1.ID) == 0) {
				pCur_stu->stu.course_1.ID = new wchar_t[2];
				pCur_stu->stu.course_1.ID[0] = L'0';
				pCur_stu->stu.course_1.ID[1] = L'\0';
				pCur_stu->stu.course_1.FinalMark = 0;
				pCur_stu->stu.course_1.MidtermMark = 0;
				pCur_stu->stu.course_1.OtherMark = 0;
				pCur_stu->stu.course_1.TotalMark = 0;
				pCur_stu->stu.course_1.GPA = 0;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 6; j++) {
						if (pCur_stu->stu.Schedule[i][j] == 1) {
							pCur_stu->stu.Schedule[i][j] = 0;
						}
					}
				}
			}
			else if (wcscmp(pCur_cou->pNext->cou.ID, pCur_stu->stu.course_2.ID) == 0) {
				pCur_stu->stu.course_2.ID = new wchar_t[2];
				pCur_stu->stu.course_2.ID[0] = L'0';
				pCur_stu->stu.course_2.ID[1] = L'\0';
				pCur_stu->stu.course_2.FinalMark = 0;
				pCur_stu->stu.course_2.MidtermMark = 0;
				pCur_stu->stu.course_2.OtherMark = 0;
				pCur_stu->stu.course_2.TotalMark = 0;
				pCur_stu->stu.course_2.GPA = 0;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 6; j++) {
						if (pCur_stu->stu.Schedule[i][j] == 2) {
							pCur_stu->stu.Schedule[i][j] = 0;
						}
					}
				}
			}
			else if (wcscmp(pCur_cou->pNext->cou.ID, pCur_stu->stu.course_3.ID) == 0) {
				pCur_stu->stu.course_3.ID = new wchar_t[2];
				pCur_stu->stu.course_3.ID[0] = L'0';
				pCur_stu->stu.course_3.ID[1] = L'\0';
				pCur_stu->stu.course_3.FinalMark = 0;
				pCur_stu->stu.course_3.MidtermMark = 0;
				pCur_stu->stu.course_3.OtherMark = 0;
				pCur_stu->stu.course_3.TotalMark = 0;
				pCur_stu->stu.course_3.GPA = 0;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 6; j++) {
						if (pCur_stu->stu.Schedule[i][j] == 3) {
							pCur_stu->stu.Schedule[i][j] = 0;
						}
					}
				}
			}
			else if (wcscmp(pCur_cou->pNext->cou.ID, pCur_stu->stu.course_4.ID) == 0) {
				pCur_stu->stu.course_4.ID = new wchar_t[2];
				pCur_stu->stu.course_4.ID[0] = L'0';
				pCur_stu->stu.course_4.ID[1] = L'\0';
				pCur_stu->stu.course_4.FinalMark = 0;
				pCur_stu->stu.course_4.MidtermMark = 0;
				pCur_stu->stu.course_4.OtherMark = 0;
				pCur_stu->stu.course_4.TotalMark = 0;
				pCur_stu->stu.course_4.GPA = 0;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 6; j++) {
						if (pCur_stu->stu.Schedule[i][j] == 4) {
							pCur_stu->stu.Schedule[i][j] = 0;
						}
					}
				}
			}
			else if (wcscmp(pCur_cou->pNext->cou.ID, pCur_stu->stu.course_5.ID) == 0) {
				pCur_stu->stu.course_5.ID = new wchar_t[2];
				pCur_stu->stu.course_5.ID[0] = L'0';
				pCur_stu->stu.course_5.ID[1] = L'\0';
				pCur_stu->stu.course_5.FinalMark = 0;
				pCur_stu->stu.course_5.MidtermMark = 0;
				pCur_stu->stu.course_5.OtherMark = 0;
				pCur_stu->stu.course_5.TotalMark = 0;
				pCur_stu->stu.course_5.GPA = 0;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 6; j++) {
						if (pCur_stu->stu.Schedule[i][j] == 5) {
							pCur_stu->stu.Schedule[i][j] = 0;
						}
					}
				}
			}
			_wremove(file_3);
			std::wofstream fout_1(file_3);
			fout_1.imbue(std::locale(fout_1.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
			fout_1 << pCur_stu->stu.account.ID << L"," << pCur_stu->stu.account.Pass << std::endl;
			fout_1 << pCur_stu->stu.ID << L"," << pCur_stu->stu.FirstName << L"," << pCur_stu->stu.LastName << L"," << pCur_stu->stu.Gender << L"," << pCur_stu->stu.Birthday.Day << L"/" << pCur_stu->stu.Birthday.Month << L"/" << pCur_stu->stu.Birthday.Year << L"," << pCur_stu->stu.SocialID << std::endl;
			fout_1 << pCur_stu->stu.course_1.ID << L"," << pCur_stu->stu.course_1.TotalMark << L"," << pCur_stu->stu.course_1.FinalMark << L"," << pCur_stu->stu.course_1.MidtermMark << L"," << pCur_stu->stu.course_1.OtherMark << L"," << pCur_stu->stu.course_1.GPA << std::endl;
			fout_1 << pCur_stu->stu.course_2.ID << L"," << pCur_stu->stu.course_2.TotalMark << L"," << pCur_stu->stu.course_2.FinalMark << L"," << pCur_stu->stu.course_2.MidtermMark << L"," << pCur_stu->stu.course_2.OtherMark << L"," << pCur_stu->stu.course_2.GPA << std::endl;
			fout_1 << pCur_stu->stu.course_3.ID << L"," << pCur_stu->stu.course_3.TotalMark << L"," << pCur_stu->stu.course_3.FinalMark << L"," << pCur_stu->stu.course_3.MidtermMark << L"," << pCur_stu->stu.course_3.OtherMark << L"," << pCur_stu->stu.course_3.GPA << std::endl;
			fout_1 << pCur_stu->stu.course_4.ID << L"," << pCur_stu->stu.course_4.TotalMark << L"," << pCur_stu->stu.course_4.FinalMark << L"," << pCur_stu->stu.course_4.MidtermMark << L"," << pCur_stu->stu.course_4.OtherMark << L"," << pCur_stu->stu.course_4.GPA << std::endl;
			fout_1 << pCur_stu->stu.course_5.ID << L"," << pCur_stu->stu.course_5.TotalMark << L"," << pCur_stu->stu.course_5.FinalMark << L"," << pCur_stu->stu.course_5.MidtermMark << L"," << pCur_stu->stu.course_5.OtherMark << L"," << pCur_stu->stu.course_5.GPA << std::endl;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 6; j++) {
					fout_1 << pCur_stu->stu.Schedule[i][j];
				}
			}
			fout_1.close();
			pCur_stu = pCur_stu->pNext;
		}
		Delete_Node_stu(pHead_stu);
		_wremove(file_1);
		Node_cou* pTemp = pCur_cou->pNext;
		pCur_cou->pNext = pCur_cou->pNext->pNext;
		delete pTemp;
		pHead_cou = pDummy->pNext;
		delete pDummy;
		_wremove(Create_file_4("Course", current_semester, ".txt"));
		std::wofstream fout(Create_file_4("Course", current_semester, ".txt"));
		fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		pCur_cou = pHead_cou;
		while (pCur_cou->pNext != nullptr) {
			fout << pCur_cou->cou.ID << std::endl;
			pCur_cou = pCur_cou->pNext;
		}
		fout.close();
	}
	std::wstring str_5;
	wchar_t* a = new wchar_t[1];
	a[0] = L'\0';
	std::wifstream fin_4(Create_file_4("Course", current_semester, ".txt"));
	fin_4.imbue(std::locale(fin_4.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin_4, str_5);
	fin_4.close();
	wchar_t* b = new wchar_t[str_5.length() + 1];
	str_5.copy(b, str_5.length(), 0);
	b[str_5.length()] = L'\0';
	if (wcscmp(a, b) == 0) {
		_wremove(Create_file_4("Course", current_semester, ".txt"));
	}
	delete[] current_year;
	delete[] current_semester;
	system("cls");
	std::wcout << "Delete success" << std::endl;
	char key = toupper(_getch());
	if (key == 27)
	{
		Delete_course(file_login);
	}
}

void Delete_course(wchar_t* file_login) {
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
	if (checkFileWithFstream_wstring(Create_file_4("Course", current_semester, ".txt"))) {
		std::wstring str_3;
		Node_cou* pHead_cou = new Node_cou;
		Node_cou* pCur_cou = pHead_cou;
		int x = 0;
		std::wifstream fin_1(Create_file_4("Course", current_semester, ".txt"));
		fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin_1.eof()) {
			pCur_cou->pNext = new Node_cou;
			std::getline(fin_1, str_3);
			pCur_cou->pNext->cou.ID = new wchar_t[str_3.length() + 1];
			str_3.copy(pCur_cou->pNext->cou.ID, str_3.length(), 0);
			pCur_cou->pNext->cou.ID[str_3.length()] = L'\0';
			pCur_cou = pCur_cou->pNext;
			pCur_cou->pNext = nullptr;
			x++;
		}
		if (pHead_cou->pNext == nullptr) {
			delete pHead_cou;
			pHead_cou = nullptr;
			std::wcout << L"No course had been created" << std::endl;
		}
		else {
			Node_cou* pTemp = pHead_cou;
			pHead_cou = pHead_cou->pNext;
			delete pTemp;
		}
		fin_1.close();
		x--;
		pCur_cou = pHead_cou;
		for (int i = 0; i < x; i++) {
			wchar_t* file_1 = Create_file_2(pCur_cou->cou.ID, current_semester, ".txt");
			std::wifstream fin_2(file_1);
			fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_2, str_1);
			Read_file_cou(str_1, pCur_cou);
			std::getline(fin_2, str_1);
			pCur_cou->cou.StudentID = new wchar_t[str_1.length() + 1];
			str_1.copy(pCur_cou->cou.StudentID, str_1.length(), 0);
			pCur_cou->cou.StudentID[str_1.length()] = L'\0';
			fin_2.close();
			pCur_cou = pCur_cou->pNext;
		}
		int pointer = 0;
		int check = 0;
		while (1) {
			ShowCur(0);
			system("cls");
			pCur_cou = pHead_cou;
			int count = 0;
			while (pCur_cou->pNext != nullptr) {
				if (count == pointer) {
					SetColor(15, 4);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cou->cou.ID << "." << pCur_cou->cou.Name;
				}
				else {
					SetColor(15, 3);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cou->cou.ID << "." << pCur_cou->cou.Name;
				}
				count++;
				pCur_cou = pCur_cou->pNext;
			}
			while (1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer > 0) {
							pointer--;
						}
						else {
							pointer = x - 1;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer < x - 1) {
							pointer++;
						}
						else {
							pointer = 0;
						}
						break;
					}
					if (key == 13) {
						if (pointer == -1) {

						}
						else {
							check = 1;
							break;
						}
					}
					if (key == 27) {
						Sub_menu_cou_staff(file_login);
					}
				}
			}
			if (check == 1) {
				break;
			}
		}
		Delete_one_course(pHead_cou, pointer, file_login);
		Delete_Node_cou(pHead_cou);
	}
	else {
		system("cls");
		std::wcout << L"No course had been created" << std::endl;
	}
	delete[] current_year;
	delete[] current_semester;
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_cou_staff(file_login);
	}
}

void View_Score_course(Node_cou* pCur_cou, wchar_t* file_login) {
	system("cls");
	if (pCur_cou->cou.count != 0) {
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
		std::wstring str_3;
		wchar_t* file_1 = Create_file_2(pCur_cou->cou.ID, current_semester, ".txt");
		std::wifstream fin_1(file_1);
		fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
		std::getline(fin_1, str_3);
		std::getline(fin_1, str_3);
		fin_1.close();
		Node_stu* pHead_stu = new Node_stu;
		Node_stu* pCur_stu = pHead_stu;
		int begin = 0;
		int end = -1;
		wchar_t* a;
		for (int i = 0; i < pCur_cou->cou.count; i++) {
			pCur_stu->pNext = new Node_stu;
			begin = end + 1;
			end = str_3.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_3.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_stu->pNext->stu.ID = Convert_wchart_to_int(a, end - begin);
			delete[] a;
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
		std::wstring str_4;
		Score* b = new Score[pCur_cou->cou.count];
		pCur_stu = pHead_stu;
		for (int i = 0; i < pCur_cou->cou.count; i++) {
			wchar_t* file_2 = Convert_int_to_wchart(pCur_stu->stu.ID);
			wchar_t* file_3 = Create_file_2(file_2, Create_second_folder("Student", current_year), ".txt");
			std::wifstream fin_2(file_3);
			fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_2, str_4);
			std::getline(fin_2, str_4);
			Read_file_stu(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_1(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_2(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_3(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_4(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_5(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			fin_2.close();

			if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_1.ID) == 0) {
				b[i].FinalMark = pCur_stu->stu.course_1.FinalMark;
				b[i].MidtermMark = pCur_stu->stu.course_1.MidtermMark;
				b[i].OtherMark = pCur_stu->stu.course_1.OtherMark;
				b[i].TotalMark = pCur_stu->stu.course_1.TotalMark;
				b[i].GPA = pCur_stu->stu.course_1.GPA;
			}
			else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_2.ID) == 0) {
				b[i].FinalMark = pCur_stu->stu.course_2.FinalMark;
				b[i].MidtermMark = pCur_stu->stu.course_2.MidtermMark;
				b[i].OtherMark = pCur_stu->stu.course_2.OtherMark;
				b[i].TotalMark = pCur_stu->stu.course_2.TotalMark;
				b[i].GPA = pCur_stu->stu.course_2.GPA;
			}
			else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_3.ID) == 0) {
				b[i].FinalMark = pCur_stu->stu.course_3.FinalMark;
				b[i].MidtermMark = pCur_stu->stu.course_3.MidtermMark;
				b[i].OtherMark = pCur_stu->stu.course_3.OtherMark;
				b[i].TotalMark = pCur_stu->stu.course_3.TotalMark;
				b[i].GPA = pCur_stu->stu.course_3.GPA;
			}
			else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_4.ID) == 0) {
				b[i].FinalMark = pCur_stu->stu.course_4.FinalMark;
				b[i].MidtermMark = pCur_stu->stu.course_4.MidtermMark;
				b[i].OtherMark = pCur_stu->stu.course_4.OtherMark;
				b[i].TotalMark = pCur_stu->stu.course_4.TotalMark;
				b[i].GPA = pCur_stu->stu.course_4.GPA;
			}
			else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_5.ID) == 0) {
				b[i].FinalMark = pCur_stu->stu.course_5.FinalMark;
				b[i].MidtermMark = pCur_stu->stu.course_5.MidtermMark;
				b[i].OtherMark = pCur_stu->stu.course_5.OtherMark;
				b[i].TotalMark = pCur_stu->stu.course_5.TotalMark;
				b[i].GPA = pCur_stu->stu.course_5.GPA;
			}
			pCur_stu = pCur_stu->pNext;
		}
		system("cls");
		SetColor(15, 0);
		std::wcout << pCur_cou->cou.ID << L"." << pCur_cou->cou.Name << std::endl;
		pCur_stu = pHead_stu;
		for (int i = 0; i < pCur_cou->cou.count; i++) {
			std::wcout << i + 1 << L"," << pCur_stu->stu.ID << L"," << pCur_stu->stu.FirstName << L" " << pCur_stu->stu.LastName << L"," << b[i].FinalMark << L"," << b[i].MidtermMark << L"," << b[i].OtherMark << L"," << b[i].TotalMark << std::endl;
			pCur_stu = pCur_stu->pNext;
		}
		delete[] current_year;
		delete[] current_semester;
		Delete_Node_stu(pHead_stu);
	}
	else {
		system("cls");
		std::wcout << "No students registered this course" << std::endl;
	}
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_course_score(pCur_cou, file_login);
	}
}

void Change_Score_course_1(Node_cou* pCur_cou, wchar_t* file_login) {
	if (pCur_cou->cou.count != 0) {
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
		std::wstring str_3;
		wchar_t* file_1 = Create_file_2(pCur_cou->cou.ID, current_semester, ".txt");
		std::wifstream fin_1(file_1);
		fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
		std::getline(fin_1, str_3);
		std::getline(fin_1, str_3);
		fin_1.close();
		Node_stu* pHead_stu = new Node_stu;
		Node_stu* pCur_stu = pHead_stu;
		int begin = 0;
		int end = -1;
		wchar_t* a;
		for (int i = 0; i < pCur_cou->cou.count; i++) {
			pCur_stu->pNext = new Node_stu;
			begin = end + 1;
			end = str_3.find(',', begin);
			a = new wchar_t[end - begin + 1];
			str_3.copy(a, end - begin, begin);
			a[end - begin] = L'\0';
			pCur_stu->pNext->stu.ID = Convert_wchart_to_int(a, end - begin);
			delete[] a;
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
		std::wstring str_4;
		Score* b = new Score[pCur_cou->cou.count];
		pCur_stu = pHead_stu;
		for (int i = 0; i < pCur_cou->cou.count; i++) {
			wchar_t* file_2 = Convert_int_to_wchart(pCur_stu->stu.ID);
			wchar_t* file_3 = Create_file_2(file_2, Create_second_folder("Student", current_year), ".txt");
			std::wifstream fin_2(file_3);
			fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_2, str_4);
			begin = str_4.find(',', 0) + 1;
			end = str_4.length();
			pCur_stu->stu.account.Pass = new wchar_t[end - begin + 1];
			str_4.copy(pCur_stu->stu.account.Pass, end - begin, begin);
			pCur_stu->stu.account.Pass[end - begin] = L'\0';
			std::getline(fin_2, str_4);
			Read_file_stu(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_1(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_2(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_3(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_4(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			Read_course_5(str_4, pCur_stu);
			std::getline(fin_2, str_4);
			int count = 0;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 6; j++) {
					pCur_stu->stu.Schedule[i][j] = str_4[count] - int('0');
					count++;
				}
			}
			fin_2.close();

			if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_1.ID) == 0) {
				b[i].FinalMark = pCur_stu->stu.course_1.FinalMark;
				b[i].MidtermMark = pCur_stu->stu.course_1.MidtermMark;
				b[i].OtherMark = pCur_stu->stu.course_1.OtherMark;
				b[i].TotalMark = pCur_stu->stu.course_1.TotalMark;
				b[i].GPA = pCur_stu->stu.course_1.GPA;
			}
			else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_2.ID) == 0) {
				b[i].FinalMark = pCur_stu->stu.course_2.FinalMark;
				b[i].MidtermMark = pCur_stu->stu.course_2.MidtermMark;
				b[i].OtherMark = pCur_stu->stu.course_2.OtherMark;
				b[i].TotalMark = pCur_stu->stu.course_2.TotalMark;
				b[i].GPA = pCur_stu->stu.course_2.GPA;
			}
			else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_3.ID) == 0) {
				b[i].FinalMark = pCur_stu->stu.course_3.FinalMark;
				b[i].MidtermMark = pCur_stu->stu.course_3.MidtermMark;
				b[i].OtherMark = pCur_stu->stu.course_3.OtherMark;
				b[i].TotalMark = pCur_stu->stu.course_3.TotalMark;
				b[i].GPA = pCur_stu->stu.course_3.GPA;
			}
			else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_4.ID) == 0) {
				b[i].FinalMark = pCur_stu->stu.course_4.FinalMark;
				b[i].MidtermMark = pCur_stu->stu.course_4.MidtermMark;
				b[i].OtherMark = pCur_stu->stu.course_4.OtherMark;
				b[i].TotalMark = pCur_stu->stu.course_4.TotalMark;
				b[i].GPA = pCur_stu->stu.course_4.GPA;
			}
			else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_5.ID) == 0) {
				b[i].FinalMark = pCur_stu->stu.course_5.FinalMark;
				b[i].MidtermMark = pCur_stu->stu.course_5.MidtermMark;
				b[i].OtherMark = pCur_stu->stu.course_5.OtherMark;
				b[i].TotalMark = pCur_stu->stu.course_5.TotalMark;
				b[i].GPA = pCur_stu->stu.course_5.GPA;
			}
			pCur_stu = pCur_stu->pNext;
		}
		

		int pointer = 0;
		int check = 0;
		while (1) {
			SetColor(15, 0);
			ShowCur(0);
			system("cls");
			pCur_stu = pHead_stu;
			int count = 0;
			for (int i = 0; i < pCur_cou->cou.count; i++) {
				if (count == pointer) {
					SetColor(15, 4);
					GotoXY(0, 0 + count);
					std::wcout << i + 1 << L"," << pCur_stu->stu.ID << L"," << pCur_stu->stu.FirstName << L" " << pCur_stu->stu.LastName << L"," << b[i].FinalMark << L"," << b[i].MidtermMark << L"," << b[i].OtherMark << L"," << b[i].TotalMark << std::endl;
				}
				else {
					SetColor(15, 3);
					GotoXY(0, 0 + count);
					std::wcout << i + 1 << L"," << pCur_stu->stu.ID << L"," << pCur_stu->stu.FirstName << L" " << pCur_stu->stu.LastName << L"," << b[i].FinalMark << L"," << b[i].MidtermMark << L"," << b[i].OtherMark << L"," << b[i].TotalMark << std::endl;
				}
				count++;
				pCur_stu = pCur_stu->pNext;
			}
			while (1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer > 0) {
							pointer--;
						}
						else {
							pointer = pCur_cou->cou.count - 1;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer < pCur_cou->cou.count - 1) {
							pointer++;
						}
						else {
							pointer = 0;
						}
						break;
					}
					if (key == 13) {
						if (pointer == -1) {

						}
						else {
							check = 1;
							pCur_stu = pHead_stu;
							for (int i = 0; i < pointer; i++) {
								pCur_stu = pCur_stu->pNext;
							}
							break;
						}
					}
					if (key == 27) {
						Menu_course_score(pCur_cou, file_login);
					}
				}
			}
			if (check == 1) {
				break;
			}
		}
		system("cls");
		Change_Score_course_2(pCur_cou, pCur_stu, file_login);
		delete[] current_year;
		delete[] current_semester;
		Delete_Node_stu(pHead_stu);
	}
	else {
		system("cls");
		std::wcout << "No students registered this course" << std::endl;
	}
	char key = toupper(_getch());
	if (key == 27)
	{
		Menu_course_score(pCur_cou, file_login);
	}
}

void Change_Score_course_2(Node_cou* pCur_cou, Node_stu* pCur_stu, wchar_t* file_login) {
	system("cls");
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
	Score b;
	std::wcout << "Input new Total score: ";
	std::wcin >> b.TotalMark;
	std::wcout << "Input new Final score: ";
	std::wcin >> b.FinalMark;
	std::wcout << "Input new Midterm score: ";
	std::wcin >> b.MidtermMark;
	std::wcout << "Input new Other score: ";
	std::wcin >> b.OtherMark;
	if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_1.ID) == 0) {
		pCur_stu->stu.course_1.FinalMark = b.TotalMark;
		pCur_stu->stu.course_1.MidtermMark = b.FinalMark;
		pCur_stu->stu.course_1.OtherMark = b.MidtermMark;
		pCur_stu->stu.course_1.TotalMark = b.OtherMark;
	}
	else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_2.ID) == 0) {
		pCur_stu->stu.course_2.FinalMark = b.TotalMark;
		pCur_stu->stu.course_2.MidtermMark = b.FinalMark;
		pCur_stu->stu.course_2.OtherMark = b.MidtermMark;
		pCur_stu->stu.course_2.TotalMark = b.OtherMark;
	}
	else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_3.ID) == 0) {
		pCur_stu->stu.course_3.FinalMark = b.TotalMark;
		pCur_stu->stu.course_3.MidtermMark = b.FinalMark;
		pCur_stu->stu.course_3.OtherMark = b.MidtermMark;
		pCur_stu->stu.course_3.TotalMark = b.OtherMark;
	}
	else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_4.ID) == 0) {
		pCur_stu->stu.course_4.FinalMark = b.TotalMark;
		pCur_stu->stu.course_4.MidtermMark = b.FinalMark;
		pCur_stu->stu.course_4.OtherMark = b.MidtermMark;
		pCur_stu->stu.course_4.TotalMark = b.OtherMark;
	}
	else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_5.ID) == 0) {
		pCur_stu->stu.course_5.FinalMark = b.TotalMark;
		pCur_stu->stu.course_5.MidtermMark = b.FinalMark;
		pCur_stu->stu.course_5.OtherMark = b.MidtermMark;
		pCur_stu->stu.course_5.TotalMark = b.OtherMark;
	}
	wchar_t* file_1 = Convert_int_to_wchart(pCur_stu->stu.ID);
	_wremove(Create_file_2(file_1, Create_second_folder("Student", current_year), ".txt"));
	std::wofstream fout(Create_file_2(file_1, Create_second_folder("Student", current_year), ".txt"));
	fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	fout << pCur_stu->stu.account.ID << L"," << pCur_stu->stu.account.Pass << std::endl;
	fout << pCur_stu->stu.ID << L"," << pCur_stu->stu.FirstName << L"," << pCur_stu->stu.LastName << L"," << pCur_stu->stu.Gender << L"," << pCur_stu->stu.Birthday.Day << L"/" << pCur_stu->stu.Birthday.Month << L"/" << pCur_stu->stu.Birthday.Year << L"," << pCur_stu->stu.SocialID << std::endl;
	fout << pCur_stu->stu.course_1.ID << L"," << pCur_stu->stu.course_1.TotalMark << L"," << pCur_stu->stu.course_1.FinalMark << L"," << pCur_stu->stu.course_1.MidtermMark << L"," << pCur_stu->stu.course_1.OtherMark << L"," << pCur_stu->stu.course_1.GPA << std::endl;
	fout << pCur_stu->stu.course_2.ID << L"," << pCur_stu->stu.course_2.TotalMark << L"," << pCur_stu->stu.course_2.FinalMark << L"," << pCur_stu->stu.course_2.MidtermMark << L"," << pCur_stu->stu.course_2.OtherMark << L"," << pCur_stu->stu.course_2.GPA << std::endl;
	fout << pCur_stu->stu.course_3.ID << L"," << pCur_stu->stu.course_3.TotalMark << L"," << pCur_stu->stu.course_3.FinalMark << L"," << pCur_stu->stu.course_3.MidtermMark << L"," << pCur_stu->stu.course_3.OtherMark << L"," << pCur_stu->stu.course_3.GPA << std::endl;
	fout << pCur_stu->stu.course_4.ID << L"," << pCur_stu->stu.course_4.TotalMark << L"," << pCur_stu->stu.course_4.FinalMark << L"," << pCur_stu->stu.course_4.MidtermMark << L"," << pCur_stu->stu.course_4.OtherMark << L"," << pCur_stu->stu.course_4.GPA << std::endl;
	fout << pCur_stu->stu.course_5.ID << L"," << pCur_stu->stu.course_5.TotalMark << L"," << pCur_stu->stu.course_5.FinalMark << L"," << pCur_stu->stu.course_5.MidtermMark << L"," << pCur_stu->stu.course_5.OtherMark << L"," << pCur_stu->stu.course_5.GPA << std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			fout << pCur_stu->stu.Schedule[i][j];
		}
	}
	fout.close();
	delete[] current_year;
	delete[] file_1;
	system("cls");
	std::wcout << "Change success" << std::endl;
	char key = toupper(_getch());
	if (key == 27)
	{
		Change_Score_course_1(pCur_cou, file_login);
	}
}

void Menu_course_score(Node_cou* pCur_cou, wchar_t* file_login) {
	int Max_List_Menu = 4;
	int flag = 0;
	int pointer = 0;
	SetColor(15, 0);
	std::wstring menu[] = { L"Input Score", L"View Score" ,L"Change Score", L"Exit" };
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
						Input_score(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 1:
						View_Score_course(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 2:
						Change_Score_course_1(pCur_cou, file_login);
						Sleep(100000);
						break;
					case 3:
						View_course_score(file_login);
						break;
					}
					break;
				}
				if (key == 27) {
					View_course_score(file_login);
					break;
				}
			}
		}
		Sleep(100);
	}
}

void View_course_score(wchar_t* file_login) {
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
	if (checkFileWithFstream_wstring(Create_file_4("Course", current_semester, ".txt"))) {
		std::wstring str_3;
		Node_cou* pHead_cou = new Node_cou;
		Node_cou* pCur_cou = pHead_cou;
		int x = 0;
		std::wifstream fin_1(Create_file_4("Course", current_semester, ".txt"));
		fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin_1.eof()) {
			pCur_cou->pNext = new Node_cou;
			std::getline(fin_1, str_3);
			pCur_cou->pNext->cou.ID = new wchar_t[str_3.length() + 1];
			str_3.copy(pCur_cou->pNext->cou.ID, str_3.length(), 0);
			pCur_cou->pNext->cou.ID[str_3.length()] = L'\0';
			pCur_cou = pCur_cou->pNext;
			pCur_cou->pNext = nullptr;
			x++;
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
		fin_1.close();
		x--;
		pCur_cou = pHead_cou;
		for (int i = 0; i < x; i++) {
			wchar_t* file_1 = Create_file_2(pCur_cou->cou.ID, current_semester, ".txt");
			std::wifstream fin_2(file_1);
			fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_2, str_1);
			Read_file_cou(str_1, pCur_cou);
			fin_2.close();
			pCur_cou = pCur_cou->pNext;
		}
		int pointer = 0;
		int check = 0;
		while (1) {
			ShowCur(0);
			system("cls");
			pCur_cou = pHead_cou;
			int count = 0;
			while (pCur_cou->pNext != nullptr) {
				if (count == pointer) {
					SetColor(15, 4);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cou->cou.ID << "." << pCur_cou->cou.Name;
				}
				else {
					SetColor(15, 3);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cou->cou.ID << "." << pCur_cou->cou.Name;
				}
				count++;
				pCur_cou = pCur_cou->pNext;
			}
			while (1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer > 0) {
							pointer--;
						}
						else {
							pointer = x - 1;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer < x - 1) {
							pointer++;
						}
						else {
							pointer = 0;
						}
						break;
					}
					if (key == 13) {
						pCur_cou = pHead_cou;
						if (pointer == -1) {

						}
						else {
							for (int i = 0; i < pointer; i++) {
								pCur_cou = pCur_cou->pNext;
							}
							check = 1;
							break;
						}
					}
					if (key == 27) {
						Sub_menu_cou_staff(file_login);
					}
				}
			}
			if (check == 1) {
				break;
			}
		}
		Menu_course_score(pCur_cou, file_login);
		Delete_Node_cou(pHead_cou);
	}
	else {
		system("cls");
		std::wcout << "No course had been created" << std::endl;
	}
	delete[] current_year;
	delete[] current_semester;
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_cou_staff(file_login);
	}
}

void View_score_of_class_1(wchar_t* file) {
	Node_cla* pHead_cla;
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
	system("cls");
	if (checkFileWithFstream_wstring(Create_file_4("Class", Create_second_folder("Class", current_year), ".txt"))) {
		pHead_cla = new Node_cla;
		Node_cla* pCur_cla = pHead_cla;
		std::wstring str;
		int x = 0;
		std::wifstream fin(Create_file_4("Class", Create_second_folder("Class", current_year), ".txt"));
		fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin.eof()) {
			pCur_cla->pNext = new Node_cla;
			std::getline(fin, str);
			pCur_cla->pNext->cla.Name = new wchar_t[str.length() + 1];
			str.copy(pCur_cla->pNext->cla.Name, str.length(), 0);
			pCur_cla->pNext->cla.Name[str.length()] = L'\0';
			pCur_cla = pCur_cla->pNext;
			pCur_cla->pNext = nullptr;
			x++;
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
		x--;
		int pointer = 0;
		int check = 0;
		while (1) {
			ShowCur(0);
			system("cls");
			pCur_cla = pHead_cla;
			int count = 0;
			while (pCur_cla->pNext != nullptr) {
				if (count == pointer) {
					SetColor(15, 4);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cla->cla.Name;
				}
				else {
					SetColor(15, 3);
					GotoXY(50, 20 + count);
					std::wcout << pCur_cla->cla.Name;
				}
				count++;
				pCur_cla = pCur_cla->pNext;
			}
			while (1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 72 || key == 'w' || key == 'W') {
						if (pointer > 0) {
							pointer--;
						}
						else {
							pointer = x - 1;
						}
						break;
					}
					if (key == 80 || key == 's' || key == 'S') {
						if (pointer < x - 1) {
							pointer++;
						}
						else {
							pointer = 0;
						}
						break;
					}
					if (key == 13) {
						pCur_cla = pHead_cla;
						if (pointer == -1) {

						}
						else {
							for (int i = 0; i < pointer; i++) {
								pCur_cla = pCur_cla->pNext;
							}
							check = 1;
							break;
						}
					}
					if (key == 27) {
						Sub_menu_stu_staff(file);
					}
				}
			}
			if (check == 1) {
				break;
			}
		}
		View_score_of_class_2(pCur_cla->cla.Name, current_year, file);
	}
	else {
		system("cls");
		std::wcout << "No class had been added" << std::endl;
	}
	delete[] current_year;
	char key = toupper(_getch());
	if (key == 27)
	{
		Sub_menu_stu_staff(file);
	}
}

void View_score_of_class_2(wchar_t* cla, char* current_year, wchar_t* file) {
	std::wstring str_1;
	std::wstring str_2;
	std::wifstream fin(L"Default_time.txt");
	fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin, str_1);
	std::getline(fin, str_2);
	fin.close();
	char* current_semester = new char[str_2.length() + 1];
	for (int i = 0; i < str_2.length(); i++) {
		current_semester[i] = str_2[i];
	}
	current_semester[str_2.length()] = L'\0';

	Node_stu* pHead_stu = new Node_stu;
	Node_stu* pCur_stu = pHead_stu;
	std::wifstream fin_3(Create_file_3(cla, Create_second_folder("Class", current_year), ".txt"));
	fin_3.imbue(std::locale(fin_3.getloc(), new std::codecvt_utf8<wchar_t>));
	std::getline(fin_3, str_1);
	std::getline(fin_3, str_1);
	fin_3.close();
	int loop = str_1.length() / 9;
	int begin = 0;
	int end = -1;
	wchar_t* a;
	for (int i = 0; i < loop; i++) {
		pCur_stu->pNext = new Node_stu;
		begin = end + 1;
		end = str_1.find(',', begin);
		a = new wchar_t[end - begin + 1];
		str_1.copy(a, end - begin, begin);
		a[end - begin] = L'\0';
		pCur_stu->pNext->stu.ID = Convert_wchart_to_int(a, end - begin);
		delete[] a;
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
	pCur_stu = pHead_stu;
	for (int i = 0; i < loop; i++) {
		wchar_t* file_1 = Convert_int_to_wchart(pCur_stu->stu.ID);
		wchar_t* file_2 = Create_file_2(file_1, Create_second_folder("Student", current_year), ".txt");
		std::wifstream fin_2(file_2);
		fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
		std::getline(fin_2, str_1);
		std::getline(fin_2, str_1);
		Read_file_stu(str_1, pCur_stu);
		std::getline(fin_2, str_1);
		Read_course_1(str_1, pCur_stu);
		std::getline(fin_2, str_1);
		Read_course_2(str_1, pCur_stu);
		std::getline(fin_2, str_1);
		Read_course_3(str_1, pCur_stu);
		std::getline(fin_2, str_1);
		Read_course_4(str_1, pCur_stu);
		std::getline(fin_2, str_1);
		Read_course_5(str_1, pCur_stu);
		fin_2.close();
		pCur_stu = pCur_stu->pNext;
	}
	
	if (checkFileWithFstream_wstring(Create_file_4("Course", current_semester, ".txt"))) {
		std::wstring str_3;
		Node_cou* pHead_cou = new Node_cou;
		Node_cou* pCur_cou = pHead_cou;
		int x = 0;
		std::wifstream fin_1(Create_file_4("Course", current_semester, ".txt"));
		fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
		while (!fin_1.eof()) {
			pCur_cou->pNext = new Node_cou;
			std::getline(fin_1, str_3);
			pCur_cou->pNext->cou.ID = new wchar_t[str_3.length() + 1];
			str_3.copy(pCur_cou->pNext->cou.ID, str_3.length(), 0);
			pCur_cou->pNext->cou.ID[str_3.length()] = L'\0';
			pCur_cou = pCur_cou->pNext;
			pCur_cou->pNext = nullptr;
			x++;
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
		fin_1.close();
		x--;
		pCur_cou = pHead_cou;
		for (int i = 0; i < x; i++) {
			wchar_t* file_3 = Create_file_2(pCur_cou->cou.ID, current_semester, ".txt");
			std::wifstream fin_2(file_3);
			fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_2, str_1);
			Read_file_cou(str_1, pCur_cou);
			fin_2.close();
			pCur_cou = pCur_cou->pNext;
		}
		system("cls");
		SetColor(15, 0);
		std::wcout << cla << std::endl;
		std::wcout << L"                    ";
		pCur_cou = pHead_cou;
		for (int i = 0; i < x; i++) {
			std::wcout << pCur_cou->cou.ID << L",";
			pCur_cou = pCur_cou->pNext;
		}
		std::wcout << std::endl;
		pCur_stu = pHead_stu;
		for (int i = 0; i < loop; i++) {
			std::wcout << i + 1 << L"," << pCur_stu->stu.ID << L"," << pCur_stu->stu.FirstName << L" " << pCur_stu->stu.LastName << L",";
			pCur_cou = pHead_cou;
			for (int i = 0; i < x; i++) {
				if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_1.ID) == 0) {
					std::wcout << pCur_stu->stu.course_1.TotalMark << L",";
				}
				else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_2.ID) == 0) {
					std::wcout << pCur_stu->stu.course_2.TotalMark << L",";
				}
				else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_3.ID) == 0) {
					std::wcout << pCur_stu->stu.course_3.TotalMark << L",";
				}
				else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_4.ID) == 0) {
					std::wcout << pCur_stu->stu.course_4.TotalMark << L",";
				}
				else if (wcscmp(pCur_cou->cou.ID, pCur_stu->stu.course_5.ID) == 0) {
					std::wcout << pCur_stu->stu.course_5.TotalMark << L",";
				}
				else {
					std::wcout << 0 << L",";
				}
				pCur_cou = pCur_cou->pNext;
			}
			std::wcout << std::endl;
			pCur_stu = pCur_stu->pNext;
		}
		Delete_Node_cou(pHead_cou);
	}
	else {
		system("cls");
		SetColor(15, 0);
		std::wcout << L"No course had been created" << std::endl;
	}
	delete[] current_semester;
	Delete_Node_stu(pHead_stu);
	char key = toupper(_getch());
	if (key == 27)
	{
		View_score_of_class_1(file);
	}
}

void Sub_menu_time_staff(wchar_t* file) {
	int Max_List_Menu = 4;
	int flag = 0;
	int pointer = 0;
	SetColor(15, 0);
	std::wstring menu[] = { L"Create School Year", L"Create Semester", L"Choose Default Time" ,L"Exit"};
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
						Create_school_year(file);
						Sleep(100000);
						break;
					case 1:
						Create_semester_1(file);
						Sleep(100000);
						break;
					case 2:
						Choose_default_time_1(file, 0);
						Sleep(100000);
						break;
					case 3:
						Sub_menu_staff(file);
						break;
					}
					break;
				}
				if (key == 27) {
					Sub_menu_staff(file);
					break;
				}
			}
		}
		Sleep(100);
	}
}

void Sub_menu_cou_staff(wchar_t* file) {
	Node_cou* pHead_cou;
	int Max_List_Menu = 7;
	int flag = 0;
	int pointer = 0;
	SetColor(15, 0);
	std::wstring menu[] = { L"Choose Course Registration Time",L"Input Course", L"View List Of Course", L"Update Course" ,L"Delete Course", L"Score", L"Exit" };
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
						Choose_cou_regis_time(file);
						Sleep(100000);
						break;
					case 1:
						Input_course_data(pHead_cou,file);
						Sleep(100000);
						break;
					case 2:
						View_list_of_course(file);
						Sleep(100000);
						break;
					case 3:
						Update_course(file);
						Sleep(100000);
						break;
					case 4:
						Delete_course(file);
						Sleep(100000);
						break;
					case 5:
						View_course_score(file);
						Sleep(100000);
						break;
					case 6:
						Sub_menu_staff(file);
						break;
					}
					break;
				}
				if (key == 27) {
					Sub_menu_staff(file);
					break;
				}
			}
		}
		Sleep(100);
	}
}

void Sub_menu_stu_staff(wchar_t* file) {
	Node_stu* pHead_stu;
	Node_cla* pHead_cla;
	int Max_List_Menu = 4;
	int flag = 0;
	int pointer = 0;
	SetColor(15, 0);
	std::wstring menu[] = { L"Input Student", L"View List Of Class", L"Score Of Class", L"Exit" };
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
						Input_student_data(pHead_stu, pHead_cla, file);
						Sleep(100000);
						break;
					case 1:
						View_list_of_class(file);
						Sleep(100000);
						break;
					case 2:
						View_score_of_class_1(file);
						Sleep(100000);
						break;
					case 3:
						Sub_menu_staff(file);
						break;
					}
					break;
				}
				if (key == 27) {
					Sub_menu_staff(file);
					break;
				}
			}
		}
		Sleep(100);
	}
}

void Sub_menu_staff(wchar_t* file) {
	int Max_List_Menu = 7;
	int flag = 0;
	SetColor(15, 0);
	std::wstring menu[] = { L"Information",L"Change Pass",L"Time",L"Course",L"Student",L"Log Out", L"Exit" };
	int pointer = 0;
	Node_cou* pHead_cou;
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
						Screen_inf_to_console_staff(file);
						Sleep(100000);
						break;
					case 1:
						Change_pass_staff(file);
						Sleep(100000);
						break;
					case 2:
						Sub_menu_time_staff(file);
						Sleep(100000);
						break;
					case 3:
						Sub_menu_cou_staff(file);
						Sleep(100000);
						break;
					case 4:
						Sub_menu_stu_staff(file);
						Sleep(100000);
						break;
					case 5:
						Main_menu();
						break;
					case 6: 
						Exit();
						flag = -1;
						break;
					}
					break;
				}
			}
		}
		if (flag == -1) {
			delete[] file;
			break;
		}
		Sleep(100);
	}
	std::cout << "Thank you very much. Bye!" << std::endl;
	Sleep(100);
	_getch();
}

void Menu_staff() {
	SetColor(15, 0);
	wchar_t* file = Login_staff();
	Sub_menu_staff(file);
	delete[] file;
}

wchar_t* Login(int& n) {
	SetColor(15, 0);
	std::wstring str;
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
	wchar_t* pass = new wchar_t[1];
	pass[0] = L'\0';
	wchar_t* input = new wchar_t[1];
	input[0] = L'\0';
	wchar_t* filename = new wchar_t[1];
	filename[0] = L'\0';
	wchar_t* file_1 = new wchar_t[1];
	file_1[0] = L'\0';
	wchar_t* file_2 = new wchar_t[1];
	file_2[0] = L'\0';
	int check = 0;
	do {
		system("cls");
		std::wcout << "Input the username: ";
		std::getline(std::wcin, str);
		delete[] filename;
		filename = new wchar_t[str.length() + 1];
		str.copy(filename, str.length(), 0);
		filename[str.length()] = L'\0';
		delete[] file_1;
		delete[] file_2;
		file_1 = Create_file_3(filename, "Staff", ".txt");
		file_2 = Create_file_2(filename, Create_second_folder("Student", current_year), ".txt");
		std::wifstream fin_1(file_1);
		std::wifstream fin_2(file_2);
		if (!fin_1 && !fin_2) {
			std::wcout << L"Error username \n";
			Sleep(200);
			check = 0;
		}
		else if (fin_1) {
			fin_1.imbue(std::locale(fin_1.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_1, str);
			delete[] pass;
			delete[] input;
			int begin = str.find(',', 0) + 1;
			int end = str.length();
			pass = new wchar_t[end - begin + 1];
			str.copy(pass, end - begin, begin);
			pass[end - begin] = L'\0';
			std::wcout << "Input the password: ";
			std::getline(std::wcin, str);
			input = new wchar_t[str.length() + 1];
			str.copy(input, str.length(), 0);
			input[str.length()] = L'\0';
			check = Check_pass(pass, input);
			if (check) {
				n = 1;
				std::wcout << "Input success" << std::endl;
			}
			else {
				std::wcout << "Error password" << std::endl;
				Sleep(200);
			}
		}
		else {
			fin_2.imbue(std::locale(fin_2.getloc(), new std::codecvt_utf8<wchar_t>));
			std::getline(fin_2, str);
			int begin = str.find(',', 0) + 1;
			int end = str.length();
			pass = new wchar_t[end - begin + 1];
			str.copy(pass, end - begin, begin);
			pass[end - begin] = L'\0';
			std::wcout << "Input the password: ";
			std::getline(std::wcin, str);
			input = new wchar_t[str.length() + 1];
			str.copy(input, str.length(), 0);
			input[str.length()] = L'\0';
			check = Check_pass(pass, input);
			if (check) {
				n = 2;
				std::wcout << "Input success" << std::endl;
			}
			else {
				std::wcout << "Error password" << std::endl;
				Sleep(200);
			}
		} 
		fin_1.close();
		fin_2.close();
	} while (check != 1);
	delete[] current_year;
	delete[] pass;
	delete[] input;
	delete[] filename;
	if (n == 1) {
		delete[] file_2;
		return file_1;
	}
	else {
		delete[] file_1;
		return file_2;
	}
}

void Main_menu() {
	int n = 0;
	wchar_t* file = Login(n);
	if (n == 1) {
		Sub_menu_staff(file);
	}
	else {
		Sub_menu_stu(file);
	}
}

void main() {
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

	{
		//bỏ các hàm thực thi vào đây
		Main_menu();
	}

	if (_CrtDumpMemoryLeaks())
	{
		std::wcout << "Leak";
	}
	else std::wcout << "No";
}