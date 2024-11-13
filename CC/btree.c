#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

Node* root = NULL;

Node* find_minimum(Node* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

void insert(Node** root, int id, const char* name) {
    if (*root == NULL) {

        Node* new_node = (Node*)malloc(sizeof(Node));
        if (new_node == NULL) {
            fprintf(stderr, "Erreur : Échec de l'allocation mémoire.\n");
            exit(EXIT_FAILURE);
        }
        new_node->id = id;
        strncpy(new_node->name, name, sizeof(new_node->name) - 1);
        new_node->name[sizeof(new_node->name) - 1] = '\0';
        new_node->left = NULL;
        new_node->right = NULL;
        *root = new_node;
        return;
    }

    if (id == (*root)->id) {
        printf("Erreur : L'ID %d existe deja.\n", id);
    } else if (id < (*root)->id) {
        insert(&(*root)->left, id, name);
    } else {
        insert(&(*root)->right, id, name);
    }
}

void print_table_header() {
    printf("+----------------+----------------+\n");
    printf("| ID             | Nom            |\n");
    printf("+----------------+----------------+\n");
}

void in_order(Node* root) {
    if (root != NULL) {
        in_order(root->left);
        printf("| %-14d | %-14s |\n", root->id, root->name);
        in_order(root->right);
    }
}

void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

void save_tree(Node* root, FILE* file) {
    if (root == NULL) {
        return;
    }
    fprintf(file, "%d %s\n", root->id, root->name);
    save_tree(root->left, file);
    save_tree(root->right, file);
}

Node* load_tree(FILE* file) {
    int id;
    char name[256];

    if (fscanf(file, "%d %255s", &id, name) != 2) {
        return NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }
    new_node->id = id;
    strncpy(new_node->name, name, sizeof(new_node->name) - 1);
    new_node->name[sizeof(new_node->name) - 1] = '\0';

    new_node->left = load_tree(file);
    new_node->right = load_tree(file);

    return new_node;
}
Node* delete_node(Node* root, int id) {
    if (root == NULL) {
        printf("Erreur : ID %d non trouvé.\n", id);
        return root;
    }

    if (id < root->id) {
        root->left = delete_node(root->left, id);
    } else if (id > root->id) {
        root->right = delete_node(root->right, id);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = find_minimum(root->right);
        root->id = temp->id;
        strncpy(root->name, temp->name, sizeof(root->name) - 1);
        root->name[sizeof(root->name) - 1] = '\0';
        root->right = delete_node(root->right, temp->id);
    }
    return root;
}