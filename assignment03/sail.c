/*
Compile: make sail
Run: ./sail
*/
 
#include "base.h"

/*
In einer Spielewelt sei die Erde eine Scheibe mit den Kontinenten Europa, Afrika und Amerika. Afrika liegt südlich von Europa. Amerika liegt westlich von Europa und Afrika. In der Spielewelt können Nord-, Süd-, Ost- und Westwinde auftreten. In der Spielewelt gibt es genau ein Segelschiff. Wenn das Segelschiff bei Westwind in Europa startet, fährt es nach Amerika. Wenn es bei Ostwind in Amerika startet, landet es (auf Grund einer nördlichen Wasserströmung) in Europa. Wenn es bei Westwind von Amerika aus startet, fällt es ins Nichts. Wenn es bei Südwind in Europa startet, landet es in Afrika. Entsprechendes gilt für die anderen möglichen Kombinationen von Startposition und Windrichtung. Nehmen Sie an, dass sich die Windrichtung nur vor, aber nie während einer Reise des Segelschiffs ändert. Entwickeln Sie eine Funktion, die abhängig von der Startposition des Segelschiffs und der Windrichtung beim Start die Zielposition bestimmt.
*/

enum TrafficLight {
    RED,
    GREEN,
    YELLOW
};

// enum TrafficLight -> enum TrafficLight
// Return the amount of tax for the given price.
enum TrafficLight sail(enum TrafficLight);

static void sail_test() {
    check_expect_i(sail(RED), GREEN);
    check_expect_i(sail(GREEN), YELLOW);
    check_expect_i(sail(YELLOW), RED);
}

// Produces the next color of a traffic light
// given the current color of the traffic light.
enum TrafficLight sail(enum TrafficLight tl) {
    if (tl == RED) {
        return GREEN;
    } else if (tl == GREEN) {
        return YELLOW;
    } else if (tl == YELLOW) {
        return RED;
    }
    return RED;
}

int main(void) {
    sail_test();
    return 0;
}
