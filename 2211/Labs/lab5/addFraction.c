#include <stdio.h>

int main(void) {

    int num1Num, num1Den, num2Num, num2Den;
    printf("Enter two fractions seperated by a plus sign: ");
    scanf("%d/%d+%d/%d", &num1Num, &num1Den, &num2Num, &num2Den);

    int numResult = (num1Num * num2Den) + (num2Num * num1Den);
    int denResult = num1Den * num2Den;

    int lowestCommon;
    if (numResult > denResult) {
        lowestCommon = numResult % denResult;
        numResult /= lowestCommon;
        denResult /= lowestCommon;
    } else if (denResult > numResult) {
        lowestCommon = denResult % numResult;
        numResult /= lowestCommon;
        denResult /= lowestCommon;
    } else {
        numResult = 1;
        denResult = 1;
    }

    printf("The sum is: %d/%d", numResult, denResult);
    

    return 0;
}