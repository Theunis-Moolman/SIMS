#ifndef ALGORITHMS_H_INCLUDED
#define ALGORITHMS_H_INCLUDED

#include "student.h"

void BubbleSortById(Student arr[], int count);
void BubbleSortByIdPtr(Student** students, int count);
int BinarySearchById(Student arr[], int left, int right, int id);
void swopPtr(Student* element1Ptr, Student* element2Ptr);

#endif // ALGORITHMS_H_INCLUDED
