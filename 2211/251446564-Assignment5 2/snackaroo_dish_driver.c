/**
 * Program that allows the user to store the information of a dish and driver
 * Student Name: Isaac Tran
 * Student email: itran9@uwo.ca
 * Student ID: 251446564
 * Due Date: 2025-11-25
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snackaroo_dish_driver.h"
#include "snackaroo_dish.h"
#include "snackaroo_driver.h"

/* dish_driver nodes are stored in a singly-linked list */
static dish_driver_code *dish_driverHead = NULL;
static int dish_driverCount = 0;

static dish_driver_code *find_dish_driver(int code, dish_driver_code **out_prev) {
    dish_driver_code *prev = NULL;
    dish_driver_code *cur = dish_driverHead;
    while (cur) {
        if (cur->id == code) {
            if (out_prev) *out_prev = prev;
            return cur;
        }
        prev = cur;
        cur = cur->next;
    }
    if (out_prev) *out_prev = NULL;
    return NULL;
}

static void append_dish_driver(dish_driver_code *node) {
    if (!dish_driverHead) dish_driverHead = node;
    else {
        dish_driver_code *cur = dish_driverHead;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
}

int dish_driver_has_dish(int dish_code) {
    dish_driver_code *cur = dish_driverHead;
    while (cur) {
        if (cur->dishCode == dish_code) return 1;
        cur = cur->next;
    }
    return 0;
}

int dish_driver_has_driver(int driver_code) {
    dish_driver_code *cur = dish_driverHead;
    while (cur) {
        if (cur->driverCode == driver_code) return 1;
        cur = cur->next;
    }
    return 0;
}

int newDish_driver(void) {
    int id, dishCode, driverCode;
    printf("Enter dish_driver id: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (id < 0) {
        printf("Id must be non-negative.\n");
        return 1;
    }
    if (find_dish_driver(id, NULL))
    { printf("Dish-driver id already exists.\n");
        return 1;
    }

    printf("Enter dish code: ");
    if (scanf("%d", &dishCode) != 1)
    { printf("Invalid dish code.\n");
        return 1;
    }
    if (!dish_exists(dishCode)) {
        printf("Dish code %d not found.\n", dishCode);
        return 1;
    }

    printf("Enter driver code: ");
    if (scanf("%d", &driverCode) != 1) {
        printf("Invalid driver code.\n");
        return 1;
    }
    if (!driver_exists(driverCode)) {
        printf("Driver code %d not found.\n", driverCode);
        return 1;
    }

    dish_driver_code *node = malloc(sizeof(dish_driver_code));
    if (!node) {
        printf("Out of memory.\n");
        return 1;
    }
    node->id = id; node->dishCode = dishCode; node->driverCode = driverCode; node->next = NULL;
    append_dish_driver(node);
    dish_driverCount++;
    printf("Dish-driver %d added (dish %d -> driver %d).\n", id, dishCode, driverCode);
    return 0;
}

int searchDish_driver(void) {
    int id;
    printf("Enter dish_driver id: ");
    if (scanf("%d", &id) != 1) { 
        printf("Invalid input.\n"); 
        return 1; 
    }
    dish_driver_code *node = find_dish_driver(id, NULL);
    if (!node) { 
        printf("Dish-driver %d not found.\n", id); 
        return 1; 
    }
    printf("Dish-driver %d -> dish %d, driver %d\n", node->id, node->dishCode, node->driverCode);
    return 0;
}

int listDish_driver(void) {
    printf("%-10s %-10s %-10s\n", "Rel ID", "Dish", "Driver");
    dish_driver_code *cur = dish_driverHead;
    while (cur) {
        printf("%-10d %-10d %-10d\n", cur->id, cur->dishCode, cur->driverCode);
        cur = cur->next;
    }
    return 0;
}

int dishes_for_driver(void) {
    int driverCode;
    printf("Enter driver code: ");
    if (scanf("%d", &driverCode) != 1) { 
        printf("Invalid input.\n"); 
        return 1; 
    }
    if (!driver_exists(driverCode)) { 
        printf("Driver %d not found.\n", driverCode); 
        return 1; 
    }
    /* iterate dish_driver entries and for each match print dish attributes */
    dish_driver_code *cur = dish_driverHead;
    int found = 0;
    while (cur) {
        if (cur->driverCode == driverCode) {
            Dish *d = dish_get(cur->dishCode);
            if (d) {
                if (!found) printf("%-12s %-26s %-32s %-10s %s\n", "Dish Code", "Dish Name", "Restaurant", "Rating", "Price");
                printf("%-12d %-26s %-32s %-10.1f $%.2f\n", d->code, d->name, d->restaurant, d->rating, d->price);
                found = 1;
            }
        }
        cur = cur->next;
    }
    if (!found) printf("No dishes found for driver %d.\n", driverCode);
    return 0;
}

int drivers_for_dish(void) {
    int dishCode;
    printf("Enter dish code: ");
    if (scanf("%d", &dishCode) != 1) { 
        printf("Invalid input.\n"); 
        return 1; 
    }
    if (!dish_exists(dishCode)) { 
        printf("Dish %d not found.\n", dishCode); 
        return 1; 
    }
    dish_driver_code *cur = dish_driverHead;
    int found = 0;
    while (cur) {
        if (cur->dishCode == dishCode) {
            Driver *drv = driver_get(cur->driverCode);
            if (drv) {
                if (!found) printf("%-12s %-26s %-16s %s\n", "Driver Code", "Driver Name", "Vehicle Col", "Licence");
                printf("%-12d %-26s %-16d %s\n", drv->code, drv->name, drv->vehicleColour, drv->licencePlate);
                found = 1;
            }
        }
        cur = cur->next;
    }
    if (!found) printf("No drivers found for dish %d.\n", dishCode);
    return 0;
}

int eraseDish_driver(void) {
    int id;
    printf("Enter dish_driver id to erase: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    dish_driver_code *prev = NULL;
    dish_driver_code *node = find_dish_driver(id, &prev);
    if (!node) {
        printf("Dish-driver %d not found.\n", id);
        return 1;
    }
    if (!prev) dish_driverHead = node->next; else prev->next = node->next;
    free(node);
    dish_driverCount--;
    printf("Dish-driver %d removed.\n", id);
    return 0;
}

/**
 * Writes the current in-memory list of dish_driver entries to filename in bianry form.
 * Returns 0 on success, 1 on failure.
 */
int dish_driver_dump(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) { 
        perror("opening file"); 
        return 1;
    }
    /* write count then each dish_driver {id,dish,driver} */
    int count = 0;
    dish_driver_code *cur = dish_driverHead;
    while (cur) {
        count++; 
        cur = cur->next;
    }
    if (fwrite(&count, sizeof(count), 1, f) != 1) { 
        fclose(f); 
        return 1;
    }
    cur = dish_driverHead;

    while (cur) {
        if (fwrite(&cur->id, sizeof(cur->id), 1, f) != 1) break;
        if (fwrite(&cur->dishCode, sizeof(cur->dishCode), 1, f) != 1) break;
        if (fwrite(&cur->driverCode, sizeof(cur->driverCode), 1, f) != 1) break;
        cur = cur->next;
    }
    fclose(f);
    printf("Wrote %d dish_driver entries to %s\n", count, filename);
    return 0;
}

int dish_driver_restore(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) { 
        perror("opening file"); 
        return 1; 
    }

    int count = 0;

    if (fread(&count, sizeof(count), 1, f) != 1) { 
        fclose(f); 
        printf("Empty or invalid file\n"); 
        return 1; 
    }
    
    for (int i = 0; i < count; ++i) {
        int id, dishCode, driverCode;
        if (fread(&id, sizeof(id), 1, f) != 1) break;
        if (fread(&dishCode, sizeof(dishCode), 1, f) != 1) break;
        if (fread(&driverCode, sizeof(driverCode), 1, f) != 1) break;
        
        /* skip duplicates */
        if (find_dish_driver(id, NULL)) continue;
        
        /* enforce referential integrity: dish and driver must exist */
        if (!dish_exists(dishCode) || !driver_exists(driverCode)) {
            printf("Skipping dish_driver %d -> missing dish or driver (%d,%d)\n", id, dishCode, driverCode);
            continue;
        }
        dish_driver_code *node = malloc(sizeof(dish_driver_code));
        if (!node) {
            printf("Out of memory while restoring\n"); fclose(f); 
            return 1; 
        }
        node->id = id; node->dishCode = dishCode; node->driverCode = driverCode; node->next = NULL;
        append_dish_driver(node);
        dish_driverCount++;
    }

    fclose(f);
    printf("Restore complete from %s\n", filename);
    return 0;
}

/* dish_driver_menu exported to top-level program */
void dish_driver_menu(void) {
    char operationCode = '\0';
    while (1) {
        printf("\n================================ Dish-Driver Menu ====================================\n");
        printf("(i) Insert, (s) Search, (p) Print all dish_driver, (a) Print all dishes for a driver,\n");
        printf("(v) Print all drivers for a dish, (e) Erase dish_driver, (d) Dump to file, (r) Restore from file, (q) Quit\n");
        printf("========================================================================================\n");
        printf("Enter operation: ");
        if (scanf(" %c", &operationCode) != 1) break;
        if (operationCode == 'i') newDish_driver();
        else if (operationCode == 's') {
            searchDish_driver();
        } else if (operationCode == 'p') {
            listDish_driver();
        } else if (operationCode == 'a') {
            dishes_for_driver();
        } else if (operationCode == 'v') {
            drivers_for_dish();
        } else if (operationCode == 'e') {
            eraseDish_driver();
        } else if (operationCode == 'd') {
            char filename[256];
            printf("Enter filename to dump to: ");
            if (scanf(" %255s", filename) == 1) dish_driver_dump(filename);
        } else if (operationCode == 'r') {
            char filename[256];
            printf("Enter filename to restore from: ");
            if (scanf(" %255s", filename) == 1) dish_driver_restore(filename);
        } else if (operationCode == 'q') break;
        else printf("Unknown operation: %c\n", operationCode);
    }
    /* free list */
    dish_driver_code *cur = dish_driverHead;
    while (cur) {
        dish_driver_code *next = cur->next;
        free(cur);
        cur = next;
    }
    dish_driverHead = NULL;
}