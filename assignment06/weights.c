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
Gegeben ist ein String-Array mit Elementen verschiedenen Gewichts. Im String-Array ist abwechselnd eine Zahl (als String) und eine Einheit (kg, g oder t) gespeichert. Ein Beispiel wäre: ["10", "kg", "500", "g", "0.5", "t"]. Ihre Aufgabe besteht darin, das Gesamtgewicht aller Elemente in Kilogramm zu berechnen. Beachten Sie dabei, dass Sie zunächst die verschiedenen Gewichte auf Kilogramm umrechnen müssen. Gewichte unbekannter Einheit können Sie ignorieren.
*/

// int --> Array(String)    [todo: write signature]
// Returns ...    [todo: write purpose statement]
int total_weight_kg(int a); // todo: modify header (parameters, parameter types, return type)

static void total_weight_kg_test(void) {
    // todo: implement tests
}

int total_weight_kg(int a) { // todo: modify header (parameters, parameter types, return type)
    // todo: implement
    return 0;
}

int main(void) {
    total_weight_kg_test();
    return 0;
}
