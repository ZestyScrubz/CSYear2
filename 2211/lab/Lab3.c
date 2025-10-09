#include <stdio.h>
int main(void) {
    int num1, num2, num3, num4, largest, smallest;
    printf("Enter four integers: ");
    scanf("%d %d %d %d", &num1, &num2, &num3, &num4);

    if (num1 >= num2) {
        largest = num1;
        smallest = num2;
    }
    if (num3 >= largest) {
        largest = num3;
    }
    if (num4 >= largest) {
        largest = num4;
    }
    if (num3 <= smallest) {
        smallest = num3;
    }
    if (num4 <= smallest) {
        smallest = num4;
    }

    printf("Largest: %d\n", largest);
    printf("Smallest: %d\n", smallest);

    return 0;
}