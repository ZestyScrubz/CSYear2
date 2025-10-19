/* Reverses a series of numbers */
#include <stdio.h>
#define SIZE(arr) ((int) (sizeof(arr) / sizeof(arr[0]))) 
int main(void) {
    int i, numElements;

    printf("Enter the number of elements: ");
    scanf("%d", &numElements);

    // new array with the inputed size
    int array[numElements];

    for (i = 0; i < numElements; i++) {
        scanf("%d", &array[i]); 
    }

    int length = SIZE(array);

    printf("In reverse order:");
    for (i = length - 1; i >= 0; i--) {
        printf(" %d", array[i]); 
    }

    printf("\n"); 
    return 0; 
}