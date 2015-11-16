/*
Compile: make people
Run: ./people
*/

#include "base.h"
#include "string.h"

// a) struct Statistics ...

struct Statistics {
    int mean_year;
    int males;
    int females;
    double mean_height_males;
    double mean_height_females;
};

struct TotalStatistics {
    int total_years;
    int total_males;
    int total_females;
    double total_height_males;
    double total_height_females;
};

// b) ... make_statistics...

struct Statistics make_statistics(void) {
    struct Statistics s = {0, 0, 0, 0.0, 0.0};
    return s;
}

struct TotalStatistics make_total_statistics(void) {
    struct TotalStatistics t = {0, 0, 0, 0.0, 0.0}
    return t;
}

// c) ... print_statistics...

double round_two_decimal_places(double x) {
    return (double) ((int) (100 * x)) / 100;
}

void print_statistics(struct Statistics s) {
    printf("mean year: ");
    printi(s.mean_year);
    printf("\n");
    
    printf("number males: ");
    printi(s.males);
    printf("\n");
    
    printf("number females: ");
    printi(s.females);
    printf("\n");
    
    printf("mean height males: ");
    printd(round_two_decimal_places(s.mean_height_males));
    printf("\n");
    
    printf("mean height females: ");
    printd(round_two_decimal_places(s.mean_height_females));
    printf("\n");
}

// d) ... compute_statistics...

double mean(double total, int number_of_values) {
    return total / number_of_values;
}

struct Statistics compute_statistics(String data) {
    s = make_statistics();
    t = make_total_statistics();
    int number_of_values = 0;
    int passed_first_line = 0;
    for(int i = 0; i < s_length(data); i++) {
        if(s_get(data, i) == '\n') passed_first_line = 1;
        if(passed_first_line) {
            t.total_years += i_of_s(s_sub(data, i, i + 4));
            if(s_get(data, i + 5) == 'm') {
                t.total_males++;
                t.total_height_males += d_of_s(s_sub(data, i + 7, i + 11));
            } else {
                t.total_females++;
                t.total_height_females += d_of_s(s_sub(data, i + 7, i + 11));
            }
        }
        i += 10;
    }
    s.mean_year = mean(t.total_years, number_of_values);
    s.males = t.total_males;
    s.females = t.total_females;
    s.mean_height_males = mean(t.total_height_males, number_of_values);
    s.mean_height_females = mean(t.total_height_females, number_of_values);
}

// e) header file...

int main(void) {
	String table = s_read_file("people10.txt");
	printsln(table);
	// ... compute_statistics(table);
	// print_statistics(...);
	return 0;
}
