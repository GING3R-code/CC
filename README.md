Fichier btree.c
C’est ici que j’ai mis tout ce qui concerne l’arbre binaire. Chaque fonction a été pensée pour que l’arbre reste trié et efficace.

1. Fonction insert
J’ai utilisé la récursivité parce que ça colle parfaitement avec la structure hiérarchique d’un arbre binaire. À chaque étape, on décide si on va à gauche ou à droite selon la valeur.
J’ai aussi choisi un double pointeur (Node**) pour que, même si l’arbre est vide, on puisse facilement mettre à jour sa racine sans avoir à gérer ce cas à part dans repl.c.

2. Fonction delete_node
Pour supprimer un nœud, il y a trois cas à gérer :

Le nœud est une feuille.
Le nœud a un seul enfant.
Le nœud a deux enfants.
J’ai tout écrit dans une seule fonction pour que ça reste compact et facile à comprendre. Quand il y a deux enfants, je trouve le successeur avec find_minimum, ce qui évite de casser la structure de l’arbre. Pourquoi ? Parce que c’est une méthode classique et éprouvée pour garder un BST valide.

3. Fonction find_minimum
Pour trouver le minimum, on suit simplement le chemin le plus à gauche de l’arbre. J’ai préféré une approche itérative au lieu de récursive pour éviter d’empiler des appels inutiles. C’est rapide, clair et efficace.

4. Fonction in_order
J’ai utilisé un parcours in-order parce que c’est le moyen naturel de parcourir un arbre binaire dans l’ordre trié. Pourquoi récursif ? Parce que ça rend la logique très lisible : gauche → nœud courant → droite. C’est exactement ce qu’on veut pour afficher les données dans le bon ordre.

5. Fonction free_tree
Cette fonction est essentielle pour éviter les fuites mémoire. J’ai utilisé une méthode récursive parce qu’il faut libérer chaque nœud individuellement, en commençant par les feuilles. Ça garantit que tout est bien nettoyé.

6. Fonction save_tree
Pour sauvegarder l’arbre, j’ai utilisé une écriture récursive : chaque nœud est écrit dans un fichier, suivi de ses sous-arbres gauche et droit. Pourquoi ? Parce que ça reflète exactement la structure de l’arbre. C’est simple et ça garantit que les données sont faciles à recharger.

7. Fonction load_tree
Quand on recharge les données, on lit les nœuds un par un dans le même ordre qu’on les a sauvegardés. J’ai préféré cette approche parce qu’elle permet de reconstruire l’arbre exactement comme il était, sans avoir à recalculer quoi que ce soit.

8. Fonction print_table_header
J’ai ajouté cette fonction pour afficher un en-tête propre avant de montrer les données. Pourquoi ? Parce que c’est plus clair pour l’utilisateur et ça donne un aspect bien organisé.
