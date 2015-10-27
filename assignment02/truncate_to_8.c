/*
Compile: make truncate_to_8
Run: truncate_to_8
*/

#include "base.h"
#include "string.h"
 
/*
Design a function that cuts strings to length 8 and truncates the rest of the
string.
*/
 
typedef String TruncatedString; // the output of the function
 
// String -> TruncatedString
TruncatedString truncate_to_8(String input);
 
void truncate_to_8_test() {
    check_expect_s(truncate_to_8("bla"), "bla");            // no truncation
    check_expect_s(truncate_to_8("blablabl"), "blablabl");  // no truncation
    check_expect_s(truncate_to_8("blablabla"), "blablabl"); // truncation
}
 
// Return a truncated string of length 8 given a string of arbitrary length.
TruncatedString truncate_to_8(String input) {
    if (s_length(input) <= 8) {
        return input;
    } else {
        return s_sub(input, 1, 8);
    }
}


int main(void) {
    truncate_to_8_test();
    return 0;
}
