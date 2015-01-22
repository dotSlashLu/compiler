/*
 *      Simple infix form to postfix form translator.
 *      Only available for plus and minus.
 *
 *      Translation scheme:
 *              term -> 0       {print 0}
 *                   | 1        {print 1}
 *                   | 2        {print 2}
 *                   | 3        {print 3}
 *                   ...
 *                   | 9        {print 9}
 *
 *              rest -> + term     {print +}
 *                   |  - term     {print -}
 *                   |  Ɛ
 **/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static char *s;

void syntaxerr(const char[]);
void term();
void expr();

int main(int argc, char **argv)
{
        if (argc < 2) {
                printf("Usage: %s [infix equation]\n", argv[0]);
                return 1;
        }

        s = argv[1];
        printf("Translating %s\n", s);

        while (isspace(*s)) s++;
        expr();
        fputc('\n', stdout);
        return 0;
}

void term()
{
        while (isspace(*s)) s++;
        if (!isdigit(*s)) return syntaxerr("number expected");
        while(isdigit(*s)) fputc(*s++, stdout);
        fputc(' ', stdout);
}

void expr()
{
        char sign;
        term();
        while (*s != '\0') {
                while (isspace(*s)) s++;
                if (*s == '+' || *s == '-') {
                        sign = *s;
                        s++;
                        term();
                }
                else ;
                printf("%c ", sign);
        }
}

void syntaxerr(const char err[])
{
        printf("Syntax error: %s at %c\n", err, *s);
        exit(1);
}
