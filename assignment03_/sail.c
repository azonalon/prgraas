/*
Compile: make sail
Run: ./sail
*/

#include "base.h"

/*
In einer Spielewelt sei die Erde eine Scheibe mit den Kontinenten Europa, Afrika und Amerika. Afrika liegt südlich von Europa. Amerika liegt westlich von Europa und Afrika. In der Spielewelt können Nord-, Süd-, Ost- und Westwindnde auftreten. In der Spielewelt gibt es genau ein Segelschiff. Wenn das Segelschiff bei Westwindnd in Europa startet, fährt es nach Amerika. Wenn es bei Ostwindnd in Amerika
startet, landet es (auf Grund einer nördlichen Wasserströmung) in Europa. Wenn es bei Westwindnd von Amerika aus startet, fällt es ins Nichts. Wenn es bei Südwindnd in Europa startet, landet es in Afrika. Entsprechendes gilt für die anderen möglichen Kombinationen von Startposition und windndrichtung. Nehmen Sie an, dass sich die windndrichtung nur vor, aber nie während einer Reise des Segelschiffs ändert. Entwindckeln Sie eine Funktion, die abhängig von der Startposition des Segelschiffs und der windndrichtung beim Start die Zielposition bestimmt.
*/


// Die unterschiedlichen Kontinente
enum Kontinent {
    EUROPA,
    AFRIKA,
    AMERIKA,
	NICHTS
};



// Die Windrichtungen
enum Windrichtung {
    NORD,
    SUED,
    OST,
	WEST
};

// enum Kontinent -> enum Kontinent

//Funktion
enum Kontinent kontinenten_segeln(enum Kontinent konti, enum Windrichtung wind);

int segel_test( enum Kontinent konti, enum Windrichtung wind);


//Testfunktionen bzw Beispiele für die Überprüfung
static void segeln_test() {
    check_expect_i(kontinenten_segeln(AMERIKA,SUED), NICHTS);
    check_expect_i(kontinenten_segeln(EUROPA,WEST), AMERIKA);
    check_expect_i(kontinenten_segeln(EUROPA,SUED), AFRIKA);
	check_expect_i(kontinenten_segeln(EUROPA,OST), NICHTS);
	check_expect_i(kontinenten_segeln(AMERIKA,SUED), NICHTS);
	check_expect_i(kontinenten_segeln(AMERIKA,OST), EUROPA);
	check_expect_i(kontinenten_segeln(AFRIKA,SUED), NICHTS);
}

//Eigebtliche Funktion(Zuerst wird nachdem Land geguckt, danach Einzelbetrachtung des Windes)

enum Kontinent kontinenten_segeln(enum Kontinent konti, enum Windrichtung wind) {
    if (konti == EUROPA){
		if (wind == WEST)
		{
			return AMERIKA;
		} else
		   if (wind == OST)
		   {
		  	return NICHTS;
		   }else
		   if (wind == NORD)
		   {
			return NICHTS;
		   }else
		   if (wind == SUED)
		   {
	     	return AFRIKA;
		   }else
		   return NICHTS;
	}else
    if (konti == AFRIKA){
		if (wind == WEST)
		{
			return NICHTS;
		}else
		if (wind == OST)
		{
			return NICHTS;
		}else
		if (wind == NORD)
		{
			return EUROPA;
		}else
		if (wind == SUED)
		{
			return NICHTS;
		}else
		return NICHTS;
	}else
    if (konti == AMERIKA){
	    if (wind == WEST)
		{
			return NICHTS;
		}else
		if (wind == OST){
			return EUROPA;
		}else
		if (wind == NORD){
			return NICHTS;
		}else
		if (wind == SUED){
			return NICHTS;
		}else
		return NICHTS;
	}else
	return NICHTS;
}


int main(void) {
    segeln_test();
    return 0;
}
