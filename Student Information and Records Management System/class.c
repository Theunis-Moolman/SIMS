#include "class.h"
#include "utils.h"
#include "student.h"

Tree CreateNewTree(){
    Tree newTree;
    newTree.startPtr = NULL;
    return newTree;
}


ClassNode* insertClass(ClassNode* startPtr, char name[], int id, List students){
    if (startPtr == NULL){
        ClassNode* newClass = malloc(sizeof(ClassNode));
        newClass->students = students;
        copyString(name, newClass->name);
        newClass->id = id;
        newClass->leftPtr = NULL;
        newClass->rightPtr = NULL;
        return newClass;
    } else {
        if (id < startPtr->id){
            startPtr->leftPtr = insertClass(startPtr->leftPtr, name, id, students);
        } else if (id > startPtr->id){
            startPtr->rightPtr = insertClass(startPtr->rightPtr, name, id, students);
        }
    }
    return startPtr;
}

ClassNode* findClass(ClassNode* startPtr, int id){
    if (startPtr == NULL){
        return NULL;
    }

    if (startPtr->id == id){
        return startPtr;
    }
    if (id < startPtr->id){
        return findClass(startPtr->leftPtr, id);
    } else if (id > startPtr->id){
        return findClass(startPtr->rightPtr, id);
    }
    return NULL;
}

void inOrderClasses(ClassNode *startPtr){
    if (startPtr != NULL){
        inOrderClasses(startPtr->leftPtr);
        printf("Class ID: %d\n", startPtr->id);
        printf("Class name: %s\n", startPtr->name);
        printLL(&startPtr->students);
        inOrderClasses(startPtr->rightPtr);
    }
}

void deleteTree(ClassNode* startPtr){
    if (startPtr != NULL){
        deleteTree(startPtr->leftPtr);
        deleteTree(startPtr->rightPtr);
        deleteLL(&startPtr->students);
        free(startPtr);
        startPtr = NULL;
    }
}

void updateAllGPATree(ClassNode* startPtr){
    if (startPtr != NULL){
        updateAllGPATree(startPtr->leftPtr);
        updateAllGPATree(startPtr->rightPtr);
        updateStudentGPALL(&startPtr->students);
    }
}
