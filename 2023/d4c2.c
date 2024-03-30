#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

typedef struct Card {
    int amount;
    int score;
} Card;

Node * new_node(int value);
Node * insert(Node *node, int value);
Node * burn(Node *node);
bool search(Node *node, int value);

static inline int min(int x, int y) { return  x < y ? x : y;}

// #define FILE_NAME "text/test.txt"
// #define n_cards 6
#define FILE_NAME "text/d4.txt"
#define n_cards 189
#define n_chars 120

int main(int argc, char **argv)
{
    FILE *input = fopen(FILE_NAME ,"r");
    if (input == NULL) {
        printf("Couldn't open file: %s", FILE_NAME);
        return 1;
    }

    Node *tree = NULL;
    char *token;
    int total = 0;
    int card = 0;
    Card cards[n_cards];
    for (int i = 0; i < n_cards; i++) {
        cards[i] = (Card) { .amount = 1, .score = 0 };
    }

    char line[n_chars];
    for (int i = 0; i < n_cards; i++) {
        fgets(line, n_chars, input);
        strtok(line, ":");
        bool reading = true;

        while ((token = strtok(NULL, " ")) != NULL) {
            if (token[0] == '|') {
                reading = false;
                continue;
            }

            if (reading) {
                tree = insert(tree, atoi(token));
            }
            else if (search(tree, atoi(token))) {
                cards[card].score++;
            }
        }

        int max = min(card + cards[card].score, n_cards - 1);
        for (int c = card + 1; c <= max; c++) {
            cards[c].amount += cards[card].amount;
        }

        total += cards[card].amount;
        tree = burn(tree);
        card++;
    }

    printf("Total: %d\n", total);
    fclose(input);
}

Node * new_node(int value)
{
    Node *temp = (Node *) malloc(sizeof(Node));
    temp->key = value;
    temp->left = temp->right = NULL;
    return temp;
}

Node * insert(Node *node, int value)
{
    if (node == NULL) {
        return new_node(value);
    }

    if (value < node->key) {
        node-> left = insert(node->left, value);
    }
    else if (value > node->key) {
        node-> right = insert(node->right, value);
    }

    return node;
}

Node * burn(Node *node)
{
    if (node != NULL) {
        burn(node->left);
        burn(node->right);

        free(node);
        node = NULL;
    }
    return NULL;
}

bool search(Node *node, int value)
{
    if (node == NULL) {
        return false;
    }

    if (value < node->key) {
        return search(node->left, value);
    }
    else if (value > node->key) {
        return search(node->right, value);
    }

    return true;
}
