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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "btree.h"
#include "lexer.h"

#define MAX_ID_LEN 20
static char peek = ' ';
static FILE *in;
static int line = 1;
static nodeptr symtable;

int main(int argc, char **argv)
{
        symtable = malloc(sizeof(node_t));
}

tokp scan()
{
        // reset var peek
        peek = ' ';

        // space
        while ((peek = fgetc(in)) == ' ' || peek == '\t');

        // new line
        while ((peek = fgetc(in)) == '\n') line++;

        // id
        if (isalpha(peek)) {
                char *id = malloc(sizeof(char) * MAX_ID_LEN);
                // test id
                int i = 0;
                while(isalnum(peek)) {
                        peek = fgetc(in);
                        id[i++] = peek;
                }
                tokp tok = malloc(sizeof(tok_t));
                tok->type = tok_id;
                tok->data = id;
                bt_install(symtable, id, tok);
                return tok;
        }

        // num
        if (isdigit(peek)) {
                char *num = malloc(sizeof(char) * MAX_ID_LEN);
                int i = 0;
                while(isdigit(peek)) {
                        peek = fgetc(in);
                        num[i++] = peek;
                }

                long *number = malloc(sizeof(long));
                *number = (long)atol(num);
                tokp tok = malloc(sizeof(tok_t));

                tok->type = tok_num;
                tok->data = number;
                return tok;
        }
}
