#include "base.h"
#include "string.h"

// values for the statistics
struct Statistics {
    int mean_year;
    int males;
    int females;
    double mean_height_males;
    double mean_height_females;
};

// statistics with total values instead of mean values
struct TotalStatistics {
    int total_years;
    int total_males;
    int total_females;
    double total_height_males;
    double total_height_females;
};

// void -> struct Statistics
// Return struct Statistics with all values set to zero.
struct Statistics make_statistics(void);

// void -> struct TotalStatistics
// Return struct TotalStatistics with all values set to zero.
struct TotalStatistics make_total_statistics(void);

// double -> double
// Return a rounded double with two decimal places given a double.
double round_two_decimal_places(double x);

// double, int -> double
// Return the mean value given the sum of all values and the number of values.
double mean(double total, int number_of_values);

// struct Statistics -> void
// Print the data contained in struct Statistics.
void print_statistics(struct Statistics s);

// String -> struct
// Compute the values described by struct Statistics given a table of data.
struct Statistics compute_statistics(String table);