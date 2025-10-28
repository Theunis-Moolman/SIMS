#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include "class.h"
#include <stdio.h>

#define MAX_STUDENT_NUM 1000
#define MAX_CLASS_NUM 1000

void createNewBlankTemplate(char filename[], char className[]);
void saveLinkedList(int classID, List list, char className[]);
void saveAllStudentInfo(ClassNode* startPtr);
List loadClassFile(char filename[50], char className[]);
ClassNode* loadAllStudentData(ClassNode* startPtr);

#endif // IO_H_INCLUDED
