#include <stdio.h>

#define LEN 3

int sum_two_dimensional_array(const int a[][LEN], int size) {
    const int *p;
    int sum = 0;

    // read the 2d array like a 1d array
    for (p = *a; p < *a + LEN * size; p++) {
        sum += *p;
    }

    return sum;
}

int main() {
    int array[2][3] = { {1, 2, 3}, {4, 5, 6} };

    int row = sizeof(array) / sizeof(array[0]);
    int col = sizeof(array[0]) / sizeof(array[0][0]);

    printf("%d", sum_two_dimensional_array(array, row));
    return 0;
}