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
    //p -> first_name = xmalloc(s_length(first) * sizeof(char));
    p -> first_name = first;
    //p -> last_name = xmalloc(s_length(last) * sizeof(char));
    p -> last_name = last;
    p -> year_of_birth = year_of_birth;
    //p -> occupation = xmalloc(s_length(occupation) * sizeof(char));
    p -> occupation = occupation;
    return p;
}

void println_person(Person *p) {
    printf("(%s, %s, %d, %s)\n", p -> first_name, p -> last_name, p -> year_of_birth, p -> occupation);
}

void free_person(Person *p) {
    //free(p -> first_name);
    //free(p -> last_name);
    //free(p -> occupation);
    free(p);
}

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
/*int compare_first_name2(const void *a, const void *b) {
    return s_compare(a -> first_name, b -> first_name);
}*/

// todo: modify
void swap(Person* a[], int i, int j) {
    Person* tmp = make_person(
        a[i] -> first_name, a[i] -> last_name, a[i] -> year_of_birth, a[i] -> occupation);
    a[i] = a[j];
    a[j] = tmp;
    free_person(tmp);
}

// todo: modify
void quicksort(Person* a[], int left, int right, PersonComparator cmp);

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
    quicksort(a, 0, na - 1, compare_first_name);
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
void quicksort(Person* a[], int left, int right, PersonComparator cmp) {
    if (left >= right) return; // 0 or 1 elements, recursion end
    swap(a, left, (left + right) / 2); // move pivot element to left
    int j = left;
    for (int i = left + 1; i <= right; i++) {
        if (cmp(a[i], a[left]) == LT) {
            swap(a, ++j, i);
        }
        // assert: v[i] < v[left] for i = left+1..j
    }
    swap(a, left, j); // move back pivot element
    quicksort(a, left, j-1, cmp); // assert: v[i] < v[j] for i = left..j-1
    quicksort(a, j+1, right, cmp); // assert: v[i] >= v[j] for i = j+1..right
}

int main(void) {
    base_init();
    base_set_memory_check(true);
    quicksort_test();
    return 0;
}
