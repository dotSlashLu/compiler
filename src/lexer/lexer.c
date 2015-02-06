/*
 *      Simple infix to postfix translator.
 *      Translation scheme:
 *              expr    ->      expr + term      {print('+')}
 *                      |       expr - term      {print('-')}
 *                      |       term
 *
 *              term    ->      term * factor    {print('*')}
 *                      |       term / factor    {print('/')}
 *                      |       factor
 *
 *              factor  ->      ( expr )
 *                      |       num              {print(num.value)}
 *                      |       id               {print(id.lexeme)}
 *
 **/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "scanner.h"
#include "btree.h"

static nodeptr symtable;

int main(int argc, char **argv)
{
        FILE *in;
        int line = 1;

        // init symbol table
        symtable = bt_init();
        if (symtable == NULL) {
                printf("Can't create symbol table\n");
                exit(1);
        }

        // open file
        in = fopen(argv[1], "r");
        if (in == NULL) {
                perror("Open file");
                exit(1);
        }

        // scan
        while (1) {
                tokp tok = scan(in);

                if (tok->data != NULL) {
                        switch(tok->type) {
                                case tok_num:
                                        printf("%ld", *(long *)tok->data);
                                        break;
                                case tok_id:
                                        printf("%s", (char *)tok->data);
                                        break;
                        };
                        free(tok->data);
                }
                else {
                        if (tok->type == '\n')
                                printf("\t line %d\n", line++);
                        printf("%c", tok->type);
                }

                // switch(tok->type) {
                //         case '\n':
                //                 line++;
                //                 break;
                // }

                if (tok->type == EOF) {
                        free(tok->data);
                        free(tok);
                        break;
                }

                free(tok);
        }
        bt_free(symtable);
        fclose(in);
        return 0;
}

