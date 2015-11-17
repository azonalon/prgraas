/*
Compile: make fibonacci
Run: ./fibonacci
*/
#include "base.h"

#define own_time_function(f) {\
	clock_t t = clock();\
	f;\
	t = clock() - t;\
	printf("%g ms", t * 1000.0 / CLOCKS_PER_SEC);\
}

const int AnswerToEverything = 42;
#define ANSWER_TO_EVERYTHING 42

// positive integers expected
int fibonacci_recursive(int n);

void fibonacci_recursive_test(void) {
	check_expect_i(fibonacci_recursive(0), 0);
    check_expect_i(fibonacci_recursive(1), 1);
    check_expect_i(fibonacci_recursive(2), 1);
    check_expect_i(fibonacci_recursive(3), 2);
    check_expect_i(fibonacci_recursive(4), 3);
    check_expect_i(fibonacci_recursive(5), 5);
}

int fibonacci_recursive(int n) {
	if(n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci_recursive(n - 2) + fibonacci_recursive(n - 1);
    }
}

int fibonacci_iterative(int n);

void fibonacci_iterative_test(void) {
	check_expect_i(fibonacci_iterative(0), 0);
    check_expect_i(fibonacci_iterative(1), 1);
    check_expect_i(fibonacci_iterative(2), 1);
    check_expect_i(fibonacci_iterative(3), 2);
    check_expect_i(fibonacci_iterative(4), 3);
    check_expect_i(fibonacci_iterative(5), 5);
}

int fibonacci_iterative(int n) {
    if(n == 0) return 0;
    if(n == 1) return 1;
    int fib_n_minus_two = 0;
    int fib_n_minus_one = 1;
    int fib;
	for(int i = 2; i <= n; i++) {
        fib = fib_n_minus_two + fib_n_minus_one;
        fib_n_minus_two = fib_n_minus_one;
        fib_n_minus_one = fib;
    }
    return fib;
}

void timing(void) { printf("i\tfib(i)\ttime_iter [ms]\ttime_rec [ms]\n");
    for(int i = 0; i <= 45; i += 5) {
        printi(i); printf("\t");
        printi(fibonacci_iterative(i)); printf("\t");
        own_time_function(fibonacci_iterative(i)); printf("\t");
        own_time_function(fibonacci_recursive(i)); printf("\n");
    }
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
