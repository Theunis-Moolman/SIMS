#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "utils.h"
#include "algorithms.h"
#include "class.h"
#include "io.h"
#include "string.h"

enum mode{
    CREATE_CLASS = 1,
    MANIPULATE_CLASS,
    SAVE_INFO
};

enum creationMode {
    ADD_STUDENT = 1,
    DISPLAY_STUDENTS,
    DELETE_STUDENT,
    CALCULATE_GPA,
    UPDATE_GPA_ALL,
    DISPLAY_STUDENT,
    FINISH
};

enum classMode {
    PRINT_ALL_CLASSES = 1,
    ADD_STUDENT_C,
    DELETE_STUDENT_C,
    UPDATE_MARKS,
    UPDATE_GPA_ALL_T
};

List createNewClass();
void manipulateClass(Tree classTree);

int main()
{
    int choice;
    List tempStudents;
    int tempID;
    char tempName[50];
    Tree classTree = CreateNewTree();
    classTree.startPtr = loadAllStudentData(classTree.startPtr);

    printf("\a\t--------SIRMS-------\t\n");

    do {
        printf("Menu options:\n");
        printf("1: Create a class\n");
        printf("2: Manipulate a class\n");
        printf("3: Save all info\n");
        printf("0: EXIT\n");
        printf("Please make a selection: ");
        scanf("%d", &choice);
        switch ((enum mode) choice){
            case CREATE_CLASS:
                tempStudents = createNewClass();
                printf("Please input a class ID: ");
                scanf("%d", &tempID);
                printf("Please input a class name: ");
                scanf("%49s", tempName);
                classTree.startPtr = insertClass(classTree.startPtr, tempName, tempID, tempStudents);
                break;
            case MANIPULATE_CLASS:
                manipulateClass(classTree);
                break;
            case SAVE_INFO:
                saveAllStudentInfo(classTree.startPtr);
                FILE* textFile = fopen("studentData.txt", "w");
                if (textFile != NULL){
                    saveReadableFile(textFile, classTree.startPtr);
                }
                fclose(textFile);
                break;
            }

    } while (choice != 0);
    deleteTree(classTree.startPtr);
}

List createNewClass(){
    int choice;
    int count = 0;
    int tempID;
    int numStudents;
    Student* students;
    Student* tempStudent = malloc(sizeof(Student));
    Student** ptrStudents = NULL;
    List studentClass;

    printf("\a\t--------NEW CLASS CREATION MODE-------\t\n");

    printf("Please enter the amount of students to handle: ");
    scanf("%d", &numStudents);

    students = malloc(sizeof(Student) * numStudents);

    do {
        printf("Menu options:\n");
        printf("1: Add a student\n");
        printf("2: Display students\n");
        printf("3: Delete student\n");
        printf("4: Update marks\n");
        printf("5: Update GPAs\n");
        printf("6: Display student results\n");
        printf("7: FINISH\n");
        printf("Please make a selection: ");
        scanf("%d", &choice);
        switch ((enum creationMode) choice){
        case ADD_STUDENT:
            if (count < numStudents){
                memset(tempStudent, 0, sizeof(Student));
                printf("Enter student name: ");
                scanf("%49s", tempStudent->name);
                printf("Enter student surname: ");
                scanf("%49s", tempStudent->surname);
                printf("Enter student id: ");
                tempStudent->grades.numSubjects = 0;
                scanf("%d", &tempStudent->id);
                for (int i = 0; i < MAX_SUBJ; i++){
                    printf("Does this student have: %s (1 - YES, EVERYTHING ELSE - NO)", subjects[i]);
                    scanf("%d", &choice);
                    if (choice == 1){
                        copyString(subjects[i], tempStudent->grades.subjects[tempStudent->grades.numSubjects]);
                        tempStudent->grades.marks[tempStudent->grades.numSubjects] = -1.0;
                        tempStudent->grades.numSubjects++;
                    }
                }
                tempStudent->gpa = -1;
                addStudent(students, *tempStudent, &count);
            } else {
                printf("Maximum size reached! Student could not be added ) :\n");
            }
            break;
        case DISPLAY_STUDENTS:
            displayStudents(students, count);
            break;
        case DELETE_STUDENT:
            printf("Please enter a student ID: ");
            scanf("%d", &tempID);
            deleteStudent(students, &count, tempID);
            break;
        case CALCULATE_GPA:
            printf("Please enter a student ID: ");
            scanf("%d", &tempID);
            tempStudent = findStudentById(students, count, tempID);
            updateMarks(tempStudent);
            break;
        case UPDATE_GPA_ALL:
            updateAllGPA(students, count);
            break;
        case DISPLAY_STUDENT:
            printf("Please enter a student ID: ");
            scanf("%d", &tempID);
            tempStudent = findStudentById(students, count, tempID);
            displayStudent(tempStudent);
            break;
        case FINISH:
            ptrStudents = convertToArrayOfPointers(students, count);
            BubbleSortByIdPtr(ptrStudents, count);
            studentClass = convertPtrArrayToLinkedList(ptrStudents, count);
            free(students);
            free(tempStudent);
            break;
        }
    } while (choice != 7);
    return studentClass;
}

void manipulateClass(Tree classTree){
    int choice;
    int tempID;
    ClassNode* tempNode;
    Student* tempStudent = malloc(sizeof(Student));
    StudentNode* tempStudentNode;

    printf("\a\t--------MANIPULATE CLASS MODE-------\t\n");
    do {
        printf("Menu options:\n");
        printf("1: Print all classes\n");
        printf("2: Add a student\n");
        printf("3: Delete a student\n");
        printf("4: Update marks\n");
        printf("5: Update all GPA's\n");
        printf("0: EXIT\n");
        printf("Please make a selection: ");
        scanf("%d", &choice);
        switch ((enum classMode) choice){
        case PRINT_ALL_CLASSES:
            printf("Printing all classes:\n");
            inOrderClasses(classTree.startPtr);
            break;
        case ADD_STUDENT_C:
            printf("Enter a class ID:\n");
            scanf("%d", &tempID);
            tempNode = findClass(classTree.startPtr, tempID);
            memset(tempStudent, 0, sizeof(Student));
            if (tempNode != NULL){
                printf("Enter student name: ");
                scanf("%49s", tempStudent->name);
                printf("Enter student surname: ");
                scanf("%49s", tempStudent->surname);
                printf("Enter student id: ");
                tempStudent->grades.numSubjects = 0;
                scanf("%d", &tempStudent->id);
                for (int i = 0; i < MAX_SUBJ; i++){
                    printf("Does this student have: %s (1 - YES, EVERYTHING ELSE - NO)", subjects[i]);
                    scanf("%d", &choice);
                    if (choice == 1){
                        copyString(subjects[i], tempStudent->grades.subjects[tempStudent->grades.numSubjects]);
                        tempStudent->grades.marks[tempStudent->grades.numSubjects] = -1.0;
                        tempStudent->grades.numSubjects++;
                    }
                }
                tempStudent->gpa = -1;
                addStudentLL(&tempNode->students, *tempStudent);
            } else {
                printf("Could not find class!\n");
            }
            break;
        case DELETE_STUDENT_C:
            printf("Enter a class ID:\n");
            scanf("%d", &tempID);
            tempNode = findClass(classTree.startPtr, tempID);
            if (tempNode != NULL){
                printf("Enter a student ID");
                scanf("%d", &tempID);
                deleteStudentLL(&tempNode->students, tempID);
            } else{
                printf("Could not locate the class!\n");
            }
            break;
        case UPDATE_MARKS:
            printf("Enter a class ID:\n");
            scanf("%d", &tempID);
            tempNode = findClass(classTree.startPtr, tempID);
            if (tempNode != NULL){
                printf("Enter a student ID");
                scanf("%d", &tempID);
                tempStudentNode = findStudentByIDLL(&tempNode->students, tempID);
                updateMarks(&tempStudentNode->data);
            }else {
                printf("Could not locate the class!\n");
            }
            break;
        case UPDATE_GPA_ALL_T:
            updateAllGPATree(classTree.startPtr);
            break;
        }
    } while (choice != 0);
}
