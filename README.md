# CC
Fichier main.c

main : Fonction principale qui lance la boucle REPL pour interagir avec l’utilisateur. Elle appelle repl() pour entrer dans la boucle de commandes, puis libère toute la mémoire allouée à l'arbre en appelant free_tree(root) avant de quitter.

Fichier repl.c

Ce fichier gère les commandes utilisateur et la sauvegarde de données.

Fonctions de Gestion du Buffer d'Entrée

create_input_buffer : Alloue et initialise un buffer pour stocker les commandes de l'utilisateur.

print_prompt : Affiche l'invite de commande db > pour indiquer à l’utilisateur qu’il peut entrer une commande.

read_input : Lit la commande de l’utilisateur depuis le terminal, la stocke dans le buffer d’entrée, et supprime le caractère de nouvelle ligne final.

close_input_buffer : Libère la mémoire allouée pour le buffer d’entrée une fois qu’il n’est plus nécessaire.

Fonctions de Gestion des Commandes

handle_meta_command : Gère les méta-commandes spéciales, comme exit, pour quitter le programme. Si l’utilisateur entre exit, cette fonction sauvegarde l’état actuel de l’arbre, ferme le buffer d’entrée, et termine le programme.

prepare_statement : Analyse la commande de l’utilisateur et détermine si elle correspond à une instruction SQL-like (insert, select, delete). Si oui, elle assigne le type correspondant à la structure Statement.

execute_statement : Exécute l’instruction SQL-like en appelant la fonction appropriée de gestion de l’arbre :

insert : Insère un nouveau nœud avec un identifiant id et un nom name.

select : Affiche tous les nœuds de l'arbre dans l'ordre croissant des identifiants.

delete : Supprime le nœud ayant l'identifiant spécifié.

Fonctions de Sauvegarde et Chargement des Données

load_database : Charge l'arbre depuis le fichier database.txt si le fichier existe, ce qui permet de récupérer les données des sessions précédentes.

save_database : Sauvegarde l'état actuel de l'arbre dans le fichier database.txt, assurant la persistance des données pour les prochaines sessions.

Fonction Principale de la Boucle REPL

repl : Boucle principale qui reçoit les commandes de l'utilisateur, analyse leur type (meta ou statement), et exécute la fonction appropriée. Cette boucle est le cœur de l'interaction utilisateur.

Fichier btree.c

Ce fichier implémente les fonctions principales de manipulation de l'arbre binaire de recherche, utilisées pour stocker et gérer les données.


Fonctions de Base pour l'Arbre

insert : Insère un nœud dans l'arbre avec un identifiant id et un nom name. Cette fonction respecte la structure d'un arbre binaire de recherche en plaçant les valeurs inférieures à gauche et les valeurs supérieures à droite.

delete_node : Supprime un nœud ayant un identifiant id de l'arbre. Elle respecte les règles du BST en tenant compte de trois cas : suppression d'une feuille, d'un nœud avec un seul enfant, ou d'un nœud avec deux enfants.

find_minimum : Renvoie le nœud ayant la plus petite valeur dans un sous-arbre donné. Utilisé pour trouver le successeur lors de la suppression d'un nœud avec deux enfants.

in_order : Parcourt l'arbre en ordre croissant et affiche chaque nœud, ce qui permet de voir les données triées par identifiant.

free_tree : Libère la mémoire allouée pour tous les nœuds de l’arbre, pour éviter les fuites de mémoire à la fin du programme.

Fonctions de Sauvegarde et de Chargement

print_table_header : Affiche l'en-tête de la table pour organiser l'affichage des nœuds.

save_tree : Sauvegarde récursivement l'arbre dans un fichier, en enregistrant chaque nœud avec son id et son name.

load_tree : Charge récursivement l’arbre depuis un fichier. Cette fonction crée un nœud pour chaque entrée et l'ajoute à l'arbre dans l'ordre.

repl.h
Ce fichier contient les définitions et les déclarations pour les structures et fonctions de l'interface utilisateur.

Structures et Énumérations :

MetaCommandResult, PrepareResult, StatementType : Types pour gérer les résultats des commandes et les types d’instructions (méta-commandes ou SQL-like).

Statement : Structure pour représenter une instruction SQL-like, en stockant son type (insert, select, delete).

InputBuffer : Structure pour gérer le buffer d’entrée utilisateur, avec les informations sur sa longueur.

Fonctions du REPL :

repl, create_input_buffer, read_input, close_input_buffer, handle_meta_command, prepare_statement, execute_statement, save_database, load_database.
btree.h

Ce fichier contient la structure de l'arbre binaire ainsi que les fonctions pour manipuler les nœuds de l'arbre.

Structure Node : Définition de la structure d'un nœud de l'arbre, qui contient un identifiant id, un nom name, et des pointeurs vers les nœuds gauche et droit.

Fonctions de Manipulation d'Arbre :

insert, delete_node, find_minimum, in_order, free_tree, print_table_header, save_tree, load_tree.

Cette documentation fournit une vue d'ensemble claire de chaque fonction, de leur rôle, et de leur organisation dans le programme. Elle est conçue pour être accessible et utile pour comprendre le code.
