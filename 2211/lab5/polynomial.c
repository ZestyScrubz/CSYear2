#include <stdio.h>
#include <math.h>

int main(void) {
    
    int x = 
    printf("Enter a value for x: ");
    scanf("%d", &x);

    int result = 3 * pow(x, 5) + 2 * pow(x, 4) - 5 * pow(x, 3) - pow(x, 2) + 7 * x - 6;
    printf("Result: %d", result);

    return 0;
}