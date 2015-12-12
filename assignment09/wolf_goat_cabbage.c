/*
Compile: make wolf_goat_cabbage_solution
Run: ./wolf_goat_cabbage_solution
make wolf_goat_cabbage_solution && ./wolf_goat_cabbage_solution
*/

#include "base.h"        // http://hci.uni-hannover.de/files/prog1lib/base_8h.html
#include "string.h"      // http://hci.uni-hannover.de/files/prog1lib/string_8h.html
#include "list.h"        // http://hci.uni-hannover.de/files/prog1lib/list_8h.html
#include "string_list.h" // http://hci.uni-hannover.de/files/prog1lib/string__list_8h.html

/**
List of objects on the left river bank.
*/
List left;

/**
List of objects on the right river bank.
*/
List right;

/**
List of objects in the boat. The boat has a capacity of one object only.
*/
List boat;

/**
The boat may either be at the left or right river bank. We don't care for the transition (boat crossing the river).
*/
enum Position {
    LEFT, RIGHT
};

/**
Current boat position.
*/
enum Position position;

void print_situation(void) {
    sl_print(left);
    if (position == RIGHT) prints("     ");
    sl_print(boat);
    if (position == LEFT)  prints("     ");
    sl_println(right);  
}

void finish(void) {
    // todo: implement
}

void evaluate_situation(void) {
    // todo: implement
}

bool starts_with(String element, int index, String x) {
    return s_starts_with(element, x);
}

void play_wolf_goat_cabbage(void) {
    // todo: implement
}

int main(void) {
    base_init();
    base_set_memory_check(true);
    play_wolf_goat_cabbage();
    return 0;
}
