#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

#include "student.h"

struct classNode {
    int id;
    char name[50];
    List students;
    struct classNode *leftPtr, *rightPtr;
};

typedef struct classNode ClassNode;

typedef struct {
    ClassNode* startPtr;
} Tree;

Tree CreateNewTree();
ClassNode* insertClass(ClassNode* startPtr, char name[], int id, List students);
ClassNode* findClass(ClassNode* startPtr, int id);
void inOrderClasses(ClassNode *startPtr);
void deleteTree(ClassNode* startPtr);
void updateAllGPATree(ClassNode* startPtr);

#endif // CLASS_H_INCLUDED
