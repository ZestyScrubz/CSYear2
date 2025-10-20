#include <stdio.h>

int main(void) {

    int num;

    int num1, num2, num3;

    printf("Enter a three-digit number: ");
    scanf("%d", &num);

    num1 = num % 10; // right most = smallest
    num2 = (num / 10) % 10;
    num3 = (num / 100) % 10; // left most = largest = 100th

    int result = (num1 * 100) + (num2 * 10) + num3;
    printf("The reversal is: %d", result);
}