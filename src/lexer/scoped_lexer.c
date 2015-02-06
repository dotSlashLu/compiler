/*
*      Lexer with scope.
*      Translation scheme:
*
*      program ->              {top = null}
*              block
*
*      block   -> '{'          {saved = top;
*                              top = new Env(top);
*                              print("{");}
*              decls stmts
*                              {top = saved;
*              '}'             print("}");}
*
*      decls   -> decls decl
*              |  ϵ
*
*      decl    -> type id ;    {s = new Symbol;
*                              s.type = type.lexeme;
*                              top.put(id.lexeme, s);}
*
*      stmts   -> stmts stmt
*              |  ϵ
*
*      stmt    -> block
*              |  factor ;     {print(";");}
*
*      factor  -> id           {s = top.get(id.lexeme);
*                              print(id.lexeme);
*                              print(":");}
*                              print(s.type);
*
*      e.g.
*      source: {int x; char y; { bool y; x; y; } x; y;}
*      dest:   {{ x: int; y: bool; } x: int; y: char;}
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symtbl.h"
#include "scanner.h"


static FILE *in;
static int line = 1;
static symtbl env = NULL;
static tokp tok;

void block();
void decls();
void decl();


static void syntaxerror(char *err);

int main(int argc, char **argv)
{
        in = fopen(argv[1], "r");
        if (in == NULL) {
                perror("fopen");
                return -1;
        }

        // program -> block
        block();
        return 0;
}

/*
*      block   -> '{'
*              decls stmts
*              '}'
*/
void block()
{
        tok = scan(in);

        if (tok->type != '{') {
                char *err;
                asprintf(&err, "Syntax Error: program \
should start with '{', got %c in line %d\n", tok->type, line);
                syntaxerror(err);
        }

        symtbl env = st_createScope(NULL);
        fputc('{', stdout);
}

/**
*      decls   -> decls decl
*              |  ϵ
*/
void decls()
{

}

/**
*       decl    -> type id ;
*/
void decl()
{
        tok = scan(in);
        if (tok->type != tok_id) {
                char *err;
                asprintf(&err, "Syntax Error: declaration \
should start with a type, got %s in line %d\n", line, tok->type);
                syntaxerror(err);
        }
        char *type = (char *)tok->data;
        tok = scan(in);
}

static void syntaxerror(char *err)
{
        fprintf(stderr, err);
        free(err);
        if (env) st_free_deep(env);
        tok_free(tok);
        exit(1);
}
