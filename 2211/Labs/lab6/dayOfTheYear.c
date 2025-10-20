#include <stdio.h>

int day_of_year(int month, int day, int year) {

    // Days in each month for a non-leap year
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check if the year is a leap year
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
        days_in_month[1] = 29; // February has 29 days in a leap year
    }

    // Calculate the day of the year
    int day_of_year = 0;
    for (int i = 0; i < month - 1; i++) {
        day_of_year += days_in_month[i];
    }
    day_of_year += day;

    return day_of_year;
}

int main(void) {

    int month, day, year;

    printf("Enter date: ");
    scanf("%d/%d/%d", &month, &day, &year);

    int daysInYear = day_of_year(month, day, year);

    printf("%d", daysInYear);
    return daysInYear;
}


