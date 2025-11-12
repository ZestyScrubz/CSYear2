/**
 * Program that allows the user to store the information of a dish in a restaurant
 * Student Name: Isaac Tran
 * Student email: itran9@uwo.ca
 * Student ID: 251446564
 * Due Date: 2025-11-11
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// globle contanst for the maximum number of allowed dishes, and maximum number of character for the name
#define MAX_DISH_CODE 100
#define MAX_CHAR 99
#define MAX_NO_DISH 100

int dishCount = 0;
int dishCodes[MAX_NO_DISH];
char dishes[MAX_NO_DISH][MAX_CHAR + 1];
char restaurants[MAX_NO_DISH][MAX_CHAR + 1];
float ratings[MAX_NO_DISH];
float prices[MAX_NO_DISH];

int newDish(void) {
    int dishCode;
    char dishName[MAX_CHAR + 1];
    char restaurantName[MAX_CHAR + 1];
    float rating, price;

    printf("Enter dish code: ");
    scanf("%d", &dishCode);
    getchar(); // clear newline

    if (dishCode < 0) {
        printf("Dish code must be positive.\n");
        return 1;
    }

    // Check for duplicate dish code
    for (int i = 0; i < dishCount; i++) {
        if (dishCodes[i] == dishCode) {
            printf("Dish code already exists.\n");
            return 1;
        }
    }

    dishCodes[dishCount] = dishCode;

    // prompt the user to enter the dish name
    printf("Enter name of the dish: ");
    fgets(dishName, MAX_CHAR + 1, stdin);
    dishName[strcspn(dishName, "\n")] = '\0';
    // copy the dish name into an array that will hold the inputed string, with maximum of MAX_CHAR amount of character
    strncpy(dishes[dishCount], dishName, MAX_CHAR);

    // prompt the user to enter the restaurant name
    printf("Enter name of the restaurant: ");
    fgets(restaurantName, MAX_CHAR + 1, stdin);
    restaurantName[strcspn(restaurantName, "\n")] = '\0';
    // copy the dish name into an array that will hold the inputed string, with maximum of MAX_CHAR amount of character
    strncpy(restaurants[dishCount], restaurantName, MAX_CHAR);

    // prompt the user for the dish rating
    printf("Enter dish rating: ");
    scanf("%f", &rating);
    // if the dish rating is not between 0 and 10, then go back to main page
    if (rating < 0 || rating > 10) {
        printf("Rating must be between 0 and 10.\n");
        return 1;
    }
    // else if the rating is between 0 and 10, then add it to an array but put it in the at the index of dish count so we dont skip any index
    ratings[dishCount] = rating;

    // prompt user to enter dish price
    printf("Enter dish price: ");
    scanf("%f", &price);
    // if the price is not a positive float with two digits after then return back to main menu
    if (price <= 0.0f || ((int)(price * 100 + 0.5) != (int)(price * 100))) {
        printf("Price must be positive and have two digits after the decimal.\n");
        return 1;
    }
    // else if the rating is between 0 and 10, then add it to an array but put it in the at the index of dish count so we dont skip any index
    prices[dishCount] = price;

    // update the number of dishes we have in the array
    dishCount++;
    return 0;
}

/**
 * Search for a dish in the database and print it out (using the command s)
 */
int searchDish(void) {
    int searchDishCode;

    printf("Enter Dish Code: ");
    scanf("%d", &searchDishCode);

    // iterate through the dish code array to find if there exists a code
    int index = -1; // assume not found
    for (int i = 0; i < dishCount; i++) {
        if (dishCodes[i] == searchDishCode) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        printf("%-12s %-26s %-32s %-26s %s\n", "Dish Code", "Dish Name", "Restaurant Name", "Dish Rating", "Dish Price");
        printf("%-12d %-26s %-32s %-26.1f $%.2f\n",
               dishCodes[index], dishes[index], restaurants[index], ratings[index], prices[index]);
    } else {
        // this code will only run if we dont find the dish code
        printf("Dish code is not found in the data base.\n");
    }

    return 0;
}

int updateDish(void) {
    int updateDishCode;
    bool found = false;

    char dishName[MAX_CHAR + 1];
    char restaurantName[MAX_CHAR + 1];
    float rating, price;

    printf("Enter dish code: ");
    scanf("%d", &updateDishCode);
    getchar(); // clear newline

    // iterate through all the dishes to see if the code is in the data base
    int index = -1;
    for (int i = 0; i < dishCount; i++) {
        if (dishCodes[i] == updateDishCode) {
            index = i;
            found = true;
            break;
        }
    }

    // if the code is in the data base prompt the user to update all info
    if (found) {
        printf("Enter name of the dish: ");
        fgets(dishName, MAX_CHAR + 1, stdin);
        dishName[strcspn(dishName, "\n")] = '\0';
        strncpy(dishes[index], dishName, MAX_CHAR);

        printf("Enter name of the restaurant: ");
        fgets(restaurantName, MAX_CHAR + 1, stdin);
        restaurantName[strcspn(restaurantName, "\n")] = '\0';
        strncpy(restaurants[index], restaurantName, MAX_CHAR);

        printf("Enter dish rating: ");
        scanf("%f", &rating);
        if (rating < 0 || rating > 10) {
            printf("Rating must be between 0.0 and 10.0\n");
            return 1;
        }
        ratings[index] = rating;

        printf("Enter dish price: ");
        scanf("%f", &price);
        if (price <= 0.0f || ((int)(price * 100 + 0.5) != (int)(price * 100))) {
            printf("Price must be positive and have two decimal digits.\n");
            return 1;
        }
        prices[index] = price;
    } else {
        printf("Code is not found in the data base.\n");
        return 1;
    }

    return 0;
}

int listDish(void) {
    // list the dish with spacing
    printf("%-12s %-26s %-32s %-26s %s\n", "Dish Code", "Dish Name", "Restaurant Name", "Dish Rating", "Dish Price");

    // iterate through all the dish and print them out
    for (int i = 0; i < dishCount; i++) {
        printf("%-12d %-26s %-32s %-26.1f $%.2f\n",
               dishCodes[i], dishes[i], restaurants[i], ratings[i], prices[i]);
    }

    return 0;
}

int main(void) {
    char operationCode = ' ';

    while (operationCode != 'q') {
        printf("Enter operation code: ");
        scanf(" %c", &operationCode);
        getchar(); // clear newline

        if (operationCode == 'i') {
            newDish();
        } else if (operationCode == 's') {
            searchDish();
        } else if (operationCode == 'u') {
            updateDish();
        } else if (operationCode == 'p') {
            listDish();
        }
    }

    return 0;
}
