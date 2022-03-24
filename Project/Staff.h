#ifndef STAFF_H_
#define STAFF_H_

static int flag;

wchar_t* Login_staff();
void Screen_inf_to_console_staff(wchar_t* file);
void Change_pass_staff(wchar_t* file);
void Sub_menu_staff(wchar_t* file);
void Create_semester_2(wchar_t* file, char* folder, wchar_t* file_login);
void Menu_staff();
void Choose_default_time_2(wchar_t* file, char* folder, wchar_t* file_login, char* default_year_1, wchar_t* default_year_2);
void View_list_of_class(wchar_t* file);
void View_list_of_student_class(wchar_t* cla, char* current_year, wchar_t* file);
void Print_inf_cou_console(Node_cou* pCur_cou, wchar_t* file_login);
void View_list_of_student_course(Node_cou* pCur_cou, wchar_t* file_login);
void Change_timetable(Node_cou* pCur_cou, wchar_t* file_login);
void Delete_course(wchar_t* file_login);
void Export_list_of_student_course(Node_cou* pCur_cou, wchar_t* file_login);
void Menu_course_score(Node_cou* pCur_cou, wchar_t* file_login);
void View_course_score(wchar_t* file_login);
void View_score_of_class_2(wchar_t* cla, char* current_year, wchar_t* file);
void View_score_of_class_1(wchar_t* file);
void Change_Score_course_2(Node_cou* pCur_cou, Node_stu* pCur_stu, wchar_t* file_login);
void Menu_update_course(Node_cou* pCur_cou, wchar_t* file_login);
void Menu_view_cou_staff(Node_cou* pCur_cou, wchar_t* file_login);
void Sub_menu_time_staff(wchar_t* file);
void Sub_menu_stu_staff(wchar_t* file);
void Sub_menu_cou_staff(wchar_t* file);
void Main_menu();
#endif // !STAFF_H_
