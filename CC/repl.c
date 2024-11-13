#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"
#include "repl.h"

InputBuffer* create_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    if (input_buffer == NULL) {
        fprintf(stderr, "Erreur d'allocation memoire pour le buffer d'entree\n");
        exit(EXIT_FAILURE);
    }
    input_buffer->buffer = (char*)malloc(1024 * sizeof(char));
    if (input_buffer->buffer == NULL) {
        fprintf(stderr, "Erreur d'allocation memoire pour le buffer\n");
        exit(EXIT_FAILURE);
    }
    input_buffer->buffer_length = 1024;
    input_buffer->input_length = 0;
    return input_buffer;
}

void print_prompt() {
    printf("db > ");
}

void read_input(InputBuffer* input_buffer) {
    if (fgets(input_buffer->buffer, input_buffer->buffer_length, stdin) == NULL) {
        printf("Erreur lors de la lecture de l'entree\n");
        exit(EXIT_FAILURE);
    }
    input_buffer->input_length = strlen(input_buffer->buffer);

    if (input_buffer->buffer[input_buffer->input_length - 1] == '\n') {
        input_buffer->buffer[input_buffer->input_length - 1] = '\0';
        input_buffer->input_length--;
    }
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

MetaCommandResult handle_meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, "exit") == 0) {
        save_database();
        close_input_buffer(input_buffer);
        printf("Base de donnees sauvegardee. Sortie...\n");
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    if (strncmp(input_buffer->buffer, "delete", 6) == 0) {
        statement->type = STATEMENT_DELETE;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement, InputBuffer* input_buffer) {
    switch (statement->type) {
        case STATEMENT_INSERT: {
            int id;
            char name[256];
            if (sscanf(input_buffer->buffer, "insert %d %255s", &id, name) != 2) {
                printf("Erreur de syntaxe. Utilisation : insert <id> <nom>\n");
                return;
            }

            insert(&root, id, name);
            printf("Insertion resussie (ID: %d, Nom: %s)\n", id, name);
            break;
        }
        case STATEMENT_SELECT:
            printf("Contenu de la table :\n");
            print_table_header();
            in_order(root);
            printf("+----------------+----------------+\n");
            break;
        case STATEMENT_DELETE: {
            int id;
            if (sscanf(input_buffer->buffer, "delete %d", &id) != 1) {
                printf("Erreur de syntaxe. Utilisation : delete <id>\n");
                return;
            }
            root = delete_node(root, id);
            printf("Suppression reussie de l'ID : %d\n", id);
            break;
        }
    }
}

void load_database() {
    FILE* file = fopen("database.txt", "r");
    if (file != NULL) {
        root = load_tree(file);
        fclose(file);
    } else {
        root = NULL;
    }
}

void save_database() {
    FILE* file = fopen("database.txt", "w");
    if (file != NULL) {
        save_tree(root, file);
        fclose(file);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier pour la sauvegarde.\n");
    }
}

void repl() {
    load_database();
    InputBuffer* input_buffer = create_input_buffer();

    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, "exit") == 0) {
            handle_meta_command(input_buffer);
            continue;
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case PREPARE_SUCCESS:
                printf("Requete reconnue\n");
                execute_statement(&statement, input_buffer);
                printf("Execute.\n");
                break;

            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Mot-cle non reconnu au debut de '%s'.\n", input_buffer->buffer);
                continue;
        }
    }
}
