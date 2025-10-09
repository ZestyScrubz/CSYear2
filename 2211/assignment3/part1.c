#include <stdio.h>

int main(void) {
    
    int numProcess;

    printf("Enter the number of integer to process: ");
    scanf("%d", &numProcess);

    while (numProcess < 5 || numProcess > 12) {
        printf("Enter the number of integer to process: ");
        scanf("%d", &numProcess);
    }

    int intArray[numProcess];

    printf("There is enough room in your array for %d integers (%d bytes)", numProcess, sizeof(intArray));
    printf("\nPlease enter your integers separeated by space: ");
    
    int arraySize = sizeof(intArray) / sizeof(intArray[0]);

    for (int i = 0; i < arraySize; i++) {
        scanf("%d", &intArray[i]);
    }

    // start at index 0 and iterate up to the last index
    printf("Part 1:\n\tYour array is: ");
    for (int i = 0; i < arraySize; i++) {
        printf("[%d] = %d, ", i, intArray[i]);
    }
    printf("\n");

    // start at the last index of the array and iterate down to 0
    printf("Part 2:\n\tYour array in reverse is: ");
    for (int i = arraySize - 1; i >= 0; i--) {
        printf("[%d] = %d, ", i, intArray[i]);
    }
    printf("\n");

    // loop through array and take the mod of the value and print even
    printf("Part 3:\n\tThe even elements in the array is: ");
    for (int i = 0; i < arraySize; i++) {
        if (intArray[i] % 2 == 0) {
            printf("[%d] = %d, ", i, intArray[i]);
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

    // find the smallest number
    printf("Part 5:\n\tYour array in sorted order is: ");
    int smallest = intArray[0]; // make the smallest number the first index so we can compare
    for (int i = 0; i < arraySize; i++) {
        if (intArray[i] < smallest) {
            smallest = i;
        }
    }
    printf("[%d] = %d, ", smallest, intArray[smallest]);
    // find the next smallest number
    for (int i = 0; i < arraySize - 1; i++) {
        for (int j = 0; j < arraySize; j++) {
            if (intArray[j] < smallest) {

            }
        }
    }
    printf("\n");

    // switch first and last array
    printf("Part 6:\n\tYYour array with first and last element switched is: ");
    // print the last array, first
    printf("[%d] = %d,", arraySize - 1, intArray[arraySize - 1]);
    // print array starting at the second
    for (int i = 1; i < arraySize - 1; i++) {
        printf("[%d] = %d", i, intArray[i]);
    }
    // print first array, last
    printf("[0] = %d", intArray[0]);


    return 0;
}