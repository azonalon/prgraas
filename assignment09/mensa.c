/*
Compile: make mensa
Run: ./mensa
Compile & run: make mensa && ./mensa
*/

#include "base.h"        // http://hci.uni-hannover.de/files/prog1lib/base_8h.html
#include "string.h"      // http://hci.uni-hannover.de/files/prog1lib/string_8h.html
#include "list.h"        // http://hci.uni-hannover.de/files/prog1lib/list_8h.html
#include "string_list.h" // http://hci.uni-hannover.de/files/prog1lib/string__list_8h.html

/**
Today's menu.
*/
const String menu[] = { "Currywurst", "Spaghetti Bolognese", "Vegi", "Soup", "Salad" };

/**
The number of items on the menu.
*/
const int menu_count = sizeof(menu) / sizeof(char*);

/**
The list of completed food from the kitchen, waiting to be served. Each time a food item is served, the kitchen prepares a new food item randomly from the menu.
*/
List food; // List(String)

/**
The list of students standing in line and waiting for food. Each entry contains a string for the food that this student wants. The student at index 0 is at the front of the list.
*/
List students; // List(String)

/**
The reputation of the mensa. The goal of the player is to maximize the reputation of the mensa. Serving a dish that was asked for increases the reputation of the mensa by 1. Serving the wrong dish decreases the reputation by 1. If a student asks for a dish that is on the menu but not ready to be served, the reputation of the mensa decreases by 2.
*/
int reputation = 0;

/**
food: [Currywurst, Salad, Spaghetti Bolognese, Vegi, Salad]
next student: Vegi (3 students waiting)
mensa reputation: 0
> 
*/
void print_situation() {
    printf("food: ");
    sl_print(food);
    printf("\nnext student: %s (%d students waiting)\nmensa reputation: %d\n> ",
        sl_get(students, 0), l_length(students), reputation);
}

/**
Print final message, release all dynamically allocated memory, and exit the program.
*/
void finish(void) {
    printf("No more students. Done for today. The mensa is closed.\nFinal reputation: %d\n",
        reputation);
    l_free(food);
    l_free(students);
}

void not_available(void) {
    printf("You don't have %s? What a crappy mensa!\n", sl_get(students, 0));
    sl_remove(students, 0);
    reputation -= 2;
}

void last_student_leaves(void) {
    printf("You don't have %s? What a crappy mensa!\n", sl_get(students, 0));
    reputation -= 2;
}

void wrong_dish(int input) {
    printf("I don't want %s! I want %s!\n", sl_get(food, input), sl_get(students, 0));
    reputation--;
}

void right_dish(int input) {
    printf("Thank you!\n");
    sl_remove(food, input);
    sl_remove(students, 0);
    sl_append(food, menu[i_rnd(menu_count)]);
    sl_append(students, menu[i_rnd(menu_count)]);
    reputation++;
}

/**
Run the mensa simulation.

The mensa person then enters the (0-based) index from the list of food. -1 stands for "not available". -2 ends the program. 

Here is an example dialog:

food: [Currywurst, Salad, Spaghetti Bolognese, Spaghetti Bolognese, Salad]
next student: Vegi (3 students waiting)
mensa reputation: 0
> 0
I don't want Currywurst! I want Vegi!
food: [Currywurst, Salad, Spaghetti Bolognese, Spaghetti Bolognese, Salad]
next student: Vegi (3 students waiting)
mensa reputation: -1
> -1
You don't have Vegi? What a crappy mensa!
food: [Currywurst, Salad, Spaghetti Bolognese, Spaghetti Bolognese, Salad]
next student: Salad (2 students waiting)
mensa reputation: -3
> 1
Thank you!
food: [Currywurst, Spaghetti Bolognese, Spaghetti Bolognese, Salad, Currywurst]
next student: Vegi (2 students waiting)
mensa reputation: -2
> -1
You don't have Vegi? What a crappy mensa!
food: [Currywurst, Spaghetti Bolognese, Spaghetti Bolognese, Salad, Currywurst]
next student: Currywurst (1 students waiting)
mensa reputation: -4
> 0
Thank you!
food: [Spaghetti Bolognese, Spaghetti Bolognese, Salad, Currywurst, Salad]
next student: Spaghetti Bolognese (1 students waiting)
mensa reputation: -3
> 0
Thank you!
food: [Spaghetti Bolognese, Salad, Currywurst, Salad, Currywurst]
next student: Currywurst (1 students waiting)
mensa reputation: -2
> 4
Thank you!
food: [Spaghetti Bolognese, Salad, Currywurst, Salad, Soup]
next student: Vegi (1 students waiting)
mensa reputation: -1
> -1
You don't have Vegi? What a crappy mensa!
No more students. Done for today. The mensa is closed.
Final reputation: -3
*/
void run_mensa(void) {
    // todo: implement
    
    // create 5 random food items from the menu
    // store in list...
    
    food = sl_create();
    for(int i = 0; i < 5; i++) {
        sl_append(food, menu[i_rnd(menu_count)]);
    }
    
    // create 3 random food wishes from the menu (each wish from one student)
    // store in list...
    
    students = sl_create();
    for(int i = 0; i < 3; i++) {
        sl_append(students, menu[i_rnd(menu_count)]);
    }
    
    // in a loop: read user input, take action based on input, print situation
    //...
    
    print_situation();
    
    while(true) {
        
        int input = i_input();
        
        if(input == -2) {
            break;
        } else if(input == -1) {
            if(l_length(students) > 1) {
                not_available();
            } else {
                last_student_leaves();
                break;
            }
        } else if(s_compare(sl_get(food, input), sl_get(students, 0)) != 0) {
            wrong_dish(input);
        } else if(s_compare(sl_get(food, input), sl_get(students, 0)) == 0) {
            right_dish(input);
        } else {
            printf("invalid input\n");
        }
        
        print_situation();
        
    }
    
    finish();
}

int main(void) {
    base_init();
    base_set_memory_check(true);
    run_mensa();
    return 0;
}
