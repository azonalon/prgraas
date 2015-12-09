/*
Compile: make sort_persons
Run: ./sort_persons
*/

#include "base.h" // http://hci.uni-hannover.de/files/prog1lib/base_8h.html
#include "string.h" // http://hci.uni-hannover.de/files/prog1lib/string_8h.html

struct Person {
    String first_name;
    String last_name;
    int year_of_birth;
    String occupation;
};
typedef struct Person Person;

Person *make_person(String first, String last, int year_of_birth, String occupation) {
    Person* p = xmalloc(sizeof(Person));
    p -> first_name = xmalloc(s_length(first) * sizeof(char));
    p -> first_name = first;
    p -> last_name = xmalloc(s_length(last) * sizeof(char));
    p -> last_name = last;
    p -> year_of_birth = year_of_birth;
    p -> occupation = xmalloc(s_length(occupation) * sizeof(char));
    p -> occupation = occupation;
}

void println_person(Person *p) {
    String output = s_concat(s_concat(s_concat(s_concat(s_concat(s_concat(
        "(", p -> first_name), ", "), p -> last_name), ", %d, "), p -> occupation), ")");
    printf(output, p -> year_of_birth);
}

void free_person(Person *p) {
    free(p -> first_name);
    free(p -> last_name);
    free(p -> occupation);
    free(p);
}

/*
typedef enum {
    LT = -1,    // less than
    EQ = 0,     // equal
    GT = 1      // greater than
} CmpResult;
*/

typedef CmpResult (*PersonComparator)(Person *a, Person *b);

// todo: implement
CmpResult compare_first_name(Person *a, Person *b) {
    return s_compare(a -> first_name, b -> first_name);
}

// todo: implement
CmpResult compare_last_name(Person *a, Person *b) {
    return s_compare(a -> last_name, b -> last_name);
}

// todo: implement
CmpResult compare_year(Person *a, Person *b) {
    if(a -> year_of_birth == b -> year_of_birth) {
        return EQ;
    } else if(a -> year_of_birth > b -> year_of_birth) {
        return LT;
    } else {
        return GT;
    }
}

// todo: implement
CmpResult compare_occupation(Person *a, Person *b) {
    return s_compare(a -> occupation, b -> occupation);
}

// todo: implement (with qsort)
int compare_first_name2(const void *u, const void *v) {
    return 0;
}

// todo: modify
void swap(int v[], int i, int j) {
    int a = v[i];
    v[i] = v[j];
    v[j] = a;
}

// todo: modify
void quicksort(int v[], int left, int right, PersonComparator cmp);

void quicksort_test(void) {
    Person *a[4];
    a[0] = make_person("Albert", "Einstein", 1879, "Physiker");
    a[1] = make_person("Konrad", "Zuse", 1910, "Bauingenieur");
    a[2] = make_person("Jimi", "Hendrix", 1942, "Gitarrist");
    a[3] = make_person("Gottfried Wilhelm", "Leibniz", 1646, "Philosoph");
    int na = sizeof(a) / sizeof(Person*); // sizeof(a): number of bytes

    for (int i = 0; i < na; i++) {
        println_person(a[i]);
    }

    // todo: uncomment one at a time
//  quicksort(a, 0, na - 1, compare_first_name);
//  quicksort(a, 0, na - 1, compare_last_name);
//  quicksort(a, 0, na - 1, compare_year);
//  quicksort(a, 0, na - 1, compare_occupation);

//	qsort(a, na, sizeof(Person*), compare_first_name2);

    println();
    for (int i = 0; i < na; i++) {
        println_person(a[i]);
    }

    for (int i = 0; i < na; i++) {
        free_person(a[i]);
    }

}

// todo: modify
void quicksort(int v[], int left, int right, PersonComparator cmp) {
    if (left >= right) return; // 0 or 1 elements, recursion end
    swap(v, left, (left + right) / 2); // move pivot element to left
    int j = left;
    for (int i = left + 1; i <= right; i++) {
        if (v[i] < v[left]) {
            swap(v, ++j, i);
        }
        // assert: v[i] < v[left] for i = left+1..j
    }
    swap(v, left, j); // move back pivot element
    quicksort(v, left, j-1, cmp); // assert: v[i] < v[j] for i = left..j-1
    quicksort(v, j+1, right, cmp); // assert: v[i] >= v[j] for i = j+1..right
}

int main(void) {
    base_init();
    base_set_memory_check(true);
    quicksort_test();
    return 0;
}
