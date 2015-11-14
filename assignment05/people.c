/*
Compile: make people
Run: ./people
*/

#include "base.h"
#include "string.h"

// a) struct Statistics ...

// b) ... make_statistics...

// c) ... print_statistics...

// d) ... compute_statistics...

// e) header file...

int main(void) {
	String table = s_read_file("people10.txt");
	printsln(table);
	// ... compute_statistics(table);
	// print_statistics(...);
	return 0;
}
