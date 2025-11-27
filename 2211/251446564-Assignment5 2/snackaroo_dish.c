/**
 * Program that allows the user to store the information of a dish in a restaurant
 * Student Name: Isaac Tran
 * Student email: itran9@uwo.ca
 * Student ID: 251446564
 * Due Date: 2025-11-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "snackaroo_dish.h"
#include "snackaroo_dish_driver.h"

/*
 * Dishes are stored in-memory in a singly-linked list. This file provides
 * interactive CRUD operations over that list. Nodes are dynamically
 * allocated and freed when erased or when the menu exits.
 */

#define MAX_CHAR 99

static Dish *dishHead = NULL;            /* head of the linked list */
static int dishCount = 0;                /* running count for diagnostics */

/* helpers */
static Dish *find_dish(int code, Dish **out_prev);
static void append_dish(Dish *node);
/* forward declarations for functions implemented below but used earlier */
int eraseDish(void);

int newDish(void) {
    int dishCode;
    char dishName[MAX_CHAR + 1];
    char restaurantName[MAX_CHAR + 1];
    float rating, price;

    printf("Enter dish code: ");
    if (scanf("%d", &dishCode) != 1) {
        printf("Invalid input. Dish code must be an integer.\n");

        // clear input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        return 1;
    }  
    getchar(); // clear newline

    if (dishCode < 0) {
        printf("Dish code must be positive.\n");
        return 1;
    }

    /* reject duplicate codes */
    if (find_dish(dishCode, NULL)) {
        printf("Dish code already exists.\n");
        return 1;
    }

    // prompt the user to enter the dish name (accept spaces)
    printf("Enter name of the dish: ");
    if (!fgets(dishName, sizeof(dishName), stdin)) return 1;
    // if the size is larger than the max size, only grab the first MAX_CHAR characters
    // remove newline if present
    size_t len = strlen(dishName);
    if (len > 0 && dishName[len - 1] == '\n') {
        dishName[len - 1] = '\0';
    } else {
        // NO NEWLINE → means input was too long → flush remainder
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
    dishName[strcspn(dishName, "\n")] = '\0';
    /* dishName already contains the trimmed input */

    // prompt the user to enter the restaurant name (accept spaces)
    printf("Enter name of the restaurant: ");
    if (!fgets(restaurantName, sizeof(restaurantName), stdin)) return 1;
    len = strlen(restaurantName);
    if (len > 0 && restaurantName[len - 1] == '\n') {
        restaurantName[len - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
    restaurantName[strcspn(restaurantName, "\n")] = '\0';
    /* restaurantName already contains the trimmed input */

    // prompt the user for the dish rating (re-prompt until a valid number in [0,10])
    while (1) {
        char buf[128];
        printf("Enter dish rating: ");
        if (!fgets(buf, sizeof(buf), stdin)) return 1;
        if (sscanf(buf, "%f", &rating) != 1) { printf("Invalid rating. Please enter a number between 0 and 10.\n"); continue; }
        if (rating < 0.0f || rating > 10.0f) { printf("Rating must be between 0 and 10.\n"); continue; }
        break;
    }
    // else if the rating is between 0 and 10, then add it to an array but put it in the at the index of dish count so we dont skip any index
    /* rating is validated and available as `rating` */

    // prompt user to enter dish price (re-prompt until a valid positive number)
    while (1) {
        char buf[128];
        printf("Enter dish price: ");
        if (!fgets(buf, sizeof(buf), stdin)) return 1;
        if (sscanf(buf, "%f", &price) != 1) { printf("Invalid price. Please enter a numeric value.\n"); continue; }
        if (price <= 0.0f) { printf("Price must be positive.\n"); continue; }
        break;
    }
    // else if the rating is between 0 and 10, then add it to an array but put it in the at the index of dish count so we dont skip any index
    /* allocate a node and append */
    Dish *node = malloc(sizeof(Dish));
    if (!node) {
        printf("Out of memory.\n");
        return 1;
    }
    node->code = dishCode;
    strncpy(node->name, dishName, MAX_CHAR);
    node->name[MAX_CHAR] = '\0';
    strncpy(node->restaurant, restaurantName, MAX_CHAR);
    node->restaurant[MAX_CHAR] = '\0';
    node->rating = rating;
    node->price = price;
    node->next = NULL;

    append_dish(node);
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

    /* find node */
    Dish *node = find_dish(searchDishCode, NULL);
    if (!node) {
        printf("Dish code is not found in the data base.\n");
        return 1;
    }
    printf("%-12s %-26s %-32s %-26s %s\n", "Dish Code", "Dish Name", "Restaurant Name", "Dish Rating", "Dish Price");
    printf("%-12d %-26s %-32s %-26.1f $%.2f\n", node->code, node->name, node->restaurant, node->rating, node->price);

    return 0;
}

int updateDish(void) {
    int updateDishCode;
    /* input buffers and temps */
    char dishName[MAX_CHAR + 1];
    char restaurantName[MAX_CHAR + 1];
    float rating, price;

    printf("Enter dish code: ");
    scanf("%d", &updateDishCode);
    getchar(); // clear newline

    Dish *node = find_dish(updateDishCode, NULL);
    if (!node) {
        printf("Code is not found in the data base.\n");
        return 1;
    }

    /* prompt and replace fields (validate) */
        printf("Enter name of the dish: ");
        fgets(dishName, MAX_CHAR + 1, stdin);
        size_t len = strlen(dishName);
        if (len > 0 && dishName[len - 1] == '\n') {
            dishName[len - 1] = '\0';
        } else {
            // NO NEWLINE → means input was too long → flush remainder
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
        }
        dishName[strcspn(dishName, "\n")] = '\0';
        strncpy(node->name, dishName, MAX_CHAR);
        node->name[MAX_CHAR] = '\0';

        printf("Enter name of the restaurant: ");
        fgets(restaurantName, MAX_CHAR + 1, stdin);
        len = strlen(restaurantName);
        if (len > 0 && restaurantName[len - 1] == '\n') {
            restaurantName[len - 1] = '\0';
        } else {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
        }
        restaurantName[strcspn(restaurantName, "\n")] = '\0';
        strncpy(node->restaurant, restaurantName, MAX_CHAR);
        node->restaurant[MAX_CHAR] = '\0';

        /* prompt and validate rating (re-prompt on invalid) */
        while (1) {
            char tmp[128];
            printf("Enter dish rating: ");
            if (!fgets(tmp, sizeof(tmp), stdin)) return 1;
            if (sscanf(tmp, "%f", &rating) != 1) { printf("Invalid rating. Try again.\n"); continue; }
            if (rating < 0.0f || rating > 10.0f) { printf("Rating must be between 0.0 and 10.0\n"); continue; }
            node->rating = rating; break;
        }

        /* prompt and validate price (re-prompt on invalid) */
        while (1) {
            char tmp[128];
            printf("Enter dish price: ");
            if (!fgets(tmp, sizeof(tmp), stdin)) return 1;
            if (sscanf(tmp, "%f", &price) != 1) { printf("Invalid price. Try again.\n"); continue; }
            if (price <= 0.0f) { printf("Price must be positive.\n"); continue; }
            node->price = price; break;
        }

    return 0;
}

int listDish(void) {
    // list the dish with spacing
    printf("%-12s %-26s %-32s %-26s %s\n", "Dish Code", "Dish Name", "Restaurant Name", "Dish Rating", "Dish Price");

    /* iterate the list and print nodes */
    Dish *cur = dishHead;
    while (cur) {
        printf("%-12d %-26s %-32s %-26.1f $%.2f\n", cur->code, cur->name, cur->restaurant, cur->rating, cur->price);
        cur = cur->next;
    }

    return 0;
}

/*
 * dish_menu - interactive dish menu exported to top-level `snackaroo.c`
 * This replaces the old `main` and will return to the top-level
 * application when the user enters 'q'. The function frees all nodes
 * before returning.
 */
void dishMenu(void) {
    char operationCode = '\0';

    while (true) {
        printf("\n==================================== Dish Menu =====================================\n");
        printf("(i) Insert Dish, (s) Search Dish, (u) Update Dish, (p) Print All Dishes\n");
        printf("(e) Erase Dish, (p) Dump from File, (r) Restore from File (q) Quit\n");
        printf("=====================================================================================\n");
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
        } else if (operationCode == 'd') {
            /* dish dump (prototype is in snackaroo_dish.h) */
            char filename[256];
            printf("Enter filename to dump to: ");
            if (scanf(" %255s", filename) == 1) dishDump(filename);
        } else if (operationCode == 'r') {
            /* dish restore (prototype is in snackaroo_dish.h) */
            char filename[256];
            printf("Enter filename to restore from: ");
            if (scanf(" %255s", filename) == 1) dishRestore(filename);
        } else if (operationCode == 'q') {
            break;
        } else {
            printf("Unknown operation: %c\n", operationCode);
        }
    }

    /* DO NOT free the global list here — keep dishes available for the
›    * lifetime of the program so the dish_driver module can reference dishes
     * even after returning to the top-level menu. Lists will be cleaned up
     * when the program exits (OS will reclaim memory), or a later explicit
     * cleanup function could be added if desired.
     */
}

/* remove a dish from the list and free memory */
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

    Dish *prev = NULL;
    Dish *node = find_dish(eraseDishCode, &prev);
    if (!node) {
        printf("Dish code %d not found.\n", eraseDishCode);
        return 1;
    }
    /* referential integrity: cannot delete a dish that is referenced by dish_driver entries */
    if (dish_driver_has_dish(eraseDishCode)) { printf("Cannot remove dish: active dish_driver entries exist.\n"); return 1; }
    if (!prev) dishHead = node->next;
    else prev->next = node->next;
    free(node);
    dishCount--;
    printf("Dish with code %d erased successfully.\n", eraseDishCode);
    return 0;
}

int dishDump(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        perror("opening file");
        return 1;
    }

    int count = 0;
    Dish *cur = dishHead;
    while (cur) {
        count++;
        cur = cur->next;
    }

    if (fwrite(&count, sizeof(count), 1, f) != 1) {
        fclose(f);
        return 1;
    }

    cur = dishHead;
    while (cur) {
        int code = cur->code;
        if (fwrite(&code, sizeof(code), 1, f) != 1) break;
        if (fwrite(cur->name, sizeof(cur->name), 1, f) != 1) break;
        if (fwrite(cur->restaurant, sizeof(cur->restaurant), 1, f) != 1) break;
        if (fwrite(&cur->rating, sizeof(cur->rating), 1, f) != 1) break;
        if (fwrite(&cur->price, sizeof(cur->price), 1, f) != 1) break;
        cur = cur->next;
    }

    fclose(f);
    printf("Wrote %d dishes to %s\n", count, filename);
    return 0;
}


int dishRestore(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) { perror("opening file"); return 1; }

    int count = 0;
    if (fread(&count, sizeof(count), 1, f) != 1) {
        fclose(f);
        printf("Empty or invalid file\n");
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        int code;
        char name[100];
        char restaurant[100];
        float rating, price;

        if (fread(&code, sizeof(code), 1, f) != 1) break;
        if (fread(name, sizeof(name), 1, f) != 1) break;
        if (fread(restaurant, sizeof(restaurant), 1, f) != 1) break;
        if (fread(&rating, sizeof(rating), 1, f) != 1) break;
        if (fread(&price, sizeof(price), 1, f) != 1) break;

        /* skip duplicates */
        if (dish_exists(code)) continue;

        /* validate */
        if (rating < 0.0f || rating > 10.0f) {
            printf("Skipping dish %d invalid rating\n", code);
            continue;
        }
        if (price <= 0.0f) {
            printf("Skipping dish %d invalid price\n", code);
            continue;
        }

        Dish *n = malloc(sizeof(Dish));
        if (!n) {
            printf("Out of memory\n");
            fclose(f);
            return 1;
        }
        n->code = code;
        strncpy(n->name, name, sizeof(n->name)-1); n->name[sizeof(n->name)-1] = '\0';
        strncpy(n->restaurant, restaurant, sizeof(n->restaurant)-1); n->restaurant[sizeof(n->restaurant)-1] = '\0';
        n->rating = rating;
        n->price = price;
        n->next = NULL;
        append_dish(n);
        dishCount++;
    }

    fclose(f);
    printf("Restore complete from %s\n", filename);
    return 0;
}

/* --- helper implementations --- */
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

/* Public accessors used by other modules */
Dish *dish_get(int code) { return find_dish(code, NULL); }
int dish_exists(int code) { return dish_get(code) != NULL; }

static void append_dish(Dish *node) {
    if (!dishHead) dishHead = node;
    else {
        Dish *cur = dishHead;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
}
