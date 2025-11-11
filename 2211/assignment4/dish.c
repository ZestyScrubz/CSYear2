#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Globle contanst for the maximum number of allowed dishes, and maximum number of character for the name
#define MAX_DISH_CODE 100
#define MAX_DISH_CHAR 99
#define MAX_NO_DISH 100

int dishCount = 0;
int dishCodes[MAX_DISH_CODE];
char dishes[MAX_NO_DISH][MAX_DISH_CHAR + 1];
char restaurants[MAX_NO_DISH][MAX_DISH_CHAR + 1];
float ratings[MAX_NO_DISH];
float prices[MAX_NO_DISH];


int main(void) {

    char operationCode;

    while (operationCode != 'q') {
        printf("Enter operation code: ");
        scanf(" %c", &operationCode);

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

int newDish(void) {
    int dishCode;
    char dishName[MAX_DISH_CHAR + 1];
    char restaurantName[MAX_DISH_CHAR + 1];
    float rating, price;

    printf("Enter dish code: ");
    scanf("%d", &dishCode);

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

    printf("Enter name of the dish: ");
    scanf("%s", dishName);
    strcpy(dishes[dishCount], dishName);

    printf("Enter name of the restaurant: ");
    scanf("%s", restaurantName);
    strcpy(restaurants[dishCount], restaurantName);

    printf("Enter dish rating: ");
    scanf("%f", &rating);
    if (rating < 0 || rating > 10) {
        printf("Error: Rating must be between 0 and 10.\n");
        return 1;
    }
    ratings[dishCount] = rating;

    printf("Enter dish price: ");
    scanf("%f", &price);
    if (price <= 0) {
        printf("Error: Price must be positive.\n");
        return 1;
    }
    prices[dishCount] = price;

    dishCount++;
    return 0;
}

int searchDish(void) {
    
    int searchDishCode;

    printf("Enter Dish Code: ");
    scanf("%d", &searchDishCode);

    // iterate through the dish code array to find if there exists a code
    for (int i = 0; i < dishCount; i++) {
        if (dishCodes[i] == searchDishCode) {
            printf("%-12s %-26s %-32s %-26s %s\n", "Dish Code", "Dish Name", "Restaurant Name", "Dish Rating", "Dish Price");
            printf("%-12d %-26s %-32s %-26.1f $%.2f\n", dishCodes[searchDishCode], dishes[searchDishCode], restaurants[searchDishCode], ratings[searchDishCode], prices[searchDishCode]);

            return 0;
        } 
    }
    
    return 0;
}

int updateDish(void) {

    int updateDishCode;
    bool found = false;

    int dishCode;
    char dishName[MAX_DISH_CHAR + 1];
    char restaurantName[MAX_DISH_CHAR + 1];
    float rating, price;

    printf("Enter dish code: ");
    scanf("%d", &updateDishCode);

    for (int i = 0; i < dishCount; i++) {
        if (dishCodes[i] == updateDishCode) found = true;
    }

    if (found) {
        

        printf("Enter name of the dish: ");
        scanf("%s", dishName);
        strcpy(dishes[updateDishCode], dishName);

        printf("Enter name of the restaurant: ");
        scanf("%s", restaurantName);
        strcpy(restaurants[updateDishCode], restaurantName);

        printf("Enter dish rating: ");
        scanf("%f", &rating);
        if (rating < 0 || rating > 10) {
            printf("Rating must be between 0.0 and 10.0\n");
            return 1;
        }
        ratings[updateDishCode] = rating;

        printf("Enter dish price: ");
        scanf("%f", &price);
        if (price <= 0) {
            printf("Price must be positive.\n");
            return 1;
        }
        prices[updateDishCode] = price;
    }

    return 0;
}

int listDish(void) {

    printf("%-12s %-26s %-32s %-26s %s\n", "Dish Code", "Dish Name", "Restaurant Name", "Dish Rating", "Dish Price");

    for (int i = 0; i < dishCount; i++) {
        printf("%-12d %-26s %-32s %-26.1f $%.2f\n", dishCodes[i], dishes[i], restaurants[i], ratings[i], prices[i]);
    }

    return 0;
}