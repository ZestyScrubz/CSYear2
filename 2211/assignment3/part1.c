/** 
 * 2211 Computer Science Assignment 3
 * Student Name: Isaac Tran
 * Student Email: itran9@uwo.ca
 * Student ID: 251446564
 * Due Date: 2025-10-21
**/

#include <stdio.h>

int main(void) {
    
    int numProcess;

    // Prompt the user
    printf("Enter the number of integer to process: ");
    scanf("%d", &numProcess);

    while (numProcess < 5 || numProcess > 12) {
        printf("Enter the number of integer to process: ");
        scanf("%d", &numProcess);
    }

    int intArray[numProcess];

    printf("There is enough room in your array for %d integers (%d bytes)", numProcess, sizeof(intArray));
    printf("\nPlease enter your integers separated by space: ");
    
    // Store the array size value
    int arraySize = sizeof(intArray) / sizeof(intArray[0]);

    // Store each value into the array
    for (int i = 0; i < arraySize; i++) {
        scanf("%d", &intArray[i]);
    }

    // start at index 0 and iterate up to the last index
    printf("Part 1:\n\tYour array is: ");
    int firstPrinted = 1; // skip the first ","
    for (int i = 0; i < arraySize; i++) {
        if (!firstPrinted) printf(", ");
        printf("[%d] = %d", i, intArray[i]);
        firstPrinted = 0;
    }
    printf("\n");

    // start at the last index of the array and iterate down to 0
    printf("Part 2:\n\tYour array in reverse is: ");
    firstPrinted = 1;
    for (int i = arraySize - 1; i >= 0; i--) {
        if (!firstPrinted) printf(", ");
        printf("[%d] = %d", i, intArray[i]);
        firstPrinted = 0;
    }
    printf("\n");

    // loop through array and take the mod of the value and print even
    printf("Part 3:\n\tThe even elements in the array is: ");
    firstPrinted = 1;
    for (int i = 0; i < arraySize; i++) {
        if (intArray[i] % 2 == 0) {
            if (!firstPrinted) printf(", "); // we skip printing the first "," and print a "," before every print
            printf("[%d] = %d", i, intArray[i]);
            firstPrinted = 0;
        }
    }
    printf("\n");

    // loop through array and get the value and add them up
    int sum = 0;
    printf("Part 4:\n\tThe sum of all values in your array is: ");
    for (int i = 0; i < arraySize; i++) {
        sum += intArray[i];
    }
    printf("%d", sum);
    printf("\n");

    
    printf("Part 5:\n\tYour array in sorted order is: ");
    int tempArray[numProcess];

    // copy the main array in a temp array
    for (int i = 0; i < arraySize; i++) {
        tempArray[i] = intArray[i];
    }

    // Sort the array using a simple selection sort algorithm
    int tempNum;
    for (int i = 0; i < arraySize - 1; i++) {
        for (int j = i + 1; j < arraySize; j++) {
            if (tempArray[j] < tempArray[i]) {
                // Swap the elements
                tempNum = tempArray[i];
                tempArray[i] = tempArray[j];
                tempArray[j] = tempNum;
            }
        }
    }

    // loop through int array and compare with temp array if they are the same then print
    for (int i = 0; i < arraySize; i++) {
        for (int j = 0; j < arraySize; j++) {
            if (i == arraySize - 1){
                if (intArray[j] == tempArray[i]) {
                    printf("[%d] = %d", j, intArray[j]);
                    break;
                }
            } else {
                if (intArray[j] == tempArray[i]) {
                    printf("[%d] = %d, ", j, intArray[j]);
                    break;
                }
            }
        }
    }

    printf("\n");

    // switch first and last array
    printf("Part 6:\n\tYour array with first and last element switched is: ");
    // print the last array, first
    printf("[%d] = %d, ", arraySize - 1, intArray[arraySize - 1]);
    // print array starting at the second
    for (int i = 1; i < arraySize - 1; i++) {
        printf("[%d] = %d, ", i, intArray[i]);
    }
    // print first array, last
    printf("[0] = %d", intArray[0]);


    return 0;
}