#ifndef HELP_H_
#define HELP_H_

bool Check_pass(wchar_t* pass, wchar_t* input);
char* Create_file_1(char* filename, char* folder, std::string filetype);
wchar_t* Create_file_2(wchar_t* filename, char* folder, std::string filetype);
wchar_t* Create_file_3(wchar_t* filename, std::string folder, std::string filetype);
wchar_t* Create_file_4(std::string filename, std::string folder, std::string filetype);
char* Create_second_folder(std::string str, char* main_folder);
char* Create_third_folder(std::string str, char* second_folder);
int Convert_wchart_to_int(wchar_t* a, int n);
int Convert_char_to_int(char* a, int n);
double Conver_wchart_to_double(wchar_t* a, int n);
char* Convert_int_to_char(int n);
wchar_t* Convert_int_to_wchart(int n);
void GotoXY(int x, int y);
void SetColor(int background_color, int text_color);
void Delete_Node_cla(Node_cla*& pHead);
void Delete_Node_stu(Node_stu*& pHead);
void Delete_Node_cou(Node_cou*& pHead);
void Delete_Node_staff(Node_staff*& pHead);
void Delete_Node_help_1(Node_help_1*& pHead);
void Delete_Node_time_semester(Node_time_semester*& pHead);
bool checkFileWithFstream_wstring(std::wstring path);
bool checkFileWithFstream_string(std::string path);
void SetWindowSize(SHORT width, SHORT height);
void SetScreenBufferSize(SHORT width, SHORT height);
void DisableResizeWindow();
void DisableControlButon(bool Close, bool Min, bool Max);
void ShowScrollBar(BOOL Show);
void ShowCur(bool CursorVisibility);
void Exit();

#endif // !HELP_H_

