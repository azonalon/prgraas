/*
Compile: make closest
Run: ./closest
*/

// http://hci.uni-hannover.de/files/prog1lib/index.html
#include "base.h"
#include "array.h"
#include "int_array.h"
#include "double_array.h"

/*
Gegeben sind zwei Arrays a und b mit Elementen vom Typ double. Für jedes Element von a berechnet die Funktion den Index des ähnlichsten Elements in b. Ähnlichkeit ist hier definiert als kleinste absolute Differenz. Die Funktion gibt ein Array der entsprechenden Indizes zurück.
*/

// int, Array(String) --> Array(String)    [todo: write signature]
// Returns ...    [todo: write purpose statement]
int closest(int a, int b); // todo: modify header (parameters, parameter types, return type)

static void closest_test(void) {
    // todo: implement tests
}

double fabs(double x) {
    return (x >= 0) ? x : -x;
}

int closest(int a, int b) { // todo: modify header (parameters, parameter types, return type)
    // todo: implement
    return 0;
}

int main(void) {
    closest_test();
    return 0;
}
