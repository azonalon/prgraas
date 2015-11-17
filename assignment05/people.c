/*
Compile: make people
Run: ./people
*/

#include "base.h"
#include "string.h"
#include "people.h"

// void -> struct Statistics
// Return struct Statistics with all values set to zero.
struct Statistics make_statistics(void) {
    struct Statistics s = {0, 0, 0, 0.0, 0.0};
    return s;
}

// void -> struct TotalStatistics
// Return struct TotalStatistics with all values set to zero.
struct TotalStatistics make_total_statistics(void) {
    struct TotalStatistics t = {0, 0, 0, 0.0, 0.0};
    return t;
}

// double -> double
// Return a rounded double with two decimal places given a double.
double round_two_decimal_places(double x) {
    if((int) (1000 * x) % 10 < 5) {    // third decimal place is < 5
        return (double) ((int) (100 * x)) / 100;    // keep first two places
    } else {    // third decimal place is > 5
        return (double) (((int) (100 * x)) + 1) / 100;    // round up
    }
}

// double, int -> double
// Return the mean value given the sum of all values and the number of values.
double mean(double total, int number_of_values) {
    if(number_of_values != 0) {
        return total / number_of_values;
    } else {
        return 0;
    }
}

// struct Statistics -> void
// Print the data contained in struct Statistics.
void print_statistics(struct Statistics s) {
    printf("mean year: ");    // print mean year
    printi(s.mean_year);
    printf("\n");
    
    printf("number males: ");
    printi(s.males);
    printf("\n");
    
    printf("number females: ");
    printi(s.females);
    printf("\n");
    
    printf("mean height males: ");    // print rounded mean height of males
    printd(round_two_decimal_places(s.mean_height_males));
    printf("\n");
    
    printf("mean height females: ");
    printd(round_two_decimal_places(s.mean_height_females));
    printf("\n");
}

// String -> struct
// Compute the values described by struct Statistics given a table of data.
struct Statistics compute_statistics(String table) {
    struct Statistics s = make_statistics();
    struct TotalStatistics t = make_total_statistics();
    int number_of_values = 0;
    for(int i = 16; i < s_length(table); i++) {    // start counting after head
        t.total_years += i_of_s(s_sub(table, i, i + 4));
        if(s_get(table, i + 5) == 'm') {    // if line describes male
            t.total_males++;
            t.total_height_males += d_of_s(s_sub(table, i + 7, i + 11));
        } else {
            t.total_females++;
            t.total_height_females += d_of_s(s_sub(table, i + 7, i + 11));
        }
        number_of_values++;    // count number of lines
        i += 11;    // go to last index of the line
    }
    s.mean_year = mean(t.total_years, number_of_values);    // calculate mean
    s.males = t.total_males;
    s.females = t.total_females;
    s.mean_height_males = mean(t.total_height_males, t.total_males);
    s.mean_height_females = mean(t.total_height_females, t.total_females);
    return s;
}

int main(void) {
	String table = s_read_file("people.txt");
	printsln(table);
	struct Statistics s = compute_statistics(table);
	print_statistics(s);
	return 0;
}
