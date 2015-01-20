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

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_TOKEN_SIZE 20

enum tokens {
        tok_expr,
        tok_if,
        tok_for,
        tok_other = 0
};
static char lookahead[MAX_TOKEN_SIZE];
static int  lookaheadTokType;
static FILE *file;

int main(int argc, char **argv)
{
        if (argc < 2) {
                fprintf(stderr, "Usage: %s filename\n", *argv);
                exit(1);
        }
        file = fopen(*++argv);
        return 0;
}

void stmt()
{
        switch (lookaheadTokType) {
        case tok_expr:
                match("expr"); match(';');
                break;
        case tok_if:
                match(tok_if);
                match('('); match(tok_expr);
                match(')'); stmt();
                break;
        }
}

void match(unsigned char terminal)
{
        if ()
}

void gettok()
{
        while(isspace)
                getc(file);
}

