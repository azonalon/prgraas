/*
Compile: make truncate_to_n
Run: truncate_to_n
*/

#include "base.h"
#include "string.h"
 
/*
Design a function that cuts strings to length n and truncates the rest of the
string.
*/
 
typedef int Length;             // the length of the output
typedef String TruncatedString; // the output of the function
 
// (String, int) -> TruncatedString
TruncatedString truncate_to_n(String input, Length n);
 
void truncate_to_n_test() {
    check_expect_s(truncate_to_n("a", 2), "a");              // no truncation
    check_expect_s(truncate_to_n("ab", 2), "ab");            // no truncation
    check_expect_s(truncate_to_n("abc", 2), "ab");           // truncation
    check_expect_s(truncate_to_n("bla", 6), "bla");          // no truncation
    check_expect_s(truncate_to_n("blabla", 6), "blabla");    // no truncation
    check_expect_s(truncate_to_n("blablabla", 6), "blabla"); // truncation
}
 
/* Return a truncated string of length n
given a string of arbitrary length and n.
*/
TruncatedString truncate_to_n(String input, Length n) {
    if (s_length(input) <= n) {
        return input;
    } else {
        return s_sub(input, 0, n);
    }
}


int main(void) {
    truncate_to_n_test();
    return 0;
}
