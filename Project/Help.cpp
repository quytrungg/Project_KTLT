#include "Struct.h"
#include "Staff.h"
#include "Help.h"

bool Check_pass(wchar_t* pass, wchar_t* input) {
	int n = wcslen(pass);
	int m = wcslen(input);
	if (m != n)	return false;
	for (int i = 0; i < n; i++) {
		if (pass[i] != input[i]) {
			return false;
		}
	}
	return true;
}

char* Create_file_1(char* filename, char* folder, std::string filetype) {
	int n = filetype.length() + 2 + strlen(filename) + strlen(folder);
	char* file = new char[n];
	int count = 0;
	for (int i = 0; i < strlen(folder); i++) {
		file[count] = folder[i];
		count++;
	}
	file[count] = '\\';
	count++;
	for (int i = 0; i < strlen(filename); i++) {
		file[count] = filename[i];
		count++;
	}
	char* a = new char[filetype.length() + 1];
	filetype.copy(a, filetype.length(), 0);
	a[filetype.length()] = '\0';
	for (int i = 0; i < filetype.length(); i++) {
		file[count] = a[i];
		count++;
	}
	delete[] a;
	file[n - 1] = '\0';
	return file;
}

wchar_t* Create_file_2(wchar_t* filename, char* folder, std::string filetype) {
	int n = filetype.length() + 2 + wcslen(filename) + strlen(folder);
	wchar_t* file = new wchar_t[n];
	int count = 0;
	for (int i = 0; i < strlen(folder); i++) {
		file[count] = folder[i];
		count++;
	}
	file[count] = '\\';
	count++;
	for (int i = 0; i < wcslen(filename); i++) {
		file[count] = filename[i];
		count++;
	}
	char* a = new char[filetype.length() + 1];
	filetype.copy(a, filetype.length(), 0);
	a[filetype.length()] = '\0';
	for (int i = 0; i < filetype.length(); i++) {
		file[count] = a[i];
		count++;
	}
	delete[] a;
	file[n - 1] = '\0';
	return file;
}

wchar_t* Create_file_3(wchar_t* filename, std::string folder, std::string filetype) {
	int n = filetype.length() + 2 + wcslen(filename) + folder.length();
	wchar_t* file = new wchar_t[n];
	int count = 0;
	for (int i = 0; i < folder.length(); i++) {
		file[count] = folder[i];
		count++;
	}
	file[count] = '\\';
	count++;
	for (int i = 0; i < wcslen(filename); i++) {
		file[count] = filename[i];
		count++;
	}
	char* a = new char[filetype.length() + 1];
	filetype.copy(a, filetype.length(), 0);
	a[filetype.length()] = '\0';
	for (int i = 0; i < filetype.length(); i++) {
		file[count] = a[i];
		count++;
	}
	delete[] a;
	file[n - 1] = '\0';
	return file;
}

wchar_t* Create_file_4(std::string filename, std::string folder, std::string filetype) {
	int n = filetype.length() + 2 + filename.length() + folder.length();
	wchar_t* file = new wchar_t[n];
	int count = 0;
	for (int i = 0; i < folder.length(); i++) {
		file[count] = folder[i];
		count++;
	}
	file[count] = '\\';
	count++;
	for (int i = 0; i < filename.length(); i++) {
		file[count] = filename[i];
		count++;
	}
	char* a = new char[filetype.length() + 1];
	filetype.copy(a, filetype.length(), 0);
	a[filetype.length()] = '\0';
	for (int i = 0; i < filetype.length(); i++) {
		file[count] = a[i];
		count++;
	}
	delete[] a;
	file[n - 1] = '\0';
	return file;
}

int Convert_wchart_to_int(wchar_t* a, int n) {
	int m = 0;
	int p;
	for (int i = 0; i < n; i++) {
		p = a[i] - L'0';
		m = m * 10 + p;
	}
	return m;
}

int Convert_char_to_int(char* a, int n)
{
	int m = 0;
	int p;
	for (int i = 0; i < n; i++) {
		p = a[i] - L'0';
		m = m * 10 + p;
	}
	return m;
}

double Conver_wchart_to_double(wchar_t* a, int n) {
	double m = 0;
	int find = 0;
	double p;
	for (int i = 0; i < n; i++) {
		if (a[i] == L'.') {
			find = i;
			break;
		}
	}
	if (find == 0) {
		for (int i = 0; i < n; i++) {
			p = a[i] - L'0';
			m = m * 10 + p;
		}
	}
	else {
		double r = 10;
		for (int i = 0; i < find; i++) {
			p = a[i] - L'0';
			m = m * 10 + p;
		}
		for (int i = find + 1; i < n; i++) {
			p = a[i] - L'0';
			m = m + p / r;
			r = r * 10;
		}
	}
	return m;
}

char* Convert_int_to_char(int n) {
	int count = 0;
	for (int i = n; i > 0; i = i / 10) {
		count++;
	}
	char* a = new char[count + 1];
	int r;
	for (int i = 0; i < count; i++) {
		r = n % 10;
		n = n / 10;
		a[count - 1 - i] = r + '0';
	}
	a[count] = '\0';
	return a;
}

wchar_t* Convert_int_to_wchart(int n) {
	int count = 0;
	for (int i = n; i > 0; i = i / 10) {
		count++;
	}
	wchar_t* a = new wchar_t[count + 1];
	int r;
	for (int i = 0; i < count; i++) {
		r = n % 10;
		n = n / 10;
		a[count - 1 - i] = r + '0';
	}
	a[count] = '\0';
	return a;
}

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int background_color, int text_color)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int color_code = background_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}

void Delete_Node_stu(Node_stu*& pHead) {
	Node_stu* pTemp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = pHead;
	}
}

void Delete_Node_staff(Node_staff*& pHead) {
	Node_staff* pTemp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = pHead;
	}
}

void Delete_Node_cla(Node_cla*& pHead) {
	Node_cla* pTemp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = pHead;
	}
}

void Delete_Node_cou(Node_cou*& pHead) {
	Node_cou* pTemp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = pHead;
	}
}

void Delete_Node_help_1(Node_help_1*& pHead) {
	Node_help_1* pTemp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = pHead;
	}
}

void Delete_Node_time_semester(Node_time_semester*& pHead) {
	Node_time_semester*  pTemp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = pHead;
	}
}

char* Create_second_folder(std::string str, char* main_folder) {
	int n = str.length() + 2 + strlen(main_folder);
	char* second_folder = new char[n];
	int count = 0;
	for (int i = 0; i < strlen(main_folder); i++) {
		second_folder[count] = main_folder[i];
		count++;
	}
	second_folder[count] = '\\';
	count++;
	char* a = new char[str.length() + 1];
	str.copy(a, str.length(), 0);
	a[str.length()] = '\0';
	for (int i = 0; i < str.length(); i++) {
		second_folder[count] = a[i];
		count++;
	}
	delete[] a;
	second_folder[n - 1] = '\0';
	return second_folder;
}

char* Create_third_folder(std::string str, char* second_folder) {
	int n = str.length() + 2 + strlen(second_folder);
	char* third_folder = new char[n];
	int count = 0;
	for (int i = 0; i < strlen(second_folder); i++) {
		third_folder[count] = second_folder[i];
		count++;
	}
	third_folder[count] = '\\';
	count++;
	char* a = new char[str.length() + 1];
	str.copy(a, str.length(), 0);
	a[str.length()] = '\0';
	for (int i = 0; i < str.length(); i++) {
		third_folder[count] = a[i];
		count++;
	}
	delete[] a;
	third_folder[n - 1] = '\0';
	return third_folder;
}

bool checkFileWithFstream_wstring(std::wstring path) {
	std::ifstream isf(path);
	return isf.good();
}

bool checkFileWithFstream_string(std::string path) {
	std::ifstream isf(path);
	return isf.good();
}

// Ham console
void SetWindowSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT WindowSize;

	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Right = width;
	WindowSize.Bottom = height;

	SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void SetScreenBufferSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD NewSize;
	NewSize.X = width;
	NewSize.Y = height;

	SetConsoleScreenBufferSize(hStdout, NewSize);
}

void DisableResizeWindow()
{
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void DisableControlButon(bool Close, bool Min, bool Max)
{
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	if (Close == 1)
	{
		DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}
	if (Min == 1)
	{
		DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	}
	if (Max == 1)
	{
		DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	}
}

void ShowScrollBar(BOOL Show)
{
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, Show);
}

// Ham an hien con tro
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}

void Exit()
{
	exit(0);
}