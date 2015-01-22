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
void rest();
void expr();

int main(int argc, char **argv)
{
        if (argc < 2) {
                printf("Usage: %s [post fix equation]\n", argv[0]);
                return 1;
        }

        s = argv[1];
        printf("Translating %s\n", s);

        while (isspace(*s)) s++;
        while (*s != '\0') expr();
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

void rest()
{
        char sign;
        while (isspace(*s)) s++;
        if (*s == '+') {
                sign = '+';
                s++;
                if (*s != '\0') term();
        }
        else if (*s == '-') {
                sign = '-';
                s++;
                if (*s != '\0') term();
        }
        else ;
        fputc(sign, stdout);
}

void expr()
{
        term();
        rest();
}

void syntaxerr(const char err[])
{
        printf("Syntax error: %s at %c\n", err, *s);
        exit(1);
}
