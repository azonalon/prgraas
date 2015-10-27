/*
Compile: make overtime
Run: overtime
*/
 
#include "base.h"
 
/*
Design a function that computes how much overtime has been worked given an 
overall worktime.
*/
 
typedef int Hours; // represents hours worked
 
// Hours -> Hours
Hours overtime_worked(Hours hours);
 
void overtime_worked_test() {
    check_expect_i(overtime_worked(30), 0);  // below regular time
    check_expect_i(overtime_worked(40), 0);  // regular time
    check_expect_i(overtime_worked(50), 10); // 10 hours overtime
}

const Hours WEEKLY_HOURS = 40; // regular work hours per week
 
// Compute the ovetime in hours given the number of hours worked.
Hours overtime_worked(Hours hours) {
    if (hours <= WEEKLY_HOURS) {
        return 0;
    } else {
        return hours - WEEKLY_HOURS;
    }
}
 
int main(void) {
    overtime_worked_test();
    return 0;
}
