/**
 * Program that allows the user to store the information of a driver in a licencePlate
 * Student Name: Isaac Tran
 * Student email: itran9@uwo.ca
 * Student ID: 251446564
 * Due Date: 2025-11-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "snackaroo_driver.h"
#include "snackaroo_dish_driver.h"

/*
 * driveres are stored in-memory in a singly-linked list. This file provides
 * interactive CRUD operations over that list. Nodes are dynamically
 * allocated and freed when erased or when the menu exits.
 */

#define MAX_CHAR 49
#define MAX_LICENCE_CHAR 8
#define MIN_LICENCE_CHAR 2

static Driver *driverHead = NULL;            /* head of the linked list */
static int driverCount = 0;                /* running count for diagnostics */

/* helpers */
static Driver *find_driver(int code, Driver **out_prev);
static void append_driver(Driver *node);
/* forward declarations for functions implemented below but used earlier */
int eraseDriver(void);

int newDriver(void) {
    int driverCode;
    char driverName[MAX_CHAR + 1];
    char licencePlate[MAX_LICENCE_CHAR + 1];
    int vehicleColour;

    printf("Enter driver code: ");
    if (scanf("%d", &driverCode) != 1) {
        printf("Invalid input. driver code must be an integer.\n");

        // clear input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        return 1;
    }  
    getchar(); // clear newline

    if (driverCode < 0) {
        printf("driver code must be positive.\n");
        return 1;
    }

    /* reject duplicate codes */
    if (find_driver(driverCode, NULL)) {
        printf("Driver code already exists.\n");
        return 1;
    }

    // prompt the user to enter the driver name (accept spaces)
    printf("Enter name of the driver: ");
    if (!fgets(driverName, sizeof(driverName), stdin)) return 1;
    // if the size is larger than the max size, only grab the first MAX_CHAR characters
    // remove newline if present
    size_t len = strlen(driverName);
    if (len > 0 && driverName[len - 1] == '\n') {
        driverName[len - 1] = '\0';
    } else {
        // NO NEWLINE → means input was too long → flush remainder
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
    driverName[strcspn(driverName, "\n")] = '\0';
    /* driverName already contains the trimmed input */

    // prompt the user to enter the licencePlate name (accept spaces)
    printf("Enter name of the licence plate: ");
    if (!fgets(licencePlate, sizeof(licencePlate), stdin)) return 1;
    len = strlen(licencePlate);
    if (len > 0 && licencePlate[len - 1] == '\n') {
        licencePlate[len - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
    licencePlate[strcspn(licencePlate, "\n")] = '\0';
    /* licencePlate already contains the trimmed input */

    // prompt the user for the driver vehicleColour (re-prompt until a valid number in [0,10])
    while (1) {
        char buf[128];
        printf("Enter driver vehicleColour: ");
        if (!fgets(buf, sizeof(buf), stdin)) return 1;
        if (sscanf(buf, "%d", &vehicleColour) != 1) { printf("Invalid vehicle colour. Please enter a number between 0 and 10.\n"); continue; }
        if (vehicleColour < 0.0f || vehicleColour > 10.0f) { printf("vehicle colour must be between 0 and 10.\n"); continue; }
        break;
    }
    // else if the vehicleColour is between 0 and 10, then add it to an array but put it in the at the index of driver count so we dont skip any index
    /* vehicleColour is validated and available as `vehicleColour` */

    // else if the vehicleColour is between 0 and 10, then add it to an array but put it in the at the index of driver count so we dont skip any index
    /* allocate a node and append */
    Driver *node = malloc(sizeof(Driver));
    if (!node) {
        printf("Out of memory.\n");
        return 1;
    }
    node->code = driverCode;
    strncpy(node->name, driverName, MAX_CHAR);
    node->name[MAX_CHAR] = '\0';
    strncpy(node->licencePlate, licencePlate, MAX_LICENCE_CHAR);
    node->licencePlate[MAX_LICENCE_CHAR] = '\0';
    node->vehicleColour = vehicleColour;
    node->next = NULL;

    append_driver(node);
    driverCount++;
    return 0;
}

int searchDriver(void) {
    int searchDriverCode;

    printf("Enter Dish Code: ");
    scanf("%d", &searchDriverCode);

    /* find node */
    Driver *node = find_driver(searchDriverCode, NULL);
    if (!node) {
        printf("Dish code is not found in the data base.\n");
        return 1;
    }
    printf("%-12s %-26s %-32s %-26s %s\n", "Dish Code", "Dish Name", "Restaurant Name", "Dish Rating", "Dish Price");
    printf("%-12d %-26s %-32s %-26.1d\n", node->code, node->name, node->licencePlate, node->vehicleColour);

    return 0;
}

int updateDriver(void) {
    int updateDriverCode;
    /* input buffers and temps */
    char driverName[MAX_CHAR + 1];
    char licencePlate[MAX_LICENCE_CHAR + 1];
    int vehicleColour;

    printf("Enter driver code: ");
    scanf("%d", &updateDriverCode);
    getchar(); // clear newline

    Driver *node = find_driver(updateDriverCode, NULL);
    if (!node) {
        printf("Code is not found in the data base.\n");
        return 1;
    }

    /* prompt and replace fields (validate) */
        printf("Enter name of the driver: ");
        fgets(driverName, MAX_CHAR + 1, stdin);
        size_t len = strlen(driverName);
        if (len > 0 && driverName[len - 1] == '\n') {
            driverName[len - 1] = '\0';
        } else {
            // NO NEWLINE → means input was too long → flush remainder
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
        }
        driverName[strcspn(driverName, "\n")] = '\0';
        strncpy(node->name, driverName, MAX_CHAR);
        node->name[MAX_CHAR] = '\0';

        printf("Enter name of the licence plate: ");
        fgets(licencePlate, MAX_LICENCE_CHAR + 1, stdin);
        len = strlen(licencePlate);
        if (len > 0 && licencePlate[len - 1] == '\n') {
            licencePlate[len - 1] = '\0';
        } else {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
        }
        licencePlate[strcspn(licencePlate, "\n")] = '\0';
        strncpy(node->licencePlate, licencePlate, MAX_LICENCE_CHAR);
        node->licencePlate[MAX_LICENCE_CHAR] = '\0';

        /* prompt and validate vehicleColour (re-prompt on invalid) */
        while (1) {
            char tmp[128];
            printf("Enter driver vehicle colour: ");
            if (!fgets(tmp, sizeof(tmp), stdin)) return 1;
            if (sscanf(tmp, "%d", &vehicleColour) != 1) { printf("Invalid vehicle colour. Try again.\n"); continue; }
            if (vehicleColour < 0.0f || vehicleColour > 10.0f) { printf("vehicle colour must be between 0.0 and 10.0\n"); continue; }
            node->vehicleColour = vehicleColour; break;
        }

    return 0;
}

int listDriver(void) {
    // list the driver with spacing
    printf("%-12s %-26s %-32s %-26s\n", "driver Code", "driver Name", "licence plate", "vehicle colour");

    /* iterate the list and print nodes */
    Driver *cur = driverHead;
    while (cur) {
        printf("%-12d %-26s %-32s %-26.1d\n", cur->code, cur->name, cur->licencePlate, cur->vehicleColour);
        cur = cur->next;
    }

    return 0;
}

/*
 * driver_menu - interactive driver menu exported to top-level `snackaroo.c`
 * This replaces the old `main` and will return to the top-level
 * application when the user enters 'q'. The function frees all nodes
 * before returning.
 */
void driverMenu(void) {
    char operationCode = '\0';

    while (true) {
        printf("\n==================================== driver Menu =====================================\n");
        printf("(i) Insert driver, (s) Search driver, (u) Update driver, (p) Print All driveres\n");
        printf("(e) Erase driver, (p) Dump from File, (r) Restore from File (q) Quit\n");
        printf("=====================================================================================\n");
        printf("Enter operation: ");
        if (scanf(" %c", &operationCode) != 1) break;
        if (operationCode == 'i') {
            newDriver();
        } else if (operationCode == 's') {
            searchDriver();
        } else if (operationCode == 'u') {
            updateDriver();
        } else if (operationCode == 'p') {
            listDriver();
        } else if (operationCode == 'e') {
            eraseDriver();
        } else if (operationCode == 'd') {
            /* driver dump (prototype is in snackaroo_driver.h) */
            char filename[256];
            printf("Enter filename to dump to: ");
            if (scanf(" %255s", filename) == 1) driverDump(filename);
        } else if (operationCode == 'r') {
            /* driver restore (prototype is in snackaroo_driver.h) */
            char filename[256];
            printf("Enter filename to restore from: ");
            if (scanf(" %255s", filename) == 1) driverRestore(filename);
        } else if (operationCode == 'q') {
            break;
        } else {
            printf("Unknown operation: %c\n", operationCode);
        }
    }

    /* DO NOT free the global list here — keep driveres available for the
›    * lifetime of the program so the dish_driver module can reference driveres
     * even after returning to the top-level menu. Lists will be cleaned up
     * when the program exits (OS will reclaim memory), or a later explicit
     * cleanup function could be added if desired.
     */
}

/* remove a driver from the list and free memory */
int eraseDriver(void) {
    if (!driverHead) {
        printf("Database is empty. Nothing to erase.\n");
        return 1;
    }
    int eraseDriverCode;
    printf("Enter driver code to erase: ");
    if (scanf("%d", &eraseDriverCode) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    Driver *prev = NULL;
    Driver *node = find_driver(eraseDriverCode, &prev);
    if (!node) {
        printf("driver code %d not found.\n", eraseDriverCode);
        return 1;
    }
    /* referential integrity: cannot delete a driver that is referenced by dish_driver entries */
    if (dish_driver_has_driver(eraseDriverCode)) { printf("Cannot remove driver: active dish_driver entries exist.\n"); return 1; }
    if (!prev) driverHead = node->next;
    else prev->next = node->next;
    free(node);
    driverCount--;
    printf("driver with code %d erased successfully.\n", eraseDriverCode);
    return 0;
}

int driverDump(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        perror("opening file");
        return 1;
    }

    int count = 0;
    Driver *cur = driverHead;
    while (cur) {
        count++;
        cur = cur->next;
    }

    if (fwrite(&count, sizeof(count), 1, f) != 1) {
        fclose(f);
        return 1;
    }

    cur = driverHead;
    while (cur) {
        int code = cur->code;
        if (fwrite(&code, sizeof(code), 1, f) != 1) break;
        if (fwrite(cur->name, sizeof(cur->name), 1, f) != 1) break;
        if (fwrite(cur->licencePlate, sizeof(cur->licencePlate), 1, f) != 1) break;
        if (fwrite(&cur->vehicleColour, sizeof(cur->vehicleColour), 1, f) != 1) break;
        cur = cur->next;
    }

    fclose(f);
    printf("Wrote %d driveres to %s\n", count, filename);
    return 0;
}


int driverRestore(const char *filename) {
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
        char licencePlate[100];
        int vehicleColour;

        if (fread(&code, sizeof(code), 1, f) != 1) break;
        if (fread(name, sizeof(name), 1, f) != 1) break;
        if (fread(licencePlate, sizeof(licencePlate), 1, f) != 1) break;
        if (fread(&vehicleColour, sizeof(vehicleColour), 1, f) != 1) break;

        /* skip duplicates */
        if (driver_exists(code)) continue;

        /* validate */
        if (vehicleColour < 0.0f || vehicleColour > 10.0f) {
            printf("Skipping driver %d invalid vehicle colour\n", code);
            continue;
        }

        Driver *n = malloc(sizeof(Driver));
        if (!n) {
            printf("Out of memory\n");
            fclose(f);
            return 1;
        }
        n->code = code;
        strncpy(n->name, name, sizeof(n->name)-1); n->name[sizeof(n->name)-1] = '\0';
        strncpy(n->licencePlate, licencePlate, sizeof(n->licencePlate)-1); n->licencePlate[sizeof(n->licencePlate)-1] = '\0';
        n->vehicleColour = vehicleColour;
        n->next = NULL;
        append_driver(n);
        driverCount++;
    }

    fclose(f);
    printf("Restore complete from %s\n", filename);
    return 0;
}

/* --- helper implementations --- */
static Driver *find_driver(int code, Driver **out_prev) {
    Driver *prev = NULL;
    Driver *cur = driverHead;
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
Driver *driver_get(int code) { return find_driver(code, NULL); }
int driver_exists(int code) { return driver_get(code) != NULL; }

static void append_driver(Driver *node) {
    if (!driverHead) driverHead = node;
    else {
        Driver *cur = driverHead;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
}
