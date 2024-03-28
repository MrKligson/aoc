#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "text/test.txt"
#define n_lines 10
#define n_columns 10
// #define FILENAME "text/23-d2c1.txt"
// #define n_lines 140
// #define n_columns 140

int main(int argc, char **argv)
{
    FILE *input = fopen(FILENAME ,"r");
    if (input == NULL) {
        printf("Couldn't open file: %s", FILENAME);
        return 1;
    }
}
