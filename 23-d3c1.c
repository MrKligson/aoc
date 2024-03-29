#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Neighbor
{
    int row;
    int column;
} Neighbor;

// #define FILENAME "text/test.txt"
// #define n_lines 10
// #define n_columns 10
#define FILENAME "text/23-d3c1.txt"
#define n_lines 140
#define n_columns 140

char buffer[n_lines][n_columns + 1];

void read_line(FILE *, int);
int get_total(int);

int main(int argc, char **argv)
{
    FILE *input = fopen(FILENAME ,"r");
    if (input == NULL) {
        printf("Couldn't open file: %s", FILENAME);
        return 1;
    }

    int lines_read = 0;
    while (lines_read < 2) {
        // fill buffer_lines 0, 1
        read_line(input, lines_read);
        lines_read++;
    }

    long int total = 0;
    while (lines_read < n_lines) {
        read_line(input, lines_read);
        printf("%ld", total);
        total += get_total(lines_read - 1);
        printf("%ld\n", total);
        lines_read++;
    }

    fclose(input);
    printf("%ld\n", total);
}

void read_line(FILE * input, int line)
{
    int pos = 0;
    char c;
    while ((c = fgetc(input)) != '\n' && c != EOF) {
        buffer[line][pos] = c == '.' ? '\0' : c;
        pos++;
    }
    buffer[line][n_columns] = '\0';

}

int get_total(int line)
{
    int total = 0;
    for (int i = 1; i < n_columns; i++) {
        if (buffer[line][i] == '\0' || isdigit(buffer[line][i])) {
            continue;
        }

        Neighbor n = { line - 1, i - 1 };
        const int max_row = line + 2;
        const int max_column = i + 2;

        while (n.row < max_row) {
            n.column = i - 1;
            while (n.column < max_column) {
                // Check if neighbor is a digit
                if (!isdigit(buffer[n.row][n.column])) {
                    n.column++;
                    continue;
                }

                // Check is there's more digits to the left
                while (n.column > 0 && isdigit(buffer[n.row][n.column - 1])) {
                    n.column--;
                }

                int amount = strtol(&buffer[n.row][n.column], NULL, 10);
                total += amount;
                if (n.row == line && n.column < i) {
                    n.column = i + 1;
                }
                else {
                    n.column += strlen(&buffer[n.row][n.column]);
                }
            }
            n.row++;
        }
    }
    printf(" + %d = ", total);
    return total;
}