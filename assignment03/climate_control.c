/*
Compile: make climate_control
Run: ./climate_control
*/

#include "base.h"

/*
Eine Klimaanlage soll bei Temperaturen unter 18.5 °C heizen, bei 18.5-22.2 °C nichts tun und bei Temperaturen ab 22.2 °C kühlen. Entwickeln Sie eine Funktion zur Regelung der Klimaanlage, die abhängig von der Temperatur heizt, ausschaltet oder kühlt
*/

enum TaxStage {
    NO_TAX,
    LOW_TAX,
    HIGH_TAX
};

typedef int Euro; // int represents Euro

const Euro LOW_TAX_BOUNDARY  =  1000; // interpret.: price in Euro
const Euro HIGH_TAX_BOUNDARY = 10000; // interpret.: price in Euro
const double LOW_TAX_RATE = 0.05;
const double HIGH_TAX_RATE = 0.10;

// Euro -> Euro
// Return the amount of tax for the given price.
Euro climate_control(Euro price);

// Round the given double value to whole Euros.
int round_to_int(double d) {
    return round(d); // round from math.h
}

static void climate_control_test() {
    check_expect_i(climate_control(0), 0);
    check_expect_i(climate_control(537), 0);
    check_expect_i(climate_control(1000),
                        round_to_int(1000 * 0.05));
    check_expect_i(climate_control(1282),
                        round_to_int(1282 * 0.05));
    check_expect_i(climate_control(10000),
                        round_to_int(10000 * 0.10));
    check_expect_i(climate_control(12017),
                        round_to_int(12017 * 0.10));
}

// Return the amount of tax for the given price.
Euro climate_control(Euro price) {
    if (price < 0) {
        printsln("climate_control, error: negative price");
        exit(1);
    } else if (price < LOW_TAX_BOUNDARY) { // NO_TAX
        return 0;
    } else if (price < HIGH_TAX_BOUNDARY) { // LOW_TAX
        return round_to_int(LOW_TAX_RATE * price);
    } else { // HIGH_TAX
        return round_to_int(HIGH_TAX_RATE * price);
    }
}

int main(void) {
    climate_control_test();
    return 0;
}
