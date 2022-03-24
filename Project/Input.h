#ifndef INPUT_H_
#define INPUT_H_
#include "Struct.h"

void Input_one_student_by_file(std::wstring str, Node_stu* pCur);
void Input_student(std::wstring str, Node_stu*& pHead);
void Input_student_data(Node_stu*& pHead_stu, Node_cla*& pHead_cla, wchar_t* file_login);
void Input_one_class(std::wstring str, Node_cla* pCur_cla, Node_stu* pHead_stu);
void Input_one_course_direct(Node_cou* pCur);
void Input_one_course_by_file(std::wstring str, Node_cou* pCur);
void Input_course_direct(Node_cou*& pHead_cou, wchar_t* file_login);
void Input_course_by_file(Node_cou*& pHead_cou, wchar_t* file_login);
void Input_course_data(Node_cou*& pHead_cou, wchar_t* file_login);
void Input_score(Node_cou* pCur_cou, wchar_t* file_login);
#endif // !INPUT_H_
