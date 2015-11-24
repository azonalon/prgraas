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
Gegeben sind zwei Arrays a und b mit Elementen vom Typ double. Für jedes Element
von a berechnet die Funktion den Index des ähnlichsten Elements in b.
Ähnlichkeit ist hier definiert als kleinste absolute Differenz. Die Funktion
gibt ein Array der entsprechenden Indizes zurück.
*/

// Array, Array -> Array
// Returns an Array with the index of the element (the index is written on
// position n) in the second Array that is closest to the element in the first
// Array on position n.
Array closest(Array a, Array b);

static void closest_test(void) {
    ia_check_expect(
        closest(da_of_string("1.0, 2.3, -5"), da_of_string("1, 5.3, 3.3, 1.2")),
        ia_of_string("0, 2, 0"));
    ia_check_expect(
        closest(da_of_string("299792458, 42, 0.0073, 3.14"), da_of_string("0")),
        ia_of_string("0, 0, 0, 0"));
    ia_check_expect(
        closest(da_of_string("0.00000001, -1"), da_of_string("0, -0.5")),
        ia_of_string("0, 1"));
    ia_check_expect(
        closest(da_of_string("22.04"), da_of_string("99, -10.3, 25")),
        ia_of_string("2"));
}

double fabs(double x) {
    return (x >= 0) ? x : -x;
}

Array closest(Array a, Array b) {
    Array closest_indices = ia_create(a_length(a), 0);
    for(int i = 0; i < a_length(a); i++) {
        double minimal_difference = fabs(da_get(a, i) - da_get(b, 0));
        for(int j = 0; j < a_length(b); j++) {
            double difference = fabs(da_get(a, i) - da_get(b, j));
            if(difference < minimal_difference) {
                ia_set(closest_indices, i, j);
                minimal_difference = difference;
            }
        }
    }
    return closest_indices;
}

int main(void) {
    closest_test();
    return 0;
}
