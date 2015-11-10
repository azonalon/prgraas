/*
Design a function to contol and run an air conditioner.
It should heat up under 18.5°C and start cooling down over 22.2°C
*/

#include "base.h"

// make climate_control && ./climate_control;

enum Temperatur {
	Temp
}

typedef int Temp; // represents the tempreture

struct Temp double


// Check functions to monitor results of the operation.
static void Temperatur_test() {
	check_expect_i (Temp >= (18.5) && Temp <= (22.2) , 0 )
	check_expect_i (Temp ! < (18.5) && Temp ! > (22.2) , 0 )
	check_expect_i (Temp < (18.5) , 1 )
	check_expect_i (Temp > (22.2) , 1 )
}	


//	Operation to control the air conditioner.
De Temperatur_Status (De Grad Celsius) {
		if (Temp >= (18.5) && Temp <= (22.2)) {
		printsln("akkurate Temperatur");
		return 0;
	}	if (Temp < (18.5)) {
		printsln("Frostschutz aktivieren");
		return 1;
	}	if (Temp > (22.2)) {
		printsln("Eiswürfel Feuer frei");
		return 1;
	}	}
	
int main(void)	{
	climate_control();
	return0;
}