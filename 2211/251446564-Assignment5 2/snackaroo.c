
#include <stdio.h>
#include "snackaroo_dish.h"
#include "snackaroo_driver.h"
#include "snackaroo_dish_driver.h"

/*
 * snackaroo.c
 * Entry point for the Snackaroa o Dish/Driver management system.
 * Provides the top-level menu which lets the user choose the Dish
 * or Driver sub-menus. The sub-menus are implemented in
 * `snackaroo_dish.c` and `snackaroo_driver.c` respectively.
 */
int main(void) {
    char command;

    /* main input loop: read a single character command and dispatch */
    while (1) {
        printf("Enter command: ");
        if (scanf(" %c", &command) != 1) {
            /* on invalid input, keep the program alive */
            clearerr(stdin);
            continue;
        }

        if (command == 'h') {
            /* help text */
            printf("This is Snackaroo Dish Management System.\n");
            printf("Top-level commands: h (help) m (dish menu) a (driver menu) r (relation) q (quit)\n");
        } else if (command == 'q') {
            /* clean exit */
            break;
        } else if (command == 'm') {
            /* control moves to the dish sub-menu */
            dishMenu();
        } else if (command == 'a') {
            /* control moves to the driver sub-menu */
            driverMenu();
        } else if (command == 'r') {
            /* dish_driver menu: dish-driver associations */
            dish_driver_menu();
        } else {
            printf("Unknown command: %c\n", command);
        }
    }

    return 0;
}