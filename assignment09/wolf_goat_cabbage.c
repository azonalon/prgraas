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
The boat may either be at the left or right river bank. We don't care for the
transition (boat crossing the river).
*/
List current_bank;

String input;

enum Position {
    LEFT, RIGHT
};

/**
Current boat position.
*/
enum Position position;


List opposite_bank(){
    if(position == LEFT) {
        return right;
    }
    else
        return left;
}

void print_situation(void) {
    printf("Current situation: \n");
    printf("Your river bank is the");
    if(position == RIGHT)
        printf(" right ");
    else
        printf(" left ");
    printf("one.\nOn your side are ");
    sl_print(current_bank);
    printf(", \nOn the opposite side are ");
    sl_print(opposite_bank());
    printf(".\nYou placed ");
    sl_print(boat);
    printf(" on the boat.\n");
}

void finish(void) {
    sl_free(left);
    sl_free(right);
    sl_free(boat);
    exit(0);
}

void evaluate_situation(void) {

    if(sl_contains(opposite_bank(), "wolf") &&
       sl_contains(opposite_bank(), "goat")) {
        printf("Rooarr, you hear the sound of teared flesh... game over \n");
        finish();
    }
    if(sl_contains(opposite_bank(), "goat") &&
       sl_contains(opposite_bank(), "cabbage")) {
        printf("Meehehheh, in the distance you hear the goat scrunching. This is the end of the game. \n");
        finish();
    }
    if(
       sl_contains(right, "cabbage") &&
       sl_contains(right, "wolf") &&
       sl_contains(right, "goat")
       ) {
        printf("You won, congratulations!\n");
        finish();
    }
}


/* bool starts_with(String element, int index, String x) { */
/*     return s_starts_with(element, x); */
/* } */

void swap_with_boat(List bank, String object) {
    // requires object to be in bank
    String b = sl_get(boat, 0);

    sl_set(boat, 0, sl_get(bank, sl_index(bank, object)));
    if(s_equals(b, "nothing")){
        printf("Boat was empty and now contains %s", object);
        s_free(b);
        sl_remove(bank, sl_index(bank, object));
    }
    else {
        sl_set(bank, sl_index(bank, object), b);
    }
}

void deposit_on_bank(List bank) {
    String object = sl_get(boat, 0);
    sl_set(boat, 0, s_create("nothing"));
    sl_append(bank, object);
}

/* bool boat_empty() { */
/*     return s_compare(sl_get(boat, 0), " ") == EQ; */
/* } */

int is_on_bank(List bank, String object) {
    return(sl_index(bank, object)) >= 0;
}

bool is_on_boat(String object) {
    return(sl_index(boat, object)) >= 0;
}

/* void remove_from_slist(List l, String str) { */
/*     sl_remove(sl_index(l, str)); */
/* } */

void play_wolf_goat_cabbage(void) {
    left = sl_of_string("wolf,goat,cabbage");
    right = sl_create();
    boat = sl_of_string("nothing");
    position = LEFT;
    current_bank = left;
    char* command;
    while(true) {
        print_situation();
        printf("\nWhat do you want to do? \n");
        printf("w: wolf, c: cabbage, g: goat, \nl: go left, r: go right, q: quit \n");

        input = s_input(10);

        if(s_compare(input, "l") == EQ)
            command = "left";
        else if(s_compare(input, "r") == EQ)
            command = "right";
        else if(s_compare(input, "g") == EQ)
            command = "goat";
        else if(s_compare(input, "w") == EQ)
            command = "wolf";
        else if(s_compare(input, "c") == EQ)
            command = "cabbage";
        else if(s_compare(input, "q") == EQ)
            command = "quit";

        s_free(input);


        printf("\n\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n\n");
        printf("Your command: %s \n", command);

        if(s_compare(command, "left") == EQ) {
            position = LEFT;
            current_bank = left;
            printf("Now going left! \n");
        }
        else if(s_compare(command, "right") == EQ) {
            position = RIGHT;
            current_bank = right;
            printf("Now going right! \n");
        }

        else if(is_on_bank(current_bank, command)) {
            printf("The %s on your side was loaded on the boat. \n", command);
            swap_with_boat(current_bank, command);
        }
        else if(is_on_boat(command)) {
            deposit_on_bank(current_bank);
        }
        else if(s_equals(command, "quit")) {
            printf("Bored playing already? Alright, now quitting... \n");
            finish();
        }
        else {
            printf("invalid command...\n");
        }
        printf("\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
        evaluate_situation();
    }

}

int main(void) {
    base_init();
    base_set_memory_check(true);
    play_wolf_goat_cabbage();

    return 0;
}
