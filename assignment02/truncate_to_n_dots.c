/*
Compile: make truncate_to_n_dots
Run: truncate_to_n_dots
*/

#include "base.h"
#include "string.h"

/*
Design a function that cuts strings to length n and truncates the rest of the
string. If a part of the string is truncated the last three characters should
be replaced by "..." (only if the length of the string is <= 3).
*/


// (String, int) -> String
String truncate_to_n_dots(String input, int length);

void truncate_to_n_dots_test() {
    check_expect_s(truncate_to_n_dots("hu", 3), "hu");            // no truncation
    check_expect_s(truncate_to_n_dots("huh", 3), "huh");          // no truncation
    check_expect_s(truncate_to_n_dots("huhu", 3), "huh");         // truncation
    check_expect_s(truncate_to_n_dots("bla", 6), "bla");          // no truncation
    check_expect_s(truncate_to_n_dots("blabla", 6), "blabla");    // no truncation
    check_expect_s(truncate_to_n_dots("blablabla", 6), "bla..."); // truncation
}

/* Return a string of length n consisting of the first characters and "..." if
a part was trauncated given a string of arbitrary length and n.
*/
String truncate_to_n_dots(String input, int length) {
    if (s_length(input) <= length) {
        return input;
    } else if(length <= 3) {
        return s_sub(input, 0, length);
    } else {
        return s_concat(s_sub(input, 0, length-3), "...");
    }
}


int main(void) {
    truncate_to_n_dots_test();
    return 0;
}
