/*
Compile: make weights
Run: ./weights
*/
 
// http://hci.uni-hannover.de/files/prog1lib/index.html
#include "base.h"
#include "array.h"
#include "string.h"
#include "string_array.h"

/*
Gegeben ist ein String-Array mit Elementen verschiedenen Gewichts. Im
String-Array ist abwechselnd eine Zahl (als String) und eine Einheit (kg, g oder
t) gespeichert. Ein Beispiel wäre: ["10", "kg", "500", "g", "0.5", "t"]. Ihre
Aufgabe besteht darin, das Gesamtgewicht aller Elemente in Kilogramm zu
berechnen. Beachten Sie dabei, dass Sie zunächst die verschiedenen Gewichte auf
Kilogramm umrechnen müssen. Gewichte unbekannter Einheit können Sie ignorieren.
*/

// Array -> double
// Returns weight in kg for a given String-Array with weights followed by
// one of the units g, kg, t in the next element.
double total_weight_kg(Array weight_array);

static void total_weight_kg_test(void) {
    check_within_d(
        total_weight_kg(sa_of_string("100.0, g, 0.25, kg, 2, t, 42, no_unit")),
        2000.35, EPSILON);
    check_within_d(
        total_weight_kg(sa_of_string("0.0, t, 3, kg, 0.05, t, 10.5, g")),
        53.0105, EPSILON);
}

double total_weight_kg(Array weight_array) {
    double total_weight = 0.0;
    for(int i = 0; i < a_length(weight_array); i += 2) {
        double weight = d_of_s(sa_get(weight_array, i));
        String unit = sa_get(weight_array, i + 1);
        if(s_equals(unit, "g")) {
            total_weight += 1e-3 * weight;
        } else if(s_equals(unit, "kg")) {
            total_weight += weight;
        } else if(s_equals(unit, "t")) {
            total_weight += 1e3 * weight;
        }
    }
    return total_weight;
}

int main(void) {
    total_weight_kg_test();
    return 0;
}
