#!/usr/bin/env escript
%% A simple lexer
%%
%% expr    ->      term + expr      {print('+')}
%%         |       term - expr      {print('-')}
%%         |       term
%%
%% term    ->      factor * term    {print('*')}
%%         |       factor / term    {print('/')}
%%         |       factor
%%
%% factor  ->      ( expr )
%%         |       num              {print(num.value)}
%%         |       id               {print(id.lexeme)}

-module(lexer).

main([File]) ->
  case file:read_file(File) of

  {ok, Stream} ->
    expr(binary:bin_to_list(Stream));

  {error, Reason} ->
    io:format("Error open file: ~w~n", [Reason])

  end.

expr([H|T]) ->
  term(H, T).

%% ( expr )
term(H, T) when H == '('
  expr(T);
%% num
term(H, T) when H =< '9' and H >= '0'
  num(H, T);


num(H, T) ->
  io:format("~c", [H]),
  [H1|T1] = T,
  if H1 =< '9' and H1 >= '0'
    num(H1, T1).
