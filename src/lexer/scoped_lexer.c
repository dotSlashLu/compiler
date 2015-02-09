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
#include <unistd.h>

#include "symtbl.h"
#include "scanner.h"


static FILE *in;
static int line = 1;
static symtbl env = NULL;
static tokp tok;

void block();
void decls();
void decl();
void stmts();
void stmt();

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

        fputc('\n', stdout);
        st_free_deep(env);
        fclose(in);
        return 0;
}

/*
*      block   -> '{'
*              decls stmts
*              '}'
*/
void block()
{
        if (tok == NULL)
                tok = scan(in);

        if (tok->type != '{') {
                char *err;
                asprintf(&err,
                        "Syntax Error: block \
should start with '{', got %c in line %d\n",
                        tok->type, line);
                syntaxerror(err);
        }

        tok_free(tok);
        tok = NULL;

        env = st_createScope(env);
        if (env == NULL) {
                char *err = "Can't create symbol table.";
                syntaxerror(err);
        }
        fputs("{", stdout);

        tok = scan(in);
        decls();
        stmts();

        if (tok == NULL)
                tok = scan(in);
        if (tok->type != '}') {
                char *err;
                asprintf(&err,
                        "Syntax Error: block \
should end with '}', got %c in line %d\n",
                        tok->type, line);
                syntaxerror(err);
        }
        tok_free(tok);
        tok = NULL;

        if (env->parent)
                env = env->parent;
        fputs("} ", stdout);
}

/**
*      decls   -> decls decl
*              |  ϵ
*/
void decls()
{
        decl();
        tok = scan(in);
        // tok is type
        if (tok->type <= 263 && tok->type >= 260)
                decls();
}

/**
*       decl    -> type id ;
*/
void decl()
{
        if (tok == NULL)
                tok = scan(in);
        char *type = malloc(MAX_ID_LEN);
        strcpy(type, tok->data);
        tok_free(tok);

        tok = scan(in);
        if (tok->type != tok_id) {
                char *err;
                asprintf(&err,
                        "Syntax Error: declaration \
should end with an id, got %c in line %d\n",
                        tok->type, line);
                syntaxerror(err);
        }
        char *id = malloc(MAX_ID_LEN);
        strcpy(id, tok->data);
        st_put(env, id, type);
        tok_free(tok);

        tok = scan(in);
        if (tok->type != ';') {
                char *err;
                asprintf(&err,
                        "Syntax Error: decl \
should end with ';', got %c in line %d\n",
                        tok->type, line);
                syntaxerror(err);
        }
        tok_free(tok);
        tok = NULL;
}

void stmts()
{
        stmt();
        if (tok == NULL)
                tok = scan(in);
        if (tok->type == '{' || tok->type == tok_id)
                stmt();
}

/*
*      stmt    -> block
*              |  factor ;
*
*      factor  -> id
*/
void stmt()
{
        if (tok == NULL)
                tok = scan(in);

        // factor
        if (tok->type == tok_id) {
                nodeptr node = st_search(env, (char *)tok->data);
                if (node == NULL) {
                        char *err;
                        asprintf(&err,
                                "\nError: Variable %s undefined \
in line %d\n", tok->data, line);
                        syntaxerror(err);
                }
                printf("%s: %s", tok->data, node->val);
                free(node->key);
                free(node->val);
                tok_free(tok);

                tok = scan(in);
                if (tok->type != ';') {
                        char *err;
                        asprintf(&err,
                                "Syntax Error: factor \
should end with ';' in line %d\n", line);
                        syntaxerror(err);
                }
                fputs("; ", stdout);
                tok_free(tok);
                tok = NULL;
        }

        // block
        else block();
}

static void syntaxerror(char *err)
{
        fprintf(stdout, err);
        free(err);
        if (env) st_free_deep(env);
        tok_free(tok);
        fclose(in);
        exit(1);
}
