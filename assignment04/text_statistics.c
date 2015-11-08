/*
Compile: make text_statistics
Run: ./text_statistics
*/

#include "base.h"
#include "string.h"

/*
Entwickeln Sie eine Funktion zur Erstellung einer Text-Statistik. Eingabe der Funktion ist ein String beliebiger Länge. Ausgabe ist eine statistische Zusammenfassung des Strings, die folgende Komponenten enthält: Anzahl Zeichen insgesamt (inkl. Whitespace), Anzahl Buchstaben, Anzahl Wörter, Anzahl Sätze, Anzahl Zeilen. Whitespace (Leerraum) ist definiert als die Menge der Steuerzeichen Leerzeichen (' '), Tabulator ('\t'), Zeilenvorschub ('\n') und Wagenrücklauf ('\r'). Die Menge der im Eingabetext erlaubten Zeichen sind diejenigen mit einem ASCII-Code zwischen 32 (Leerzeichen) und 126 (Tilde) sowie Whitespace (also insbesondere sind keine Umlaute erlaubt). 
*/

struct Point {
    double x; // represents the x-coordinate of a point
    double y; // represents the y-coordinate of a point
};

// constructor for Point
struct Point make_point(double x, double y) {
    struct Point p = { x, y };
    return p;
}

// struct Point -> double
// Computes the distance from the given point
// to the origin of the coordinate system.
double text_statistics(struct Point p);

static void text_statistics_test() {
    check_within_d(text_statistics(make_point(0, 0)),
        0.0, EPSILON);
    check_within_d(text_statistics(make_point(1, 0)),
        1.0, EPSILON);
    check_within_d(text_statistics(make_point(-1, 0)),
        1.0, EPSILON);
    check_within_d(text_statistics(make_point(0, 2)),
        2.0, EPSILON);
    check_within_d(text_statistics(make_point(0, -2)),
        2.0, EPSILON);
    check_within_d(text_statistics(make_point(3, 4)),
        5.0, EPSILON);
    check_within_d(text_statistics(make_point(3, -4)),
        5.0, EPSILON);
}

// Computes the distance from the given point
// to the origin of the coordinate system.
double text_statistics(struct Point p) {
    return sqrt(p.x * p.x + p.y * p.y); // square root math.h
}

int main(void) {
    text_statistics_test();
    return 0;
}
