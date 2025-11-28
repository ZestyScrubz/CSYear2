snackaroo: snackaroo.o snackaroo_dish.o snackaroo_driver.o snackaroo_dish_driver.o
	gcc -o snackaroo snackaroo.o snackaroo_dish.o snackaroo_driver.o snackaroo_dish_driver.o

snackaroo.o: snackaroo.c snackaroo_dish.h snackaroo_driver.h snackaroo_dish_driver.h
	gcc -c snackaroo.c

snackaroo_dish.o: snackaroo_dish.c snackaroo_dish.h
	gcc -c snackaroo_dish.c

snackaroo_driver.o: snackaroo_driver.c snackaroo_driver.h
	gcc -c snackaroo_driver.c

snackaroo_dish_driver.o: snackaroo_dish_driver.c snackaroo_dish_driver.h
	gcc -c snackaroo_dish_driver.c