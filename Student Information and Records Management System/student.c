#include "student.h"
#include "algorithms.h"

char subjects[7][50] = {"Engineering Mathematics", "Applied Mathematics", "Electrotechniques", "Computer programming", "Electronic Engineering", "Engineering Physics", "Strength Of Materials"};

void addStudent(Student arr[], Student newStudent, int *count){
    arr[*count] = newStudent;
    (*count)++;
    printf("%d\n", *count);
}

void displayStudents(Student* arr, int count){
    for (int i = 0; i < count; i++){
        printf("%s %s: \n", (arr+i)->name, (arr+i)->surname);
        printf("Student ID: %10d\n", (arr+i)->id);
        for (int j = 0; j < (arr+i)->grades.numSubjects; j++){
            printf("\t\t%49s: ", (*(arr+i)).grades.subjects[j]);
            if ((arr+i)->grades.marks[j] == -1){
                printf("N/A\n");
            } else {
                printf("%2.2f\n", (arr+i)->grades.marks[j]);
            }
        }
        if (arr[i].gpa != -1){
            printf("GPA: %3.2f\n", (arr+i)->gpa);
        }

    }
}

Student* findStudentById(Student arr[], int count, int id){
    /*for (int i = 0; i < count; i++){
        if (arr[i].id == id){
            return &arr[i];
        }
    }
    return NULL;*/
    BubbleSortById(arr, count);
    int index = BinarySearchById(arr, 0, count, id);
    if (index != -1){
        return &arr[index];
    }
    return NULL;
}

void deleteStudent(Student arr[], int* count , int id){
    for (int i = 0; i < *count; i++){
        if (arr[i].id == id){
            for (int j = i; j < *count - 1; j++){
                arr[j] = arr[j + 1];
            }
            (*count)--;
            return;
        }
    }
}

void calculateGPA(Student *student){
    float average = 0;
    for (int i = 0; i < student->grades.numSubjects; i++){
        if (student->grades.marks[i] != -1){
            average += student->grades.marks[i];
        } else {
            printf("Incomplete grades record for %s %s!\n", student->name, student->surname);
            return;
        }
    }
    average /= student->grades.numSubjects;
    student->gpa = average;
}

void updateMarks(Student *student){
    if (student != NULL){
        for (int i = 0; i < student->grades.numSubjects; i++){
            printf("Please enter a grade for %s: ", student->grades.subjects[i]);
            scanf("%f", &student->grades.marks[i]);
        }
    }
}

void updateAllGPA(Student arr[], int count){
    for (int i = 0; i < count; i++){
        calculateGPA(&arr[i]);
    }
}

void displayStudent(Student* student){
    if (student == NULL){
        printf("Student not found!");
        return;
    }
    printf("%s %s: \n", student->name, student->surname);
    printf("Student ID: %d\n", student->id);
    for (int j = 0; j < student->grades.numSubjects; j++){
        printf("\t\t%49s: ", student->grades.subjects[j]);
        if (student->grades.marks[j] == -1){
            printf("N/A\n");
        } else {
            printf("%2.2f\n", student->grades.marks[j]);
    }
    }if (student->gpa != -1){
        printf("GPA: %3.2f\n", student->gpa);
    }
}

Student** convertToArrayOfPointers(Student arr[], int count){
    Student** students = malloc(sizeof(Student*) * count);

    for (int i = 0; i < count; i++){
        students[i] = &arr[i];
    }
    return students;
}

void displayStudentsPtr(Student** studentPtr, int count){
    if (studentPtr == NULL){
        printf("Please convert first!\n");
        return;
    }
    for (int i = 0; i < count; i++){
        printf("%s %s: \n", studentPtr[i]->name, studentPtr[i]->surname);
        printf("Student ID: %10d\n", studentPtr[i]->id);
        for (int j = 0; j < studentPtr[i]->grades.numSubjects; j++){
            printf("\t\t%49s: ", studentPtr[i]->grades.subjects[j]);
            if (studentPtr[i]->grades.marks[j] == -1){
                printf("N/A\n");
            } else {
                printf("%2.2f\n", studentPtr[i]->grades.marks[j]);
            }
        }
        if (studentPtr[i]->gpa != -1){
            printf("GPA: %3.2f\n", studentPtr[i]->gpa);
        }
    }
}

void addToFrontOfList(List* listPtr, Student student){
    StudentNode* node;
    node = malloc(sizeof(StudentNode));
    if (node == NULL){
        printf("Oh shoot! Memory allocation has failed!");
    }
    node->data = student;
    node->nextPtr = NULL;
    if (listPtr->frontPtr == NULL){
        listPtr->frontPtr = node;
        listPtr->backPtr = node;
    } else {
        node->nextPtr = listPtr->frontPtr;
        listPtr->frontPtr = node;
    }
}

void addToBackOfList(List* listPtr, Student student){
    StudentNode* node;
    node = malloc(sizeof(StudentNode));
    if (node == NULL){
        printf("Oh shoot! Memory allocation has failed!");
    }
    node->data = student;
    node->nextPtr = NULL;
    if (listPtr->frontPtr == NULL){
        listPtr->frontPtr = node;
        listPtr->backPtr = node;
    } else {
        listPtr->backPtr->nextPtr = node;
        listPtr->backPtr = node;
    }
}

List convertPtrArrayToLinkedList(Student** studentPtr, int count){
    List newList;
    newList.frontPtr = NULL;
    newList.backPtr = NULL;
    for (int i = 0; i < count; i++){
        addToFrontOfList(&newList, *studentPtr[count - 1 - i]);
    }
    return newList;
}

void addStudentLL(List* listPtr, Student data){
    if (listPtr->frontPtr != NULL){
        if (data.id < listPtr->frontPtr->data.id){
            addToFrontOfList(listPtr, data);
            return;
        } else if (data.id > listPtr->backPtr->data.id){
            addToBackOfList(listPtr, data);
            return;
        }
    } else {
            addToFrontOfList(listPtr, data);
    }

    StudentNode* node;
    StudentNode* previousPtr = NULL;
    node = malloc(sizeof(StudentNode));
    StudentNode* currentPtr = listPtr->frontPtr;
    node->data = data;
    node->nextPtr = NULL;
    while (currentPtr != NULL && currentPtr->data.id < data.id){
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }
    if (previousPtr != NULL){
        previousPtr->nextPtr = node;
        node->nextPtr = currentPtr;
    }
}

StudentNode* findStudentByIDLL(List* listPtr, int id){
    StudentNode* currentPtr = listPtr->frontPtr;
    while (currentPtr != NULL && currentPtr->data.id != id){
        currentPtr = currentPtr->nextPtr;
    }
    return currentPtr;
}

void deleteStudentLL(List* listPtr, int id){
    StudentNode* hold;
    if (listPtr->frontPtr->data.id == id){
        hold = listPtr->frontPtr;
        listPtr->frontPtr = listPtr->frontPtr->nextPtr;
        free(hold);
    }
    StudentNode* currentPtr = listPtr->frontPtr;
    StudentNode* previousPtr = NULL;
    while (currentPtr != NULL && currentPtr->data.id != id){
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }
    if (currentPtr == listPtr->backPtr){
        hold = currentPtr;
        listPtr->backPtr = previousPtr;
        listPtr->backPtr->nextPtr = NULL;
        free(hold);
    } else if (currentPtr != NULL){
        hold = currentPtr;
        previousPtr->nextPtr = currentPtr->nextPtr;
        free(hold);
    }
}

void deleteLL(List* listPtr){
    StudentNode* hold;
    StudentNode* currentPtr = listPtr->frontPtr;
    while (currentPtr != NULL){
        hold = currentPtr;
        currentPtr = currentPtr->nextPtr;
        free(hold);
    }
    listPtr->frontPtr = NULL;
    listPtr->backPtr = NULL;
}

void printLL(List* listPtr){
    StudentNode* currentPtr = listPtr->frontPtr;
    while (currentPtr != NULL){
        displayStudent(&currentPtr->data);
        currentPtr = currentPtr->nextPtr;
    }
}

void updateStudentGPALL(List* listPtr){
    StudentNode* currentPtr = listPtr->frontPtr;
    while (currentPtr != NULL){
        calculateGPA(&currentPtr->data);
        currentPtr = currentPtr->nextPtr;
    }
}
