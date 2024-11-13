CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude/

# -fsanitize=address

# Fichiers source
SRC = main.c repl.c btree.c

# Fichiers objets
OBJ = main.o repl.o btree.o

# Définir le nom de la cible en fonction du système d'exploitation
ifeq ($(OS),Windows_NT)
    TARGET_MAIN = dbwin.exe
else
    TARGET_MAIN = dbunix
endif

# Commande de suppression selon le système d'exploitation
ifeq ($(OS),Windows_NT)
    DEL = del
else
    DEL = rm -f
endif

all: $(TARGET_MAIN)

# Compilation de l'exécutable
$(TARGET_MAIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# Compilation des fichiers objets
main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

repl.o: repl.c
	$(CC) $(CFLAGS) -c $< -o $@

btree.o: btree.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(DEL) $(TARGET_MAIN) *.o
