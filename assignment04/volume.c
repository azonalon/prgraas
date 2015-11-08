/*
Compile: make volume
Run: ./volume
*/

#include "base.h"

/*
In einem Programm sollen verschiedene Formen von geometrischen Körpern, nämlich Zylinder, Kugel und Quader, repräsentiert werden. Entwickeln Sie eine Funktion, die diese geometrischen Körper vararbeiten kann (Parametertyp: Shape) und das zugehörige Volumen berechnet.
*/

enum PointTag {
    TPointEuclid, // tag for a point in Euclidean coordinates
    TPointPolar   // tag for a point in polar coordinates
};

struct EuclideanPoint {
    double x;
    double y;
};

struct PolarPoint {
    double theta;
    double magnitude;
};

struct Point {
    enum PointTag tag;                // indicate which variant follows
    union {
		struct EuclideanPoint euclid; // Euclidean variant
		struct PolarPoint polar;      // polar variant
    };
};

// constructor for PointEuclid
struct Point make_point_euclid(double x, double y) {
    struct Point p;
    p.tag = TPointEuclid;
    p.euclid.x = x;
    p.euclid.y = y;
    return p;
}

// constructor for PointPolar
struct Point make_point_polar(double t, double m) {
    struct Point p;
    p.tag = TPointPolar;
    p.polar.theta = t;
    p.polar.magnitude = m;
    return p;
}

// struct Point -> double
// Computes the distance from the given point
// to the origin of the coordinate system.
double volume(struct Point p);

static void volume_test() {
    // test cases for polar variant
    check_within_d(
        volume(make_point_polar(0.0, 0.0)), 
        0.0, EPSILON);
    check_within_d(
         volume(make_point_polar(0.0, 1.0)), 
        1.0, EPSILON);
    check_within_d(
        volume(make_point_polar(2.3, 2.0)), 
        2.0, EPSILON);

    // test cases for Euclidean variant
    check_within_d(
        volume(make_point_euclid(0.0, -2.0)), 
        2.0, EPSILON);
    check_within_d( 
        volume(make_point_euclid(2.0, 0.0)), 
        2.0, EPSILON);
    check_within_d( 
        volume(make_point_euclid(1.0, 1.0)), 
        sqrt(2.0), EPSILON); // square root
}

// Computes the distance from the given point
// to the origin of the coordinate system.
double volume(struct Point p) {
    switch (p.tag) {
        case TPointEuclid:
            return sqrt(p.euclid.x * p.euclid.x + p.euclid.y * p.euclid.y); // square root
        case TPointPolar:
            return p.polar.magnitude;
    }
    return 0;
}

int main(void) {
    volume_test();
    return 0;
}
