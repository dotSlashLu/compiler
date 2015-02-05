%%% Infix translator
-module(infix_translator).
-export([t/1]).

t({Filename, file}) ->
  case file:read_file(Filename) of
  {ok, Bin} ->
    expr(binary:bin_to_list(Bin));
  {error, Reason} ->
    io:format("Error open file: ~w~n", [Reason])
  end;

t({String, string}) ->
  expr(String).

expr([Peek | T]) ->
  if
    %% space
    (Peek == 32) or (Peek == 9) or (Peek == 10) ->
      expr(T);
    true -> true
  end,

  %% num
  term(Peek),

  %% rest
  rest(T).

term([Peek|_]) ->
  num(Peek);
term(Peek) ->
  num(Peek).

num(Peek) when Peek >= 48, Peek =< 57 ->
  io:format("~c ", [Peek]).

rest([Peek|T]) ->
  term(T),
  op(Peek),
  [_|Rest] = T,
  rest(Rest);
rest([]) ->
  ok.

op(Peek) when Peek == 43; Peek == 45 ->
  io:format("~c ", [Peek]).
