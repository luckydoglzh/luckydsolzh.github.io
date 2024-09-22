#include <stdio.h>
#include <stdlib.h>
#include "bubble_sort.h"


void printArry(int* nums, int numsSize){
    for(int i = 0; i < numsSize;i++){
        printf("%d, ", nums[i]);
    }
}
int main()
{
    int nums[10] = {12,5,23,56,67,3535,565,343,2424,33333};
    int len = sizeof(nums)/sizeof(int);

    bubbleSort(nums, len);

    printArry(nums, len);
    printf("\n");
    //system("pause");
    return 0;
}
