/*
Compile: make fibonacci
Run: ./fibonacci
*/

#include "base.h"

int fibonacci_recursive(int n);

void fibonacci_recursive_test(void) {
	// a)
}

int fibonacci_recursive(int n) {
	// b)
	return 0;
}

int fibonacci_iterative(int n);

void fibonacci_iterative_test(void) {
	// a)
}

int fibonacci_iterative(int n) {
	// c)
	return 0;
}

void timing(void) {
	// d)
}
/*
d)
i   fib(i)  time_iter [ms]  time_rek [ms]
0...
5...
...
45...
*/

int main(void) {
    fibonacci_recursive_test();
    fibonacci_iterative_test();
    timing();
}
