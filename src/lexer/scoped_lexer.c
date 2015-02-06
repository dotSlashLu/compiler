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
 *              decls stmts     {top = saved;
 *                              print("}");}
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

#include "symtbl.h"

int main(int argc, char **argv)
{

}
