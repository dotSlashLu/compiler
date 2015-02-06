#include "symtbl.h"
#include <stdio.h>

int main (int argc, char **argv)
{
        symtbl root_scope = st_createScope(NULL);
        symtbl scope2 = st_createScope(root_scope);
        symtbl scope3 = st_createScope(root_scope);

        // test for max child scope
        // int i = 0;
        // while (i++ < 1025) {
        //         if (st_createScope(root_scope) == NULL) {
        //                 fprintf(stderr, "Maximum child scope limit exceeded\n");
        //                 st_free(root_scope);
        //                 return 1;
        //         }
        // }

        st_put(scope2, "test2", "2333");
        st_put(root_scope, "test", "123");
        st_put(scope3, "test3", "ttt");

        printf("searching for test from s2\n");
        nodeptr res = st_search(scope2, "test");
        if (res != NULL) printf("result: %s\n", (char *)res->val);

        printf("searching for test2 from s2\n");
        nodeptr res2 = st_search(scope2, "test2");
        if (res2 != NULL) printf("result: %s\n", (char *)res2->val);

        printf("searching for test2 from s3\n");
        nodeptr res3 = st_search(scope3, "test2");
        if (res3 != NULL) printf("result: %s\n", (char *)res3->val);

        printf("searching for test3 from s3\n");
        nodeptr res4 = st_search(scope3, "test3");
        if (res4 != NULL) printf("result: %s\n", (char *)res4->val);

        st_free(root_scope);
        return 0;
}
