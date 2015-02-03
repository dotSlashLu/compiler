#include <stdlib.h>
#include <string.h>

#include "btree.h"
#include "symtbl.h"

void _st_free_node(symtbl root);

symtbl st_createScope(symtbl parent)
{
        nodeptr scope = bt_init();
        symtbl env = calloc(1, sizeof(symtbl_t));
        env->scope = scope;
        env->parent = parent;
        env->nchild = 0;
        if (parent != NULL) {
                *(parent->children + parent->nchild) = env;
                parent->nchild += 1;
        }
        return env;
}

symtbl st_put(symtbl to, char *key, void *data)
{
        nodeptr scope = to->scope;
        bt_install(scope, key, data);
        return to;
}

nodeptr st_search(symtbl from, char *key)
{
        nodeptr scope;
        nodeptr result;
        while ((scope = from->scope) != NULL) {
                result = bt_find(scope, key);
                if (result != NULL) return result;
                // search upper scope
                from = from->parent;
                if (from == NULL) return NULL;
        }
        return NULL;
}

void st_free(symtbl root)
{
        int n = 0;
        if (root->scope != NULL)
                bt_free(root->scope);
        while (n < root->nchild)
                st_free(*(root->children + n++));
        free(root);
}
