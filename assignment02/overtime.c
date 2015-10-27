/*
Compile: make wages
Run: ./wages
*/
 
#include "base.h"
 
/*
Design a function that computes weekly wages with overtime from hours worked.
The hourly rate is 10 €/hour. Regular working time is 40 hours/week. Overtime
is paid 150% of the normal rate of pay.
*/
 
typedef int Hours; // represents hours worked
typedef int Cents; // represents wage in cents
 
// Hours -> Cents
Cents hours_to_wages(Hours hours);
 
void hours_to_wages_test() {
    check_expect_i(hours_to_wages(0), 0);          // line 20
    check_expect_i(hours_to_wages(20), 20 * 1000); // line 21
    check_expect_i(hours_to_wages(39), 39 * 1000); // line 22
    check_expect_i(hours_to_wages(40), 40 * 1000); // line 23
    check_expect_i(hours_to_wages(41), 40 * 1000 + 1 * 1500);
    check_expect_i(hours_to_wages(45), 40 * 1000 + 5 * 1500);
}
 
// Compute the wage in cents given the number of hours worked.
Cents hours_to_wages(Hours hours) {
    if (hours <= 40) {
        return hours * 1000;
    } 
    else {
        return 40 * 1000 + (hours - 40) * 1500;
    }
}
 
int main(void) {
    hours_to_wages_test();
    return 0;
}
