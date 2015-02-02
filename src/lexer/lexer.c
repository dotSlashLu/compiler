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

#include "btree.h"
#include "lexer.h"

#define MAX_ID_LEN 20
static char peek = ' ';
static FILE *in;
static int line = 1;
static nodeptr symtable = NULL;
tokp scan();

int main(int argc, char **argv)
{
        // init symbol table
        symtable = bt_install(symtable, "", "");
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
                tokp tok = scan();
                printf("got tok: %d\n", tok->type);
                if (tok->type == EOF) break;
                free(tok);
        }
        bt_free(symtable);
}

tokp scan()
{
        // reset var peek
        peek = ' ';
        tokp tok = malloc(sizeof(tok_t));

        // space
        while ((peek = fgetc(in)) == ' ' || peek == '\t') {
                printf("got space\n");
        }

        // new line
        while (peek  == '\n') {
                printf("got new line\n");
                line++;
                peek = fgetc(in);
        }

        // id
        if (isalpha(peek)) {
                puts("got alpha\n");
                char *id = malloc(sizeof(char) * MAX_ID_LEN);
                if (id == NULL) {
                        perror("malloc");
                        exit(1);
                }
                int i = 0;
                while(isalnum(peek)) {
                        peek = fgetc(in);
                        id[i++] = peek;
                }
                tok->type = tok_id;
                tok->data = id;
                puts("installing\n");
                bt_install(symtable, id, tok);
                free(id);
                return tok;
        }

        // num
        if (isdigit(peek)) {
                printf("got num\n");
                char *num = malloc(sizeof(char) * MAX_ID_LEN);
                int i = 0;
                while(isdigit(peek)) {
                        peek = fgetc(in);
                        num[i++] = peek;
                }

                long *number = malloc(sizeof(long));
                if (number == NULL) {
                        perror("malloc");
                        exit(1);
                }
                *number = (long)atol(num);
                free(num);

                tok->type = tok_num;
                tok->data = number;
                return tok;
        }

        char *c = calloc(1, sizeof(char));
        *c = peek;
        tok->type = *c;
        return tok;
}
