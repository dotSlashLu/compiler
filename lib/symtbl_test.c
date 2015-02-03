#include "symtbl.h"

int main (int argc, char **argv)
{
        symtbl root_scope = st_createScope(NULL);
        st_free(root_scope);
        return 0;
}
