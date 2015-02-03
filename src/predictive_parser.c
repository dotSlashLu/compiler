/*
*       A toy predictive parser
*       based on CPTT 2.4
*
*       Specifically for the grammer:
*       ```
*       stmt    -> expr ;
*               |  if ( expr ) stmt
*               |  for ( optexpr ; optexpr ; optexpr ) stmt
*               |  other
*
*       optexpr -> Ɛ
*               |  expr
*       ```
*
*       where `expr` and `other` are just considered as terminals
*       for simplicity
*/

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 50

static char lookahead[MAX_TOKEN_LENGTH];
static FILE *file;

void gettok();
void stmt();
void optexpr();
void match(const char terminal[]);
void syntaxerr();

int main(int argc, char **argv)
{
        if (argc < 2) {
                fprintf(stderr, "Usage: %s filename\n", *argv);
                exit(1);
        }

        file = fopen(*++argv, "r");
        if (file == NULL) {
                perror("fopen: ");
                exit(1);
        }

        gettok();
        // only stmt is implemented for now
        while (1) stmt();

        fclose(file);
        return 0;
}

void stmt()
{
        if (strcmp(lookahead, "expr") == 0) {
                match("expr");
                match(";");
        }

        else if (strcmp(lookahead, "if") == 0) {
                match("if"); match("("); match("expr"); match(")");
                stmt();
        }

        else if (strcmp(lookahead, "for") == 0) {
                match("for"); match("(");
                optexpr(); match(";");
                optexpr(); match(";");
                optexpr(); match(")");
                stmt();
        }

        else if (strcmp(lookahead, "other") == 0) match("other");

        else syntaxerr();
}

void optexpr()
{
        if (strcmp(lookahead, "expr") == 0) match("expr");
}

void match(const char terminal[])
{
        printf("matching tok '%s' against '%s'\n", lookahead, terminal);
        if (strcmp(lookahead, terminal) == 0) return gettok();
        syntaxerr();
}

void gettok()
{
#define unpeek()(fseek(file, -1L, SEEK_CUR))
        lookahead[0] = '\0';
        int i = 0;
        int tok;

        // skip spaces
        while (isspace(tok = getc(file)));

        // EOF
        if (tok == EOF) {
                printf("Token stream ended.\n");
                fclose(file);
                exit(1);
        }

        lookahead[i++] = tok;
        // only allow single punct for now
        if (ispunct(tok)) {
                lookahead[i++] = '\0';
                return;
        }

        // peek
        while ((tok = getc(file))) {
                if (isalpha(tok)) {
                        lookahead[i++] = tok;
                        while (isalpha(tok = getc(file)))
                                lookahead[i++] = tok;
                        unpeek();
                        break;
                }

                else if (ispunct(tok)) {
                        lookahead[i++] = tok;
                        // while (ispunct(tok = getc(file)))
                        //         lookahead[i++] = tok;
                        // unpeek();
                        break;
                }

                else if (isspace(tok)) break;

                else syntaxerr();
        }
        lookahead[i++] = '\0';
}

void syntaxerr()
{
       fprintf(stderr, "Syntax error at: %s\n", lookahead);
       exit(1);
}
