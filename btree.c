#include <string.h>
#include "btree.h"

static unsigned long _hash(unsigned char *str)
nodeptr bt_install(nodeptr root, char *key, void *val);

nodeptr bt_install(nodeptr root, char *key, void *val)
{
        unsigned long hash = _hash(key);
        nodeptr n = root;
        while (n != NULL) {
                // < left, > right
                // collision prevention
                if (n->hash == hash && n->key == key) {
                        n -> val = val;
                        return n;
                }
                if (n->hash <= hash) {
                }

        }
}

static unsigned long _hash(unsigned char *str)
{
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
                /* hash * 33 + c */
                hash = ((hash << 5) + hash) + c;

        return hash;
}
