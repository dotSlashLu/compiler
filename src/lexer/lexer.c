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
                if (tok->data != NULL) {
                        switch(tok->type) {
                        case tok_num:
                                printf("num data: %ld\n", *(long *)tok->data);
                                break;
                        case tok_id:
                                printf("id data: %s\n", (char *)tok->data);
                                break;
                        };
                        free(tok->data);
                }
                if (tok->type == EOF) {
                        free(tok);
                        break;
                }
                free(tok);
        }
        bt_free(symtable);
        fclose(in);
        return 0;
}

tokp scan()
{
        fputc('\n', stdout);
        // reset var peek
        peek = ' ';
        tokp tok = calloc(1, sizeof(tok_t));

        // space
        while ((peek = fgetc(in)) == ' ' || peek == '\t') { }

        // new line
        while (peek  == '\n') {
                line++;
                peek = fgetc(in);
        }

        // id
        if (isalpha(peek)) {
                char *id = malloc(sizeof(char) * MAX_ID_LEN);
                if (id == NULL) {
                        perror("malloc");
                        exit(1);
                }
                char *tmp = id;

                while(isalnum(peek)) {
                        *tmp++ = peek;
                        peek = fgetc(in);
                }
                *tmp++ = '\0';
                tok->type = tok_id;
                tok->data = id;
                // printf("got id: %s\n", id);
                bt_install(symtable, id, tok);
                return tok;
        }

        // num
        if (isdigit(peek)) {
                char *num = malloc(sizeof(char) * MAX_ID_LEN);
                if (num == NULL) {
                        perror("malloc");
                        exit(1);
                }
                char *tmp = num;
                while(isdigit(peek)) {
                        *tmp++ = peek;
                        peek = fgetc(in);
                }
                *tmp++ = '\0';

                long *number = malloc(sizeof(long));
                if (number == NULL) {
                        perror("malloc");
                        exit(1);
                }
                *number = (long)atol(num);
                free(num);
                // printf("got num: %ld\n", *number);

                tok->type = tok_num;
                tok->data = number;
                return tok;
        }

        tok->type = peek;
        return tok;
}
