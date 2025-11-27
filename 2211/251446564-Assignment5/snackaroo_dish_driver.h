#ifndef SNACKAROO_DISH_DRIVER_H
#define SNACKAROO_DISH_DRIVER_H

/* dish_driver records the delivery association between a dish and a driver */
typedef struct dish_driver_code {
    int id;            /* dish_driver_code id/code */
    int dishCode;
    int driverCode;
    struct dish_driver_code *next;
} dish_driver_code;

void dish_driver_menu(void);

/* Helpers used by other modules */
int dish_driver_has_dish(int dish_code);   /* 1 if any dish_driver references dish_code */
int dish_driver_has_driver(int driver_code);/* 1 if any dish_driver references driver_code */

int dish_driver_dump(const char *filename);
int dish_driver_restore(const char *filename);

#endif
