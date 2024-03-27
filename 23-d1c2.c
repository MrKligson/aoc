#include <ctype.h>
#include <stdio.h>
#include <string.h>

// #define FILE_NAME "text/test.txt"
#define FILE_NAME "text/d1c1.txt"

#define n_numbers 9
#define n_buffer 6

const char *numbers[] = { "one", "two", "three", "four", "five", "six",
                          "seven", "eight", "nine" };

int append_char(char *, char);
int check_numbers(char *);
void shift(char *);

int main(int argc, char **argv)
{
    FILE *input = fopen(FILE_NAME ,"r");
    if (input == NULL) {
        printf("Couldn't open file: %s", FILE_NAME);
        return 1;
    }


    char buffer[n_buffer];
    buffer[0] = '\0';
    int total = 0;
    char c = fgetc(input);
    char previous;
    int first, last;
    first = last = -1;

    while (c != EOF) {
        if (c == '\n') {
            buffer[0] = '\0';

            printf("\n%d + %d%d : ", total, first, last);
            total += first * 10 + last;

            printf("%d\n", total);
            first = last = - 1;
            //test
            
            previous = c;
            c = fgetc(input);
            continue;
        }
        else if (!isdigit(c) && c != '\n') {
            printf("%c", c);
            while (c != EOF && c != '\n' && !isdigit(c)) {
                int appended = append_char(buffer, c);
                if (strlen(buffer) < 3) {
                    printf("%c", c);
                    c = fgetc(input);
 
                    if (isdigit(c)) {
                        break;
                    }
                   continue;
                }

                if (!appended) {
                    shift(buffer);
                    continue;
                }

                if (first < 0) {
                    first = check_numbers(buffer);
                    last = first;
                }
                else {
                    int test = check_numbers(buffer);
                    if (test > 0) {
                        last = test;
                    }

                }

                printf("%c", c);
                previous = c;
                c = fgetc(input);
            }
        }

        if (isdigit(c)) {
            buffer[0] = '\0';

            if (first == -1) {
                first = last = c - '0';
            }
            else {
                last = c - '0';
            }

            printf("%c", c);
            previous = c;
            c = fgetc(input);
        }
    }

    if (previous != '\n') {
        total += first * 10 + last;
    }

    printf("\n%d\n", total);
}

int append_char(char *buffer, char c)
{
    int index = strlen(buffer);
    if (index + 1 == n_buffer) {
        return 0;
    }

    buffer[index] = c;
    buffer[index + 1] = '\0';

    return 1;
}

int check_numbers(char *buffer)
{
    for (int i = 0; i < n_numbers; i++) {
        if (strstr(buffer, numbers[i]) != NULL) {
            return i + 1;
        }
    }
    return -1;
}

void shift(char * buffer)
{
    for (int i = 0; i < n_buffer - 1; i++) {
        buffer[i] = buffer[i + 1];
    }
}
