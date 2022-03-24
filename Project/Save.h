#ifndef SAVE_H_
#define SAVE_H_
#include "Struct.h"

void Save_stu_to_test(Node_stu* pHead, char* folder);
void Save_cla_to_test(Node_cla* pHead, char* folder);
void Save_name_class(Node_cla* pHead, char* current_year);
void Save_cou_to_test(Node_cou* pHead, char* folder);
void Save_name_course(Node_cou* pHead, char* folder);

#endif // !SAVE_H_


