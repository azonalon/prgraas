/*
Compile: make climate_control
Run: ./climate_control
*/

#include "base.h"

/*
Eine Klimaanlage soll bei Temperaturen unter 18.5 °C heizen, bei 18.5-22.2 °C
nichts tun und bei Temperaturen ab 22.2 °C kühlen. Entwickeln Sie eine Funktion
zur Regelung der Klimaanlage, die abhängig von der Temperatur heizt,
ausschaltet oder kühlt.
*/

enum ClimateRegulation {
    ERROR_MESSAGE,
    COOL,
    DO_NOTHING,
    HEAT
};

typedef double Celsius;

const Celsius ABSOLUTE_ZERO = -273.15;
const Celsius LOW_TEMPERATURE = 18.5;
const Celsius HIGH_TEMPERATURE = 22.2;

// Celsius -> enum ClimateRegulation
// Return the expected climate regulation for a given temperature.
enum ClimateRegulation climate_control(Celsius current_temperature);

static void climate_control_test() {
    check_expect_i(climate_control(-273.15), ERROR_MESSAGE);
    check_expect_i(climate_control(0), HEAT);
    check_expect_i(climate_control(18.5), DO_NOTHING);
    check_expect_i(climate_control(20), DO_NOTHING);
    check_expect_i(climate_control(22.2), COOL);
    check_expect_i(climate_control(30), COOL);
}

enum ClimateRegulation climate_control(Celsius current_temperature) {
    if (current_temperature <= ABSOLUTE_ZERO) {
        printsln("error: temperature at absolute zero or below");
        return ERROR_MESSAGE;
    } else if (current_temperature < LOW_TEMPERATURE) {
        return HEAT;
    } else if (current_temperature < HIGH_TEMPERATURE) {
        return DO_NOTHING;
    } else {
        return COOL;
    }
}

int main(void) {
    climate_control_test();
    return 0;
}
