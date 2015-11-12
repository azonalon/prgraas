/*
Compile: make text_statistics
Run: ./text_statistics
*/

#include "base.h"
#include "string.h"

/*
Entwickeln Sie eine Funktion zur Erstellung einer Text-Statistik. Eingabe der
Funktion ist ein String beliebiger Länge. Ausgabe ist eine statistische
Zusammenfassung des Strings, die folgende Komponenten enthält: Anzahl Zeichen
insgesamt (inkl. Whitespace), Anzahl Buchstaben, Anzahl Wörter, Anzahl Sätze,
Anzahl Zeilen. Whitespace (Leerraum) ist definiert als die Menge der
Steuerzeichen Leerzeichen (' '), Tabulator ('\t'), Zeilenvorschub ('\n') und
Wagenrücklauf ('\r'). Die Menge der im Eingabetext erlaubten Zeichen sind
diejenigen mit einem ASCII-Code zwischen 32 (Leerzeichen) und 126 (Tilde) sowie
Whitespace (also insbesondere sind keine Umlaute erlaubt).
*/

/*
 * A text is reduced to its number of words, letters,
 * lines and overall characters.
 */

struct TextStatistic {
    int letters; // any character in the english alphabet
    int words; // sequence of letters
    int characters; // any character including control characters
    int lines; // number of character sequences excluding \n
    int sentences; // number of character sequences excluding \n
};

// constructor TextStatistic
struct TextStatistic make_text_statistic(int letters, int words,
                                         int characters, int lines,
                                         int sentences ) {
    struct TextStatistic statistic = {
        .letters=letters,
        .words=words,
        .characters=characters,
        .lines=lines,
        .sentences=sentences
    };
    return statistic;
}

struct TextStatistic invalid_text_statistic() {
    // for cases where a text does not contain valid characters
    struct TextStatistic s = {
        -1, -1, -1, -1, -1
    };
    return s;
}

bool is_valid_char(char c) {
    return c >= 32 && c <= 126;
    // this range is stated by the assignment
}

bool is_whitespace(char c) {
    return c == ' ' || c == '\r' || c == '\n' || c == ' ' || c == '\t';
}

bool is_newline(char c){
    return c == '\n' || c == '\r';
}

bool is_dot(char c) {
    return c == '.';
}

bool is_letter(char c) {
    return ( c >= 65 && c <= 90 ) || ( c >= 97 && c <= 122);
    // The first case is A-Z, the second a-z
}

String test_1 = "The most merciful thing in the world, I think, \n\
is the inability of the human mind to correlate all \n\
its contents.";
struct TextStatistic test_1_correct = {
                                       .lines = 3,
                                       .characters = 114,
                                       .letters = 114 - 25,
                                       .words = 21,
                                       .sentences = 1,
                                       };

String test_2 = "Ph'nglui. mglw'nafh. \n Cthulhu. R'lyeh wgah'nagl fhtagn.";
struct TextStatistic test_2_correct = {
                                       .lines = 2,
                                       .characters = 56  ,
                                       .letters = 56 - 15,
                                       .words = 6,
                                       .sentences = 4,
                                       };

String test_3 = "Before this sentence is an escape character";
struct TextStatistic test_3_correct = {
                                       .lines = -1,
                                       .characters = -1,
                                       .letters = -1,
                                       .words = -1,
                                       .sentences = -1,
                                       };

String test_4 = "What happens, if I write...?";
struct TextStatistic test_4_correct = {
                                       .lines = 1,
                                       .characters = 28,
                                       .letters = 28 - 9,
                                       .words = 5,
                                       .sentences = 3,
                                       };

String test_5 = "I don't want to write a fifth test case.";
struct TextStatistic test_5_correct = {
                                       .lines = 1,
                                       .characters = 40,
                                       .letters = 40 - 10,
                                       .words = 9,
                                       .sentences = 1,
                                       };

// String -> struct TextStatistic
// gives the number of letters, words, characters and lines.
struct TextStatistic text_statistics(String text);

bool check_expect_statistics(struct TextStatistic correct,
                             struct TextStatistic test) {
    return
        check_expect_i(correct.characters , test.characters) &&
        check_expect_i(correct.letters    , test.letters   ) &&
        check_expect_i(correct.sentences  , test.sentences ) &&
        check_expect_i(correct.words      , test.words     ) &&
        check_expect_i(correct.lines      , test.lines     )
        ;
}


void text_statistics_test(){
    check_expect_statistics(text_statistics(test_1), test_1_correct);
    check_expect_statistics(text_statistics(test_2), test_2_correct);
    check_expect_statistics(text_statistics(test_3), test_3_correct);
    check_expect_statistics(text_statistics(test_4), test_4_correct);
    check_expect_statistics(text_statistics(test_5), test_5_correct);
}

// gives the number of letters, words, characters and lines.
struct TextStatistic text_statistics(String text) {
    struct TextStatistic s = {0, 1, 0, 1, 0};
    int i = 0;
    int len = s_length(text);
    bool last_was_whitespace = false;
    while(i < len) {
        char c = s_get(text, i);
        s.characters++;

        if(is_letter(c)) {
            s.letters++;
            last_was_whitespace = false;
        } else if(is_whitespace(c)) {
            if(!last_was_whitespace)
                s.words++;
            if(is_newline(c)) {
                s.lines++;
            }
            last_was_whitespace = true;
        } else if (is_dot(c)) {
            s.sentences++;
            last_was_whitespace = false;
        } else if(!is_valid_char(c)) {
            return invalid_text_statistic();
            printf("%s\n", &c);
        }

        i++;
    }
    return s;
}

int main(void) {
    text_statistics_test();
    return 0;
}
