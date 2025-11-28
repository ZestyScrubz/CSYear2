Snackaroo — Dish & Driver management (small CLI)

Overview
--------
Snackaroo is a minimal command-line program demonstrating in-memory management of two entity types:

- Dish: stored in a dynamically allocated singly linked list
  - Fields: code (int), name (string), restaurant (string), rating (float), price (float)
- Driver: stored in a dynamically allocated singly linked list
  - Fields: code (int), name (string), vehicleColour (int 0..6), licencePlate (string)

Build
-----
From the project root (macOS / Linux):

    gcc -Wall -Wextra -o snackaroo snackaroo.c snackaroo_dish.c snackaroo_driver.c

Run
---
Start the program and use the top-level menu:

    ./snackaroo

Top-level commands:
- h : help (short description)
- m : enter Dish menu (insert/search/update/list/erase)
- a : enter Driver menu (insert/search/update/list/erase)
- q : quit the program

Inside each menu, the following single-letter commands are supported:
- i : insert (add a new entity)
- s : search by numeric code
- u : update the entity with new data
- p : print/list all entities
- e : erase/delete an entity by code
- q : return to top-level menu

Notes / limitations
-------------------
- The implementation uses `scanf` in places which does not accept spaces inside string fields (e.g. driver/dish names). Consider changing to `fgets()` or `getline()` for multi-word names.
- Data is stored in memory only; there is no persistence across runs.
- Validation is performed for numeric ranges and alphanumeric licence plates.

Possible improvements
---------------------
- Add file-based persistent storage (save/load) in CSV/JSON format
- Replace `scanf("%s")` with robust line-reading for full names with spaces
- Add a suite of automated tests for the CLI and functions

Files
-----
- snackaroo.c         — top-level CLI
- snackaroo_dish.c    — dish linked list implementation & CLI
- snackaroo_driver.c  — driver linked list implementation & CLI
- snackaroo_dish.h    — dish menu prototype
- snackaroo_driver.h  — driver menu prototype

Contact
-------
This README was created automatically by the project assistant. For changes, edit files in the repository and recompile.
