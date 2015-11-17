/*
Compile: make sum_even_cubes
Run: ./sum_even_cubes
*/

#include "base.h"

int sum_even_cubes(int n);
int sum_even_cubes_rec(int n);
int sum_even_cubes_rec2(int n);
void sum_even_cubes_test(void);
void sum_even_cubes_rec_test(void);
void sum_even_cubes_rec_2_test(void);

void sum_even_cubes_test(void) {
    check_within_d( sum_even_cubes(0), 0.0, EPSILON);
    check_within_d( sum_even_cubes(1), 0.0, EPSILON);
    check_within_d( sum_even_cubes(2), 8.0, EPSILON);
    check_within_d( sum_even_cubes(23),
                    (double)(0 + 2*2*2 + 4*4*4 + 6*6*6 + 8*8*8 +
                     10*10*10 + 12*12*12 + 14*14*14 +
                     16*16*16 + 18*18*18 + 20*20*20 +
                     22*22*22)
                    , EPSILON);
    check_within_d( sum_even_cubes(18),
                    (double)(0 + 2*2*2 + 4*4*4 + 6*6*6 + 8*8*8 +
                     10*10*10 + 12*12*12 + 14*14*14 +
                     16*16*16 + 18*18*18)
                    , EPSILON);
}

void sum_even_cubes_rec_test(void) {
    check_within_d( sum_even_cubes_rec(0), 0.0, EPSILON);
    check_within_d( sum_even_cubes_rec(1), 0.0, EPSILON);
    check_within_d( sum_even_cubes_rec(2), 8.0, EPSILON);
    check_within_d( sum_even_cubes_rec(23),
                    (double)(0 + 2*2*2 + 4*4*4 + 6*6*6 + 8*8*8 +
                     10*10*10 + 12*12*12 + 14*14*14 +
                     16*16*16 + 18*18*18 + 20*20*20 +
                     22*22*22)
                    , EPSILON);
    check_within_d( sum_even_cubes_rec(18),
                    (double)(0 + 2*2*2 + 4*4*4 + 6*6*6 + 8*8*8 +
                     10*10*10 + 12*12*12 + 14*14*14 +
                     16*16*16 + 18*18*18)
                    , EPSILON);
}

void sum_even_cubes_rec2_test(void) {
    check_within_d( sum_even_cubes_rec2(0), 0.0, EPSILON);
    check_within_d( sum_even_cubes_rec2(1), 0.0, EPSILON);
    check_within_d( sum_even_cubes_rec2(2), 8.0, EPSILON);
    check_within_d( sum_even_cubes_rec2(23),
                    (double)(0 + 2*2*2 + 4*4*4 + 6*6*6 + 8*8*8 +
                     10*10*10 + 12*12*12 + 14*14*14 +
                     16*16*16 + 18*18*18 + 20*20*20 +
                     22*22*22)
                    , EPSILON);
    check_within_d( sum_even_cubes_rec2(18),
                    (double)(0 + 2*2*2 + 4*4*4 + 6*6*6 + 8*8*8 +
                     10*10*10 + 12*12*12 + 14*14*14 +
                     16*16*16 + 18*18*18)
                    , EPSILON);
}

int sum_even_cubes(int n) {
    assert(n >= 0);
    int sum = 0;
    for(int i = 0; i <= n; i += 2)
        sum += i*i*i;
    return sum;
}

int sum_even_cubes_rec(int n) {
    assert(n >= 0);
    n = n - n % 2;
    if(n == 0)
        return 0;
    else
        return n*n*n + sum_even_cubes(n - 1);
}

int sum_even_cubes_rec2_helper(int n, int accumulator) {
    if(n == 0)
        return accumulator;
    else
        return sum_even_cubes_rec2_helper(n - 2, n*n*n + accumulator);
}

int sum_even_cubes_rec2(int n) {
    assert(n >= 0)
    return sum_even_cubes_rec2_helper(n - n % 2, 0);
}


void timing(void) {
    const int test_size_1 = 1e5;
    const int test_size_2 = 1e6;
    time_function(sum_even_cubes(test_size_1));
    time_function(sum_even_cubes_rec(test_size_1));
    time_function(sum_even_cubes_rec2(test_size_1));

    time_function(sum_even_cubes(test_size_2));
    time_function(sum_even_cubes_rec(test_size_2));
    time_function(sum_even_cubes_rec2(test_size_2));
/*
 * Output
 * time: 0.17 ms
 * time: 0.169 ms
 * time: 0.767 ms
 * time: 1.675 ms
 * time: 1.715 ms
 * zsh: segmentation fault (core dumped)  ./sum_even_cubes
 *
 */
}

int main(void) {
    sum_even_cubes_test();
    sum_even_cubes_rec_test();
    sum_even_cubes_rec2_test();
	timing();
}
