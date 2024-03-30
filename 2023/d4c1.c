#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define FILE_NAME "text/test.txt"
// #define lines 6
#define FILE_NAME "text/d4.txt"
#define lines 189

typedef struct node {
    int key;
    struct node *left, *right;
} Node;

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
    return node;
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

int main(int argc, char **argv)
{
    FILE *input = fopen(FILE_NAME ,"r");
    if (input == NULL) {
        printf("Couldn't open file: %s", FILE_NAME);
        return 1;
    }

    Node *tree = NULL;
    char *token;
    int value, total = 0;
    bool found, reading = true;

    const int n_lines = 120;
    char line[n_lines];
    for (int i = 0; i < lines; i++) {
        fgets(line, n_lines, input);
        strtok(line, ":");
        value = 0;

        while ((token = strtok(NULL, " ")) != NULL) {
            if (token[0] == '|') {
                reading = false;
                continue;
            }

            if (reading) {
                tree = insert(tree, atoi(token));
            }
            else {
                found = search(tree, atoi(token));
                if (!found) {
                    continue;
                }

                if (value == 0) {
                    value++;
                }
                else {
                    value *= 2;
                }
            }
        }

        total += value;
        tree = burn(tree);
        reading = true;
    }

    printf("Total: %d\n", total);
    fclose(input);
}