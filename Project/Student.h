#ifndef STUDENT_H_
#define STUDENT_H_

bool Check_pass(wchar_t* pass, wchar_t* input);
wchar_t* Login_stu();
void Change_pass_stu(wchar_t* file);
void Screen_stu_to_console_stu(wchar_t* file);
void Sub_menu_stu(wchar_t* file);
void Menu_stu();
void Register_course(Node_cou*& pHead_cou_1, wchar_t* file);
void View_course_stu(Node_cou*& pHead_cou, wchar_t* file);
void Cout_day_of_week(int n);
void Delete_course_stu(Node_cou*& pHead_cou, wchar_t* file);
void Sub_menu_cou_stu(wchar_t* file);
void Score_stu(Node_cou*& pHead_cou, wchar_t* file);

#endif // !STUDENT_H_
