#include <stdio.h>
#include <stdlib.h>
#include "repl.h"
#include "btree.h"

int main() {

    repl();
    free_tree(root);
    
    return 0;

}