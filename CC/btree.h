#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>

typedef struct Node {
    int id;
    char name[256];
    struct Node* left;
    struct Node* right;
} Node;

extern Node* root;

void insert(Node** root, int id, const char* name);
Node* delete_node(Node* root, int id);
void in_order(Node* root);
void free_tree(Node* root);
void print_table_header();
void save_tree(Node* root, FILE* file);
Node* load_tree(FILE* file);

#endif