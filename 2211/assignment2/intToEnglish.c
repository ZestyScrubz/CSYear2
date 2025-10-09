/* 
A simple converter that converts an integer to its word form
Student Name: Isaac Tran
Student email: itran9@uwo.ca
Student ID: 251446564
Due Date: 2025-10-07
*/

#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int num;
    int hundreds_digit, tens_digit, ones_digit;

    // array of all possible number in word
    char *ones[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *tens[] = {"twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    bool flag = true;
    while (flag) {
        // prompt user to enter value
        printf("Please enter a value (1-999), 0 to quit: ");
        scanf("%d", &num);

        // if user inputs 0, exit
        if (num == 0) {
            flag = false;
            break;
        }

        // get the number of each position
        hundreds_digit = num / 100;
        tens_digit = (num / 10) % 10;
        ones_digit = num % 10;

        // if there is a digit in the hundered, get the number and concatinate it
        if (hundreds_digit != 0) {
            printf("%s hundred", ones[hundreds_digit - 1]); // given the number, its in the array - 1 position
            if (tens_digit != 0 || ones_digit != 0) // add and if there are numbers in the tenth and ones
                printf(" and ");
        }

        if (tens_digit == 1) { // it will be in the teens, so given number, corresponding teen number
            printf("%s", teens[ones_digit]);
        } else {
            if (tens_digit >= 2)
                printf("%s", tens[tens_digit - 2]);
            if (tens_digit >= 2 && ones_digit != 0) // if there is a number in the one posistion, add a "-"
                printf("-");
            if (tens_digit != 1 && ones_digit != 0) // add the one number to the end
                printf("%s", ones[ones_digit - 1]);
        }

        printf("\n\n");

    }
    return 0;
}