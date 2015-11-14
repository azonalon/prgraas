/*
Compile: make volume
Run: ./volume
*/

#include "base.h"

/*
In einem Programm sollen verschiedene Formen von geometrischen Körpern, nämlich Zylinder, Kugel und Quader, repräsentiert werden. Entwickeln Sie eine Funktion, die diese geometrischen Körper vararbeiten kann (Parametertyp: Shape) und das zugehörige Volumen berechnet.
*/

const double pi = 3.141592653589793; // Die Zahl PI welche für die Berechnung des Kreises wichtig ist

double vol; // hilfsvariable, wenn das volumen negativ

enum Volumenversch {
    TVolumenQuarderEuclid, //
    TVolumenKugelPolar,   //
	TVolumenZylinderPolar //
};

struct VolumenQuarderEuclid {
    double x;
    double y;
	double z;
};

struct VolumenKugelPolar {
    double RadiusKugel;
};

struct VolumenZylinderPolar {
    double RadiusZylinder;
	double HoeheZylinder;
};

struct Volumen {
    enum Volumenversch tag;
    union {
		struct VolumenQuarderEuclid euclid;
		struct VolumenKugelPolar polar;
		struct VolumenZylinderPolar polare;
    };
};

// constructor für VolumenQuader
struct Volumen make_VolumenQuarder_euclid(double x, double y, double z) {
    struct Volumen p;
    p.tag = TVolumenQuarderEuclid;
    p.euclid.x = x;
    p.euclid.y = y;
	p.euclid.z = z;
    return p;
}

// constructor für VolumenKugel
struct Volumen make_VolumenKugel_polar(double rku) {
    struct Volumen p;
    p.tag = TVolumenKugelPolar;
    p.polar.RadiusKugel = rku;
    return p;
}

// constructor für VolumenZylinder
struct Volumen make_VolumenZylinder_polare(double r, double h) {
    struct Volumen p;
    p.tag = TVolumenZylinderPolar;
    p.polare.RadiusZylinder = r;
	p.polare.HoeheZylinder = h;
    return p;
}



double volume(struct Volumen p);




static void volume_test() {
    // test für die Kugel (Radius)
    check_within_d(
        volume(make_VolumenKugel_polar(0.0)),
        0.0, EPSILON);
    check_within_d(
         volume(make_VolumenKugel_polar(1.0)),
        pi*4./3., EPSILON);
    check_within_d(
        volume(make_VolumenKugel_polar(2.0)),
        33.510321638291124, EPSILON);

    // test für den Quarder (x, y, z)
    check_within_d(
        volume(make_VolumenQuarder_euclid(0.0, -2.0, 2.0)),
        0.0, EPSILON);
    check_within_d(
        volume(make_VolumenQuarder_euclid(2.0, -2.0, 2.0)),
		8.0, EPSILON);
    check_within_d(
        volume(make_VolumenQuarder_euclid(1.0, 1.0, 1.0)),
        1.0, EPSILON);


	// test für den Zylinder (Radius, Hoehe)
	check_within_d(
        volume(make_VolumenZylinder_polare(3.0, 2.0)),
        56.54866776, EPSILON);
    check_within_d(
         volume(make_VolumenZylinder_polare(1.0, 2.0)),
        6.2831853071795, EPSILON);
    check_within_d(
        volume(make_VolumenZylinder_polare(0.5, 2.0)),
        1.57079632679, EPSILON);
}



// Berechnet das Volumen der einzelnen Körper
double volume(struct Volumen p) {
    if (p.tag==TVolumenQuarderEuclid) {
        vol = p.euclid.x * p.euclid.y * p.euclid.z;
		if (vol < 0) {
			return vol * (-1);
		} else {
			return vol;
		}
	}

	if (p.tag==TVolumenKugelPolar){
       vol = (4./3.)*p.polar.RadiusKugel*p.polar.RadiusKugel*p.polar.RadiusKugel* pi;
	   if (vol < 0){
		   return vol * (-1);
	   } else {
		   return vol;
	   }

    }

	if (p.tag==TVolumenZylinderPolar){
		vol = p.polare.RadiusZylinder * p.polare.RadiusZylinder * p.polare.HoeheZylinder * pi;
		if (vol < 0){
			return vol * (-1);
		} else {
			return vol;
		}
	}
    return 0;


}

int main(void) {
    volume_test();
    return 0;
}
