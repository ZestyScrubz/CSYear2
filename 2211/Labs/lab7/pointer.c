#include <stdio.h>

int sum_array(const int *a, int size) { 
  
    int sum = 0;
    const int *p; // p points to an address in the array
    for (p = a; p < a + size; p++) {
        sum += (*p); 
    }
    return sum; 
}

int main(void) {
    int array[] = {1, 2, 3, 4, 5};

    int arraySize = sizeof(array) / sizeof(array[0]);
    int sum = sum_array(array, arraySize);
    printf("%d", sum);

    return 0;
}