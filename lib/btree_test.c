#include "btree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
        nodeptr root = NULL;
        root = bt_install(root, "key1ase", "val1");
        bt_install(root, "abc2", "def2");
        bt_install(root, "abc3", "def3");
        bt_install(root, "abc5", "def5");
        bt_install(root, "awoepfh asdoi asdofih sdpofih aopweihfaowiehfa", "no content");

        nodeptr res;
        res = bt_find(root, "abc2");
        printf("Found result: %p\n", res);
        printf("{%s(%ld) => %s }\n", res->key,
                res->hash, (char *)res->val);
        bt_find(root, "key1");
        bt_find(root, "abc5");
        bt_find(root, "");


        bt_free(root);
        return 0;
}
