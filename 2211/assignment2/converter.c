/* 
A simple converter that allows the user to convert from one unit to another
Student Name: Isaac Tran
Student email: itran9@uwo.ca
Student ID: 251446564
Due Date: 2025-10-07
*/

#include <stdio.h>
#include <stdbool.h>

float gram_ounce(char c) {
    float value;
    float result;
    // Grams to ounce
    if (c == 'G') {
        printf("Please enter a value: ");
        scanf("%f", &value);

        result = value * 0.03527;
    } 
    // Ounce to grams
    else if (c == 'O') {
        printf("Please enter a value: ");
        scanf("%f", &value);

        result = value / 0.03527;
    }
    
    return result;
}

float meter_yard(char c) {
    float value;
    float result;
    // Meter to yard
    if (c == 'M') {
        printf("Please enter a value: ");
        scanf("%f", &value);

        result = value * 1.19599;
    } 
    // Yard to meter
    else if (c == 'Y') {
        printf("Please enter a value: ");
        scanf("%f", &value);

        result = value / 1.19599;
    }
    
    return result;
}

float litre_pint(char c) {
    float value;
    float result;
    // Litre to pint
    if (c == 'L') {
        printf("Please enter a value: ");
        scanf("%f", &value);

        result = value * 2.11338;
    } 
    // Pint to Litre
    else if (c == 'P') {
        printf("Please enter a value: ");
        scanf("%f", &value);

        result = value / 2.11338;
    }
    
    return result;
}

float meter_feet(char c) {
    float value;
    float result;

    // Meter to feet
    if (c == 'M') {
        printf("Please enter a value: ");
        scanf("%f", &value);

        result = value * 3.28084;
    } 
    // Feet to meter
    else if (c == 'F') {
        printf("Please enter a value: ");
        scanf("%f", &value);

        result = value / 3.28084;
    }
    
    return result;
}

int main(void) {

    int choice;
    char direction;
    bool flag = true;

    while (flag) {
        // Prompt the user what conversion they want
        printf("\nEnter a number between 1 - 5:\n");
        printf("1. Grams <-> Ounces\n");
        printf("2. Square Meters <-> Square Yards\n");
        printf("3. Litres <-> Pints\n");
        printf("4. Meters <-> Feet\n");
        printf("5. Quit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        // Switch statement to run the function of desired conversion
        switch(choice) {
            case 1: // Grams and Ounces
                printf("\"G\" Gram to Ouce, \"O\" Ounce to Gram: ");
                scanf(" %c", &direction);
                printf("Your conversion is: %f\n", gram_ounce(direction));
                break;
            case 2: // Square meters and Square Yards
                printf("\"M\" Square Meters to Square Yards, \"Y\" Square Yards to Square Meters: ");
                scanf(" %c", &direction);
                printf("Your conversion is: %f\n", meter_yard(direction));
                break;
            case 3: // Litres and Pints
                printf("\"L\". Litres to Pints, \"P\" Pints to Litres: ");
                scanf(" %c", &direction);
                printf("Your conversion is: %f\n", litre_pint(direction));
                break;
            case 4: // Meter and Feet
                printf("\"M\". Meters to Feet, \"F\" Feet to Meters: ");
                scanf(" %c", &direction);
                printf("Your conversion is: %f\n", meter_feet(direction));
                break;
            case 5: // Quit
                flag = false;
                break;
            default:  // Try again
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

