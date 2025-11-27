#ifndef SNACKAROO_DISH_H
#define SNACKAROO_DISH_H

/* Public Dish API — the Dish struct is exposed so other modules (dish_driver)
 * can inspect dish attributes. Fields are heap-allocated strings for
 * `name` and `restaurant` and must be NULL-terminated.
 */
typedef struct Dish {
	int code;
	char name[100];       /* up to 99 chars + null */
	char restaurant[100]; /* up to 99 chars + null */
	float rating;
	float price;
	struct Dish *next;
} Dish;

void dishMenu(void);

/* Accessors used by other modules */
Dish *dish_get(int code); /* returns pointer or NULL */
int dish_exists(int code); /* 1 if exists, 0 otherwise */

/* Dump/restore helpers (return 0 on success, 1 on error) */
int dishDump(const char *filename);
int dishRestore(const char *filename);

#endif
