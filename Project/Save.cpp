#include "Struct.h"
#include "Time.h"
#include "Help.h"
#include "Save.h"

void Save_stu_to_test(Node_stu* pHead, char* folder) {
	char* file;
	char* filename;
	while (pHead != nullptr) {
		filename = Convert_int_to_char(pHead->stu.ID);
		file = Create_file_1(filename, folder, ".txt");
		std::wofstream fout(file);
		fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		fout << pHead->stu.account.ID << L"," << pHead->stu.account.Pass << std::endl;
		fout << pHead->stu.ID << L"," << pHead->stu.FirstName << L"," << pHead->stu.LastName << L"," << pHead->stu.Gender << L"," << pHead->stu.Birthday.Day << L"/" << pHead->stu.Birthday.Month << L"/" << pHead->stu.Birthday.Year << L"," << pHead->stu.SocialID << std::endl;
		fout << pHead->stu.course_1.ID << L"," << pHead->stu.course_1.TotalMark << L"," << pHead->stu.course_1.FinalMark << L"," << pHead->stu.course_1.MidtermMark << L"," << pHead->stu.course_1.OtherMark << L"," << pHead->stu.course_1.GPA << std::endl;
		fout << pHead->stu.course_2.ID << L"," << pHead->stu.course_2.TotalMark << L"," << pHead->stu.course_2.FinalMark << L"," << pHead->stu.course_2.MidtermMark << L"," << pHead->stu.course_2.OtherMark << L"," << pHead->stu.course_2.GPA << std::endl;
		fout << pHead->stu.course_3.ID << L"," << pHead->stu.course_3.TotalMark << L"," << pHead->stu.course_3.FinalMark << L"," << pHead->stu.course_3.MidtermMark << L"," << pHead->stu.course_3.OtherMark << L"," << pHead->stu.course_3.GPA << std::endl;
		fout << pHead->stu.course_4.ID << L"," << pHead->stu.course_4.TotalMark << L"," << pHead->stu.course_4.FinalMark << L"," << pHead->stu.course_4.MidtermMark << L"," << pHead->stu.course_4.OtherMark << L"," << pHead->stu.course_4.GPA << std::endl;
		fout << pHead->stu.course_5.ID << L"," << pHead->stu.course_5.TotalMark << L"," << pHead->stu.course_5.FinalMark << L"," << pHead->stu.course_5.MidtermMark << L"," << pHead->stu.course_5.OtherMark << L"," << pHead->stu.course_5.GPA << std::endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 6; j++) {
				fout << pHead->stu.Schedule[i][j];
			}
		}
		pHead = pHead->pNext;
		fout.close();
	}
}

void Save_cla_to_test(Node_cla* pHead, char* folder) {
	wchar_t* file;
	while (pHead != nullptr) {
		file = Create_file_2(pHead->cla.Name, folder, ".txt");
		std::wofstream fout(file);
		fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		fout << pHead->cla.Name << std::endl;
		fout << pHead->cla.StudentID << std::endl;
		pHead = pHead->pNext;
		fout.close();
	}
}

void Save_name_class(Node_cla* pHead, char* current_year) {
	Node_cla* pHead_1;
	Node_cla* pCur;
	std::wstring str;
	if (checkFileWithFstream_wstring(Create_file_4("Class", Create_second_folder("Class",current_year),".txt"))) {
		pHead_1 = new Node_cla;
		pCur = pHead_1;
		std::wifstream fin(Create_file_4("Class", Create_second_folder("Class", current_year), ".txt"));
		if (!fin) {

		}
		else {
			fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
			while (!fin.eof()) {
				pCur->pNext = new Node_cla;
				std::getline(fin, str);
				pCur->pNext->cla.Name = new wchar_t[str.length() + 1];
				str.copy(pCur->pNext->cla.Name, str.length(), 0);
				pCur->pNext->cla.Name[str.length()] = L'\0';
				pCur = pCur->pNext;
				pCur->pNext = nullptr;
			}
			if (pHead_1->pNext == nullptr) {
				delete pHead_1;
				pHead_1 = nullptr;
			}
			else {
				Node_cla* pTemp = pHead_1;
				pHead_1 = pHead_1->pNext;
				delete pTemp;
			}
		}
		fin.close();
		pCur = pHead_1;
		std::wofstream fout(Create_file_4("Class", Create_second_folder("Class", current_year), ".txt"));
		fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		while (pCur->pNext != nullptr) {
			fout << pCur->cla.Name << std::endl;
			pCur = pCur->pNext;
		}
		while (pHead != nullptr) {
			fout << pHead->cla.Name << std::endl;
			pHead = pHead->pNext;
		}
		fout.close();
		Delete_Node_cla(pHead_1);
	}
	else {
		std::wofstream fout(Create_file_4("Class", Create_second_folder("Class", current_year), ".txt"));
		fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		while (pHead != nullptr) {
			fout << pHead->cla.Name << std::endl;
			pHead = pHead->pNext;
		}
		fout.close();
	}
}

void Save_cou_to_test(Node_cou* pHead, char* folder) {
	wchar_t* file;
	while (pHead != nullptr) {
		file = Create_file_2(pHead->cou.ID, folder, ".txt");
		std::wofstream fout(file);
		fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		fout << pHead->cou.ID << L',' << pHead->cou.Name << L',' << pHead->cou.Teacher_Name << L',' << pHead->cou.Credit << L',' << pHead->cou.max_stu << L',' << pHead->cou.count << L',';
		fout << pHead->cou.ses_1.day_of_week << L',' << pHead->cou.ses_1.session << L',' << pHead->cou.ses_2.day_of_week << L',' << pHead->cou.ses_2.session << std::endl;
		fout << pHead->cou.StudentID << std::endl;
		pHead = pHead->pNext;
		fout.close();
	}
}

void Save_name_course(Node_cou* pHead, char* folder) {
	Node_cou* pHead_1;
	Node_cou* pCur;
	std::wstring str;
	if (checkFileWithFstream_wstring(Create_file_4("Course",folder,".txt"))) {
		pHead_1 = new Node_cou;
		pCur = pHead_1;
		std::wifstream fin(Create_file_4("Course", folder, ".txt"));
		if (!fin) {

		}
		else {
			fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t>));
			while (!fin.eof()) {
				pCur->pNext = new Node_cou;
				std::getline(fin, str);
				pCur->pNext->cou.ID = new wchar_t[str.length() + 1];
				str.copy(pCur->pNext->cou.ID, str.length(), 0);
				pCur->pNext->cou.ID[str.length()] = L'\0';
				pCur = pCur->pNext;
				pCur->pNext = nullptr;
			}
			if (pHead_1->pNext == nullptr) {
				delete pHead_1;
				pHead_1 = nullptr;
			}
			else {
				Node_cou* pTemp = pHead_1;
				pHead_1 = pHead_1->pNext;
				delete pTemp;
			}
		}
		fin.close();
		pCur = pHead_1;
		std::wofstream fout(Create_file_4("Course", folder, ".txt"));
		fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		while (pCur->pNext != nullptr) {
			fout << pCur->cou.ID << std::endl;
			pCur = pCur->pNext;
		}
		while (pHead != nullptr) {
			fout << pHead->cou.ID << std::endl;
			pHead = pHead->pNext;
		}
		fout.close();
		Delete_Node_cou(pHead_1);
	}
	else {
		std::wofstream fout(Create_file_4("Course", folder, ".txt"));
		fout.imbue(std::locale(fout.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		while (pHead != nullptr) {
			fout << pHead->cou.ID << std::endl;
			pHead = pHead->pNext;
		}
		fout.close();
	}
}
