#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cube_set {
    int red;
    int green;
    int blue;
} Cube_set;

// #define FILENAME "text/test.txt"
// #define n_games 5
#define FILENAME "text/23-d2c1.txt"
#define n_games 100

Cube_set games[n_games];

void add_game(char *);

int main(int argc, char **argv)
{
    FILE *input = fopen(FILENAME ,"r");
    if (input == NULL) {
        printf("Couldn't open file: %s", FILENAME);
        return 1;
    }

    const int n_line = 200;
    char line[n_line];
    while (fgets(line, n_line, input) != NULL) {
        if (strncmp(line, "Game", 4) != 0) {
            continue;
        }
        add_game(line);
    }

    int total = 0;
    for (int i = 0; i < n_games; i ++) {
        total += games[i].red * games[i].green * games[i].blue;;
    }

    fclose(input);
    printf("%d\n", total);
}

void add_game(char *game)
{
    Cube_set cube = {0, 0, 0};
    //discard "Game"
    char *token = strtok(game, " ");
    token = strtok(NULL, ": ");
    if (token == NULL) {
        return;
    }

    //get game #
    int index = atoi(token) - 1;

    // iterate over every {amount, color} pair
    int color = 0;
    int amount = 0;
    while ((token = strtok(NULL, ";, "))  != NULL) {
        if (!color) {
            amount = atoi(token);
            color++;
            continue;
        }

        switch (token[0]) {
            case 'r':
                cube.red = amount > cube.red ? amount : cube.red;
                break;
            case 'g':
                cube.green = amount > cube.green ? amount : cube.green;
                break;
            case 'b':
                cube.blue = amount > cube.blue ? amount : cube.blue;
                break;
            default:
                return;
        }

        amount = color = 0;
    }

    games[index] = cube;
}
