#include "io.h"
#include "student.h"
#include "class.h"
#include "utils.h"
#include <dirent.h>

void createNewBlankTemplate(char filename[], char className[]){
    FILE* fPtr = fopen(filename, "wb");
    if (fPtr != NULL){
        fwrite(className, sizeof(char), 50, fPtr);
        Student blankStudent;
        copyString("", blankStudent.name);
        copyString("", blankStudent.surname);
        blankStudent.gpa = -1.0;
        blankStudent.id = -1.0;
        blankStudent.grades.numSubjects = 0;
        for (int i = 0; i < MAX_SUBJ; i++){
            blankStudent.grades.marks[i] = -1.0;
            copyString("", blankStudent.grades.subjects[i]);
        }
        for (int i = 0; i < MAX_STUDENT_NUM; i++){
            fwrite(&blankStudent, sizeof(Student), 1, fPtr);
        }
        fclose(fPtr);
    }
    else {
        printf("Oh no! The file you specified could not be opened");
    }
}

void writeStudentInfo(char filename[], Student student){
    FILE* fPtr = fopen(filename, "rb+");
    fseek(fPtr, sizeof(char)*50, SEEK_SET);
    if (fPtr != NULL){
        fseek(fPtr, (student.id - 1) * sizeof(Student), SEEK_CUR);
        fwrite(&student, sizeof(Student), 1, fPtr);
    }
}

void saveLinkedList(int classID, List list, char className[]){
    StudentNode* currentPtr = list.frontPtr;
    char filename[50];
    snprintf(filename, sizeof(filename), "Classes/%d.bin", classID);
    createNewBlankTemplate(filename, className);
    while (currentPtr != NULL){
        writeStudentInfo(filename, currentPtr->data);
        currentPtr = currentPtr->nextPtr;
    }
}

void saveAllStudentInfo(ClassNode* startPtr){
    if (startPtr != NULL){
        saveAllStudentInfo(startPtr->leftPtr);
        saveAllStudentInfo(startPtr->rightPtr);
        saveLinkedList(startPtr->id, startPtr->students, startPtr->name);
    }
}

void saveReadableFile(FILE* stream, ClassNode* startPtr){
    if (startPtr != NULL){
        saveReadableFile(stream, startPtr->leftPtr);
        fprintf(stream, "Class name: %s\n", startPtr->name);
        fprintf(stream, "Class ID: %d\n", startPtr->id);
        StudentNode* currentPtr = startPtr->students.frontPtr;
        while (currentPtr != NULL){
            fprintf(stream, "->%s %s: \n", currentPtr->data.name, currentPtr->data.surname);
            fprintf(stream, "--->Student ID: %d\n", currentPtr->data.id);
            for (int j = 0; j < currentPtr->data.grades.numSubjects; j++){
                fprintf(stream, "\t\t>%49s: ", currentPtr->data.grades.subjects[j]);
                if (currentPtr->data.grades.marks[j] == -1){
                    fprintf(stream, "N/A\n");
                } else {
                    fprintf(stream, "%2.2f\n", currentPtr->data.grades.marks[j]);
            }
            }if (currentPtr->data.gpa != -1){
                fprintf(stream, "---->GPA: %3.2f\n", currentPtr->data.gpa);
            }
            currentPtr = currentPtr->nextPtr;
        }
        fprintf(stream, "-------------------------------------------------------------------------------\n");
        saveReadableFile(stream, startPtr->rightPtr);
    }
}

List loadClassFile(char filename[50], char className[]){
    FILE* fPtr = fopen(filename, "rb");
    List classList;
    classList.frontPtr = NULL;
    classList.backPtr = NULL;

    if (fPtr != NULL){

        Student tempStudent;
        fread(className, sizeof(char), 50, fPtr);
        while (fread(&tempStudent, sizeof(tempStudent), 1, fPtr) == 1){
            if (tempStudent.id != -1){
                addStudentLL(&classList, tempStudent);
            }
        }
    }
    fclose(fPtr);
    return classList;
}

ClassNode* loadAllStudentData(ClassNode* startPtr){
    DIR* dir = opendir("Classes");
    struct dirent* entry;
    int classID;
    char className[50];

    if (!dir){
        printf("Could not open directory?\n");
        return startPtr;
    }

    while ((entry = readdir(dir)) != NULL){
        if (strstr(entry->d_name, ".bin")) {
            char filepath[50];
            snprintf(filepath, 50, "%s/%s", "Classes", entry->d_name);

            char idStr[10];
            strncpy(idStr, entry->d_name, strlen(entry->d_name) - 4);
            idStr[strlen(entry->d_name) - 4] = '\0';
            classID = atoi(idStr);

            List classList = loadClassFile(filepath, className);

            startPtr = insertClass(startPtr, className, classID, classList);
        }
    }

    closedir(dir);
    return startPtr;
}
