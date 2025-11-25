

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// global constants for dish data
#define MAX_DISH_CHAR 99
#define MIN_RATING 0.0f
#define MAX_RATING 10.0f

/* Dish node stored in a singly-linked list */
typedef struct Dish {
    int code;
    char name[MAX_DISH_CHAR + 1];
    char restaurant[MAX_DISH_CHAR + 1];
    float rating;
    float price;
    struct Dish *next;
} Dish;

static Dish *dishHead = NULL;
static int dishCount = 0; // retained for diagnostics / limits if desired

// helpers
/*
 * find_dish - locate a dish node by its code
 * @code: numeric dishes code to search for
 * @out_prev: optional out-parameter returning the previous node (or NULL if none)
 *
 * Returns pointer to the matching node or NULL if not found.
 */
static Dish *find_dish(int code, Dish **out_prev) {
    Dish *prev = NULL;
    Dish *cur = dishHead;
    while (cur) {
        if (cur->code == code) {
            if (out_prev) *out_prev = prev;
            return cur;
        }
        prev = cur;
        cur = cur->next;
    }
    if (out_prev) *out_prev = NULL;
    return NULL;
}

/*
 * append_dish - append a node to the tail of the list
 * The function expects `node->next` to be NULL and simply walks the
 * list to attach the node at the end. If the list is empty the node
 * becomes the new head.
 */
static void append_dish(Dish *node) {
    if (!dishHead) {
        dishHead = node;
    } else {
        Dish *cur = dishHead;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
}

/*
 * newDish - interactive insertion of a new dish
 *
 * Prompts the user for fields, validates them and creates a new
 * Dish node. Duplicate codes are rejected. On success a new node is
 * appended to the list and dishCount is incremented.
 *
 * Returns 0 on success, 1 on invalid input or when allocation fails.
 */
int newDish(void) {
    int dishCode;
    char dishName[MAX_DISH_CHAR + 1];
    char restaurantName[MAX_DISH_CHAR + 1];
    float rating, price;

    printf("Enter dish code: ");
    if (scanf("%d", &dishCode) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (dishCode < 0) {
        printf("Dish code must be positive.\n");
        return 1;
    }

    // Check for duplicate dish code
    /* reject duplicate codes */
    if (find_dish(dishCode, NULL)) {
        printf("Dish code already exists.\n");
        return 1;
    }

    printf("Enter name of the dish: ");
    if (scanf("%99s", dishName) != 1) {
        printf("Invalid name.\n");
        return 1;
    }

    printf("Enter name of the restaurant: ");
    if (scanf("%99s", restaurantName) != 1) {
        printf("Invalid restaurant name.\n");
        return 1;
    }

    printf("Enter dish rating: ");
    scanf("%f", &rating);
    if (rating < 0 || rating > 10) {
        printf("Error: Rating must be between 0 and 10.\n");
        return 1;
    }
    

    printf("Enter dish price: ");
    scanf("%f", &price);
    if (price <= 0) {
        printf("Error: Price must be positive.\n");
        return 1;
    }
    // create node and append
    /* create node and append to the list */
    Dish *node = malloc(sizeof(Dish));
    if (!node) {
        printf("Out of memory.\n");
        return 1;
    }
    node->code = dishCode;
    strncpy(node->name, dishName, MAX_DISH_CHAR);
    node->name[MAX_DISH_CHAR] = '\0';
    strncpy(node->restaurant, restaurantName, MAX_DISH_CHAR);
    node->restaurant[MAX_DISH_CHAR] = '\0';
    node->rating = rating;
    node->price = price;
    node->next = NULL;

    append_dish(node);
    dishCount++;
    return 0;
}

int searchDish(void) {
    
    int searchDishCode;

    printf("Enter Dish Code: ");
    scanf("%d", &searchDishCode);

    /* lookup the node */
    Dish *node = find_dish(searchDishCode, NULL);
    if (!node) {
        printf("Dish code not found.\n");
        return 1;
    }
    printf("%-12s %-26s %-32s %-26s %s\n", "Dish Code", "Dish Name", "Restaurant Name", "Dish Rating", "Dish Price");
    printf("%-12d %-26s %-32s %-26.1f $%.2f\n", node->code, node->name, node->restaurant, node->rating, node->price);
    return 0;
    
    return 0;
}

int updateDish(void) {

    int updateDishCode;
    char dishName[MAX_DISH_CHAR + 1];
    char restaurantName[MAX_DISH_CHAR + 1];
    float rating, price;

    printf("Enter dish code: ");
    scanf("%d", &updateDishCode);

    /* find node to update */
    Dish *node = find_dish(updateDishCode, NULL);
    if (!node) {
        printf("Dish code not found.\n");
        return 1;
    }

    printf("Enter name of the dish: ");
    if (scanf("%99s", dishName) == 1) {
        strncpy(node->name, dishName, MAX_DISH_CHAR);
        node->name[MAX_DISH_CHAR] = '\0';
    }

    printf("Enter name of the restaurant: ");
    if (scanf("%99s", restaurantName) == 1) {
        strncpy(node->restaurant, restaurantName, MAX_DISH_CHAR);
        node->restaurant[MAX_DISH_CHAR] = '\0';
    }

    printf("Enter dish rating: ");
    if (scanf("%f", &rating) == 1) {
        if (rating < MIN_RATING || rating > MAX_RATING) {
            printf("Rating must be between 0.0 and 10.0\n");
            return 1;
        }
        node->rating = rating;
    }

    printf("Enter dish price: ");
    if (scanf("%f", &price) == 1) {
        if (price <= 0) {
            printf("Price must be positive.\n");
            return 1;
        }
        node->price = price;
    }

    return 0;
}

/*
 * listDish - print a formatted table of all dishes
 *
 * Iterates the linked list printing each node. If there are no dishes
 * this prints only the header.
 */
int listDish(void) {
    printf("%-12s %-26s %-32s %-26s %s\n", "Dish Code", "Dish Name", "Restaurant Name", "Dish Rating", "Dish Price");
    Dish *cur = dishHead;
    while (cur) {
        printf("%-12d %-26s %-32s %-26.1f $%.2f\n", cur->code, cur->name, cur->restaurant, cur->rating, cur->price);
        cur = cur->next;
    }
    return 0;
}

/*
If the dish code is found, erase the dish safely by removing the element from the linked list and freeing the memory
If the dish code is not found, tell the user the error. The user can try again or you can return the user to the main prompt*/
int eraseDish(void) {
    if (!dishHead) {
        printf("Database is empty. Nothing to erase.\n");
        return 1;
    }
    int eraseDishCode;
    printf("Enter dish code to erase: ");
    if (scanf("%d", &eraseDishCode) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    /* find node and previous pointer, then unlink and free */
    Dish *prev = NULL;
    Dish *node = find_dish(eraseDishCode, &prev);
    if (!node) {
        printf("Dish code %d not found.\n", eraseDishCode);
        return 1;
    }
    if (!prev) dishHead = node->next;
    else prev->next = node->next;
    free(node);
    dishCount--;
    printf("Dish with code %d erased successfully.\n", eraseDishCode);
    return 0;
}

int dish_menu(void) {
    char operationCode = '\0';

    while (true) {
        printf("Enter operation: ");
        if (scanf(" %c", &operationCode) != 1) break;

        if (operationCode == 'i') {
            newDish();
        } else if (operationCode == 's') {
            searchDish();
        } else if (operationCode == 'u') {
            updateDish();
        } else if (operationCode == 'p') {
            listDish();
        } else if (operationCode == 'e') {
            eraseDish();
        } else if (operationCode == 'q') {
            break;
        } else {
            printf("Unknown operation: %c\n", operationCode);
        }
    }

    // free list before returning
    /* free entire list before returning */
    Dish *cur = dishHead;
    while (cur) {
        Dish *next = cur->next;
        free(cur);
        cur = next;
    }

    return 0;
}