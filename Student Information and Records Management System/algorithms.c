#include "algorithms.h"

void BubbleSortById(Student arr[], int count){
    int sorted = 0;
    Student hold;
    while (!sorted){
        sorted = 1;
        for (int i = 0; i < count - 1; i++){
            if (arr[i].id > arr[i + 1].id){
                sorted = 0;
                hold = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = hold;
            }
        }
    }
}

void BubbleSortByIdPtr(Student** students, int count){
    int sorted = 0;
    while (!sorted){
        sorted = 1;
        for (int i = 0; i < count -1; i++){
            if (students[i]->id > students[i+1]->id){
                swopPtr(students[i], students[i+1]);
            }
        }
    }
}

int BinarySearchById(Student arr[], int left, int right, int id){
    int index = (right + left)/2;
    if (left>right){
        return -1;
    }
    if (arr[index].id == id){
        return index;
    } else if (arr[index].id > id){
        return BinarySearchById(arr, index + 1, right, id);
    } else if (arr[index].id < id){
        return BinarySearchById(arr, left, index - 1, id);
    }
    return -1;
}

void swopPtr(Student* element1Ptr, Student* element2Ptr){
    Student hold;
    if (element1Ptr == NULL || element2Ptr == NULL){
        return;
    }
    hold = *element1Ptr;
    *element1Ptr = *element2Ptr;
    *element2Ptr = hold;
}
