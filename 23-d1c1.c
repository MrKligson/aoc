#include <ctype.h>
#include <stdio.h>

// #define FILE_NAME "text/test.txt"
#define FILE_NAME "text/23-d1c1.txt"

int main(int argc, char **argv)
{
    FILE *input = fopen(FILE_NAME ,"r");
    if (input == NULL) {
        printf("Couldn't open file: %s", FILE_NAME);
        return 1;
    }

    int total = 0;
    char c, previous;
    int first, last;
    first = last = -1;

    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            total += first + last;
            first = last = - 1;
        }
        else if (!isdigit(c)) {
            continue;
        }
        else if (first == -1){
            first = last = c - '0';
            first *= 10;
        }
        else {
            last = c - '0';
        }

        previous = c;
    }

    if (previous != '\n') {
        total += first + last;
    }

    fclose(input);
    printf("%d\n", total);
}