
// global constants for driver data
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_DRIVER_CHAR 50
#define MAX_LICENCE_CHAR 16
#define MIN_LICENCE_CHAR 2

typedef struct Driver {
    int code;
    char name[MAX_DRIVER_CHAR + 1];
    int vehicleColour; // 0-6
/*
 * snackaroo_driver.c
 * Driver management for Snackaroo.
 *
 * The drivers database is an in-memory linked list of Driver nodes. Each
 * node contains a unique numeric code, the driver's name, vehicle colour
 * (stored as an integer index 0..6), and an alphanumeric licence plate.
 * This module provides interactive CRUD operations and frees any
 * allocated nodes when leaving the driver menu.
 */

    char licencePlate[MAX_LICENCE_CHAR + 1];
    struct Driver *next;
} Driver;

static Driver *driverHead = NULL;
static int driverCount = 0;

// helper: find node and previous by code
static Driver *find_driver(int code, Driver **out_prev) {
    Driver *prev = NULL;
    Driver *cur = driverHead;
    while (cur) {
        if (cur->code == code) {
            if (out_prev) *out_prev = prev;
            return cur;
        }
/*
 * find_driver - locate a driver node by its unique code
 * @code: numeric driver key to find
 * @out_prev: if non-NULL receives the previous node pointer (or NULL when none)
 *
 * Returns the matching Driver* or NULL if not found.
 */
        prev = cur;
        cur = cur->next;
    }
    if (out_prev) *out_prev = NULL;
    return NULL;
}

// append to list (at tail)
static void append_driver(Driver *node) {
    if (!driverHead) {
        driverHead = node;
    } else {
        Driver *cur = driverHead;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
/*
 * append_driver - attach node to the tail of the drivers list
 * Expects node->next == NULL and walks to the tail to attach it. If the
 * list is empty the node becomes the new head.
 */
}

// CRUD function declarations
int newDriver(void);
int searchDriver(void);
int updateDriver(void);
int listDriver(void);
int eraseDriver(void);

int driver_menu(void) {
    char operationCode = '\0';
/* Function declarations exported as CLI operations */

    while (true) {
        printf("Enter operation: ");
        if (scanf(" %c", &operationCode) != 1) break;

        if (operationCode == 'i') {
/*
 * driver_menu - interactive menu loop for driver CRUD operations
 * Prompts for single-character commands and runs new/search/update/list/erase
 * until the user enters 'q', at which point the menu frees all remaining
 * nodes and returns.
 */
            newDriver();
        } else if (operationCode == 's') {
            searchDriver();
        } else if (operationCode == 'u') {
            updateDriver();
        } else if (operationCode == 'p') {
            listDriver();
        } else if (operationCode == 'e') {
            eraseDriver();
        } else if (operationCode == 'q') {
            break;
        } else {
            printf("Unknown operation: %c\n", operationCode);
        }
    }

    // free list
    Driver *cur = driverHead;
    while (cur) {
        Driver *next = cur->next;
        free(cur);
        cur = next;
    }

    return 0;
}


int newDriver(void) {
    /* no fixed maximum; linked list can grow as needed */

    int driverCode;
    char driverName[MAX_DRIVER_CHAR + 1];
    char licence[MAX_LICENCE_CHAR + 1];
    int colour;
/*
 * newDriver - interactively create and append a new driver
 * Validates inputs before allocation. Returns 0 on success, 1 on error.
 */

    printf("Enter Driver Code: ");
    if (scanf("%d", &driverCode) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (driverCode < 0) {
        printf("Driver code must be positive.\n");
        return 1;
    }

    if (find_driver(driverCode, NULL)) {
        printf("Driver code already exists.\n");
        return 1;
    }

    printf("Enter name of the driver: ");
    if (scanf("%50s", driverName) != 1) {
        printf("Invalid name.\n");
        return 1;
    }

    printf("Enter the colour of the vehicle (0-6): ");
    if (scanf("%d", &colour) != 1) {
        printf("Invalid colour.\n");
        return 1;
    }
    if (colour < 0 || colour > 6) {
        printf("Invalid vehicle colour.\n");
        return 1;
    }

    printf("Enter licence plate of the driver: ");
    if (scanf("%15s", licence) != 1) {
        printf("Invalid licence plate.\n");
        return 1;
    }
    size_t len = strlen(licence);
    if (len < MIN_LICENCE_CHAR || len >= MAX_LICENCE_CHAR) {
        printf("Licence plate length invalid.\n");
        return 1;
    }
    for (size_t i = 0; i < len; i++) {
        if (!isalnum((unsigned char)licence[i])) {
            printf("Licence plate must be alphanumeric.\n");
            return 1;
        }
    }

    Driver *node = malloc(sizeof(Driver));
    if (!node) {
        printf("Out of memory.\n");
        return 1;
    }
    node->code = driverCode;
    strncpy(node->name, driverName, MAX_DRIVER_CHAR);
    node->name[MAX_DRIVER_CHAR] = '\0';
    node->vehicleColour = colour;
    strncpy(node->licencePlate, licence, MAX_LICENCE_CHAR - 1);
    node->licencePlate[MAX_LICENCE_CHAR - 1] = '\0';
    node->next = NULL;

    append_driver(node);
    driverCount++;
    printf("Driver %d added.\n", driverCode);
    return 0;
}

int searchDriver(void) {
    int searchDriverCode;
    printf("Enter driver code: ");
    if (scanf("%d", &searchDriverCode) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    Driver *node = find_driver(searchDriverCode, NULL);
    if (!node) {
        printf("Driver code not found.\n");
        return 1;
    }
    printf("Driver Code: %d\n", node->code);
    printf("Driver Name: %s\n", node->name);
    printf("Vehicle Colour: %d\n", node->vehicleColour);
    printf("Licence Plate: %s\n", node->licencePlate);
    return 0;
}

int updateDriver(void) {
    int updateDriverCode;
    printf("Enter driver code: ");
    if (scanf("%d", &updateDriverCode) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    Driver *node = find_driver(updateDriverCode, NULL);
    if (!node) {
        printf("Driver code not found.\n");
        return 1;
    }

    char driverName[MAX_DRIVER_CHAR + 1];
    int colour;
    char licence[MAX_LICENCE_CHAR + 1];

    printf("Enter name of the driver: ");
    if (scanf("%50s", driverName) == 1) {
        strncpy(node->name, driverName, MAX_DRIVER_CHAR);
        node->name[MAX_DRIVER_CHAR] = '\0';
    }

    printf("Enter vehicle colour (0-6): ");
    if (scanf("%d", &colour) == 1) {
        if (colour < 0 || colour > 6) {
            printf("Invalid vehicle colour.\n");
            return 1;
        }
        node->vehicleColour = colour;
    }

    printf("Enter licence plate: ");
    if (scanf("%15s", licence) == 1) {
        size_t len = strlen(licence);
        if (len < MIN_LICENCE_CHAR || len >= MAX_LICENCE_CHAR) {
            printf("Licence plate length invalid.\n");
            return 1;
        }
        for (size_t i = 0; i < len; i++) {
            if (!isalnum((unsigned char)licence[i])) {
                printf("Licence plate must be alphanumeric.\n");
                return 1;
            }
        }
        strncpy(node->licencePlate, licence, MAX_LICENCE_CHAR - 1);
        node->licencePlate[MAX_LICENCE_CHAR - 1] = '\0';
    }

    printf("Driver %d updated.\n", node->code);
    return 0;
}

int listDriver(void) {
    printf("%-12s %-26s %-16s %s\n", "Driver Code", "Driver Name", "Vehicle Colour", "Licence Plate");
    Driver *cur = driverHead;
    while (cur) {
        printf("%-12d %-26s %-16d %s\n", cur->code, cur->name, cur->vehicleColour, cur->licencePlate);
        cur = cur->next;
    }
    return 0;
}

int eraseDriver(void) {
    int eraseDriverCode;
    printf("Enter driver code: ");
    if (scanf("%d", &eraseDriverCode) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    Driver *prev = NULL;
    Driver *node = find_driver(eraseDriverCode, &prev);
    if (!node) {
        printf("Driver code not found.\n");
        return 1;
    }
    if (!prev) {
        driverHead = node->next;
    } else {
        prev->next = node->next;
    }
    free(node);
    driverCount--;
    printf("Driver code %d erased.\n", eraseDriverCode);
    return 0;
}
