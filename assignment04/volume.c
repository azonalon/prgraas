/*
Compile: make volume
Run: ./volume
*/

#include "base.h"

/*
In einem Programm sollen verschiedene Formen von geometrischen Körpern, nämlich
Zylinder, Kugel und Quader, repräsentiert werden. Entwickeln Sie eine Funktion,
die diese geometrischen Körper vararbeiten kann (Parametertyp: Shape) und das
zugehörige Volumen berechnet.
*/

const double PI = 3.1415926;

enum ShapeTag {
    TCuboid,      // tag for a cuboid
    TCylinder,    // tag for a cylinder
    TBall         // tag for a ball
};

struct Cuboid {    // width, depth and height of the cuboid
    double x;
    double y;
    double z;
};

struct Cylinder {    // radius and height of the cylinder
    double r;
    double z;
};

struct Ball {    // radius of the ball
    double r;
};

struct Shape {
    enum ShapeTag tag;               // indicate which variant follows
    union {
		struct Cuboid cuboid;        // cuboid variant
		struct Cylinder cylinder;    // cylinder variant
        struct Ball ball;            // ball variant
    };
};

// constructor for cuboid
struct Shape make_cuboid(double x, double y, double z) {
    struct Shape s;
    s.tag = TCuboid;
    s.cuboid.x = x;
    s.cuboid.y = y;
    s.cuboid.z = z;
    return s;
}

// constructor for cylinder
struct Shape make_cylinder(double r, double z) {
    struct Shape s;
    s.tag = TCylinder;
    s.cylinder.r = r;
    s.cylinder.z = z;
    return s;
}

// constructor for ball
struct Shape make_ball(double r) {
    struct Shape s;
    s.tag = TBall;
    s.cylinder.r = r;
    return s;
}

// struct Shape -> double
// Computes the volume from the given shape.
double volume(struct Shape s);

static void volume_test() {
    // test cases for cuboid variant
    check_within_d(
        volume(make_cuboid(0.0, 0.0, 0.0)),
        0.0, EPSILON);
    check_within_d(
        volume(make_cuboid(1.0, 1.0, 1.0)),
        1.0, EPSILON);
    check_within_d(
        volume(make_cuboid(1.4, 2.5, 3.6)),
        12.6, EPSILON);

    // test cases for cylinder
    check_within_d(
        volume(make_cylinder(0.0, 2.0)),
        0.0, EPSILON);
    check_within_d( 
        volume(make_cylinder(1.0, 1.0 / PI)),
        1.0, EPSILON);
    check_within_d( 
        volume(make_cylinder(1.9, 1.2)),
        PI * 1.9 * 1.9 * 1.2, EPSILON);

    // test cases for ball
    check_within_d(
        volume(make_ball(0.0)),
        0.0, EPSILON);
    check_within_d(
        volume(make_ball(1.0)),
        4.0 / 3.0 * PI, EPSILON);
    check_within_d(
        volume(make_ball(2.4)),
        4.0 / 3.0 * PI * 2.4 * 2.4 * 2.4, EPSILON);
}

// Computes the volume from the given shape.
double volume(struct Shape s) {
    switch (s.tag) {
        case TCuboid:
            return s.cuboid.x * s.cuboid.y * s.cuboid.z;
            break;
        case TCylinder:
            return PI * s.cylinder.r * s.cylinder.r * s.cylinder.z;
            break;
        case TBall:
            return 4 / 3 * PI * s.ball.r * s.ball.r * s.ball.r;
            break;
        default:
            printf("ERROR: invalid shape");
            return 0;
    }
    return 0;
}

int main(void) {
    volume_test();
    return 0;
}
