#ifndef SNACKAROO_DRIVER_H
#define SNACKAROO_DRIVER_H

typedef struct Driver {
	int code;
	char name[50]; /* up to 49 chars */
	int vehicleColour; /* 0..6 */
	char licencePlate[9]; /* up to 8 chars + NUL */
	struct Driver *next;
} Driver;

void driverMenu(void);
int eraseDriver(void);

/* Accessors */
Driver *driver_get(int code);
int driver_exists(int code);

/* Dump/restore helpers */
int driverDump(const char *filename);
int driverRestore(const char *filename);

#endif
