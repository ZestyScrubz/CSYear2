#include <stdio.h>
int main(void) {
    int days, starting_day;
    printf("Enter number of days in month: ");
    scanf("%d", &days);
    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    scanf("%d", &starting_day);

    // if the starting day is more than 7, then just -7 to see what the day it would land on
    // eg 8-7 would be sunday
    if (starting_day > 7) {
        starting_day -= 7;
    }

    /* Create spaces for the amount of starting days */
    for (int i = 1; i < starting_day; i++) {
        printf("    ");
    }

    /* Print the days of the month */
    for (int i = 1; i <= days; i++) {
        printf("%2d", i);
        printf("  ");

        // when it reaches the 7th day start on a new line
        // i - 1 because starting day is 1-7 and were trying to figure out if the whole 7 col has been filled
        if (((i - 1) + starting_day) % 7 == 0) printf("\n");
    }

    return 0;
}