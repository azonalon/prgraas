/*
Compile: make sail
Run: ./sail
*/

#include "base.h"

/*
In einer Spielewelt sei die Erde eine Scheibe mit den Kontinenten Europa,
Afrika und Amerika. Afrika liegt südlich von Europa. Amerika liegt westlich von
Europa und Afrika. In der Spielewelt können Nord-, Süd-, Ost- und Westwinde
auftreten. In der Spielewelt gibt es genau ein Segelschiff. Wenn das
Segelschiff bei Westwind in Europa startet, fährt es nach Amerika. Wenn es bei
Ostwind in Amerika startet, landet es (auf Grund einer nördlichen
Wasserströmung) in Europa. Wenn es bei Westwind von Amerika aus startet, fällt
es ins Nichts. Wenn es bei Südwind in Europa startet, landet es in Afrika.
Entsprechendes gilt für die anderen möglichen Kombinationen von Startposition
und Windrichtung. Nehmen Sie an, dass sich die Windrichtung nur vor, aber nie
während einer Reise des Segelschiffs ändert. Entwickeln Sie eine Funktion, die
abhängig von der Startposition des Segelschiffs und der Windrichtung beim Start
die Zielposition bestimmt.
*/

enum Continent {
    AFRICA,
    AMERICA,
    EUROPE,
    NOWHERE
};

enum WindDiretion {
    NORTH,
    WEST,
    EAST,
    SOUTH
};

// (enum Continent, enum WindDiretion) -> enum Continent
// Return the next continent for a given continent and a wind direction.
enum Continent sail(enum Continent starting_continent, enum WindDiretion wd);

static void sail_test() {
    check_expect_i(sail(AMERICA, EAST), EUROPE);
    check_expect_i(sail(EUROPE, WEST), AMERICA);
    check_expect_i(sail(EUROPE, SOUTH), AFRICA);
    check_expect_i(sail(AFRICA, NORTH), EUROPE);
    check_expect_i(sail(AMERICA, SOUTH), NOWHERE);
    check_expect_i(sail(AFRICA, EAST), NOWHERE);
    check_expect_i(sail(NOWHERE, NORTH), NOWHERE);
    check_expect_i(sail(NOWHERE, WEST), NOWHERE);
}

enum Continent sail(enum Continent starting_continent, enum WindDiretion wd) {
    if (starting_continent == AFRICA) {
        if (wd == NORTH) {
            return EUROPE;
        } else {
            return NOWHERE;
        }
    } else if (starting_continent == AMERICA) {
        if (wd == EAST) {
            return EUROPE;
        } else {
            return NOWHERE;
        }
    } else if (starting_continent == EUROPE) {
        if (wd == WEST) {
            return AMERICA;
        } else if (wd == SOUTH) {
            return AFRICA;
        } else {
            return NOWHERE;
        }
    } else {
        return NOWHERE;
    }
}

enum Continent sail_with_switch(enum Continent starting_continent,
                                enum WindDiretion wd)
{
    switch(starting_continent)
    {
        case AFRICA:
            if (wd == NORTH)
                return EUROPE;
            else
                return NOWHERE;
        case AMERICA:
            if (wd == EAST)
                return EUROPE;
            else
                return NOWHERE;
        case EUROPE:
            if (wd == WEST)
                return AMERICA;
            else if (wd == SOUTH)
                return AFRICA;
            else
                return NOWHERE;
        default:
            return NOWHERE;

    }
}

int main(void) {
    sail_test();
    return 0;
}
