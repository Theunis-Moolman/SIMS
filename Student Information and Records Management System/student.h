#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#define MAX_NAME 50
#define MAX_SUBJ 7

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numSubjects;
    float marks[MAX_SUBJ];
    char subjects[MAX_SUBJ][50];
} Grades;

typedef struct {
    int id;
    char name[MAX_NAME];
    char surname[MAX_NAME];
    Grades grades;
    float gpa;
} Student;

struct studentNode{
    Student data;
    struct studentNode* nextPtr;
};

typedef struct studentNode StudentNode;

typedef struct {
    StudentNode *frontPtr, *backPtr;
} List;

extern char subjects[7][50];
void addStudent(Student arr[], Student newStudent, int *count);
void displayStudents(Student* arr, int count);
Student* findStudentById(Student arr[], int count, int id);
void deleteStudent(Student arr[], int* count, int id);
void updateMarks(Student* student);
void calculateGPA(Student *student);
void updateAllGPA(Student arr[], int count);
void displayStudent(Student* student);
Student** convertToArrayOfPointers(Student arr[], int count);
void displayStudentsPtr(Student** studentPtr, int count);
List convertPtrArrayToLinkedList(Student** studentPtr, int count);
void addToFrontOfList(List* listPtr, Student student);
void addToBackOfList(List* listPtr, Student student);
void addStudentLL(List* listPtr, Student data);
StudentNode* findStudentByIDLL(List* listPtr, int id);
void deleteStudentLL(List* listPtr, int id);
void deleteLL(List* listPtr);
void printLL(List* listPtr);
void updateStudentGPALL(List* listPtr);

#endif // STUDENT_H_INCLUDED
