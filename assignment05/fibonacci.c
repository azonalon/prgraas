/*
Compile: make fibonacci
Run: ./fibonacci
*/

#include "base.h"
#define own_time_function(f) {\
	clock_t t = clock();\
	f;\
	t = clock() - t;\
	printf("%g", t * 1000.0 / CLOCKS_PER_SEC);\
}

/*
Write two functions to calculate Fibonacci numbers. One function should work
recursively, the other iteratively. Print a table with the time of calculation
of both variants for 0, 5, 10, ..., 45.
*/

// int -> int
// Return the Fibonacci number f(n) for given n using recursion (expect n > 0).
int fibonacci_recursive(int n);

// Implement test cases for iteration.
void fibonacci_recursive_test(void) {
	check_expect_i(fibonacci_recursive(0), 0);
    check_expect_i(fibonacci_recursive(1), 1);
    check_expect_i(fibonacci_recursive(2), 1);
    check_expect_i(fibonacci_recursive(3), 2);
    check_expect_i(fibonacci_recursive(4), 3);
    check_expect_i(fibonacci_recursive(5), 5);
}

// int -> int
// Return the Fibonacci number f(n) for given n using recursion (expect n > 0).
int fibonacci_recursive(int n) {
	if(n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {    //use recursion formula if n > 1
        return fibonacci_recursive(n - 2) + fibonacci_recursive(n - 1);
    }
}

// int -> int
// Return the Fibonacci number f(n) for given n using iteration (expect n > 0).
int fibonacci_iterative(int n);

// Implement test cases for iteration.
void fibonacci_iterative_test(void) {
	check_expect_i(fibonacci_iterative(0), 0);
    check_expect_i(fibonacci_iterative(1), 1);
    check_expect_i(fibonacci_iterative(2), 1);
    check_expect_i(fibonacci_iterative(3), 2);
    check_expect_i(fibonacci_iterative(4), 3);
    check_expect_i(fibonacci_iterative(5), 5);
}

// int -> int
// Return the Fibonacci number f(n) for given n using iteration (expect n > 0).
int fibonacci_iterative(int n) {
    if(n == 0) return 0;
    if(n == 1) return 1;
    int fib_n_minus_two = 0;    // set start values
    int fib_n_minus_one = 1;
    int fib;
    // Start with calculation of the second Fibonacci number and iterate to n.
	for(int i = 2; i <= n; i++) {
        fib = fib_n_minus_two + fib_n_minus_one;    // use recursion formula
        fib_n_minus_two = fib_n_minus_one;          // shift indices
        fib_n_minus_one = fib;
    }
    return fib;
}

// Print table of Fibonacci numbers and time of calculation for both variants.
void timing(void) {
    // print head of the table
    printf("i\tfib(i)\t\ttime_iter [ms]\ttime_rec [ms]\n");
    for(int i = 0; i <= 45; i += 5) {    // evaluate and print values
        printi(i); printf("\t");
        if(fibonacci_iterative(i) <= 9999999) {    // test if second tab needed
            printi(fibonacci_iterative(i)); printf("\t\t");
        } else {
            printi(fibonacci_iterative(i)); printf("\t");
        }
        own_time_function(fibonacci_iterative(i)); printf("\t\t");
        own_time_function(fibonacci_recursive(i)); printf("\n");
    }
}

/*
The output is:
i       fib(i)          time_iter [ms]  time_rec [ms]
0       0               0               0
5       5               0               0
10      55              0               0
15      610             0               0
20      6765            0               0
25      75025           0               0
30      832040          0               31
35      9227465         0               328
40      102334155       0               3718
45      1134903170      0               41393
*/

int main(void) {
    fibonacci_recursive_test();
    fibonacci_iterative_test();
    timing();
}
