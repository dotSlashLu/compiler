-module(infix_translator).
-export([translate/1]).

translate(Filename) ->
  case file:read_file(Filename) of
  {ok, Bin} ->
    expr(binary:bin_to_list(Bin));
  {error, Reason} ->
    io:format("Error open file: ~w~n", Reason)
  end.

expr([Peek | T]) ->
  if
    %% space
    (Peek == 32) or (Peek == 9) or (Peek == 10) ->
      expr(T);

    %% num
    (Peek >= 48) and (Peek =< 57) ->
      term(Peek),
      expr(T);

    %% +-
    (Peek == 43) or (Peek == 45) ->
      expr(T),
      io:format("~c ", [Peek]);

    true -> true

  end;


expr([]) ->
  true.

term(Peek) ->
  % if
  %   %% space
  %   (Peek == 32) or (Peek == 9) or (Peek == 10) ->
  %     term(T);

  %   true -> true
  % end,
  io:format("~c ", [Peek]).

scan([Peek | T]) ->
  if
    %% space
    (Peek == 32) or (Peek == 9) or (Peek == 10) ->
      scan(T);
    %% num
    (Peek >= 48) and (Peek =< 57) ->
      io:format("~c", [Peek]),
      scan(T);
    %% + -
    (Peek == 43) or (Peek == 45) ->
      io:format("an op!~n"),
      scan(T),
      io:format("~c", [Peek]);
    %% eof
    T == [] ->
      io:format("EOF~n");
    true -> true
  end;

scan([]) ->
  io:format("EOF~n").

%% term, number
% scan([Peek | T]) when Peek >= 48, Peek =< 57 ->
%   io:format("~s", [Peek]),
%   scan(T);
%
% %% sign
% scan([Peek | T]) when Peek = 43; Peek = 45 ->
%   scan(T),
%   io:format("~s", [Peek]);
%
% scan([_ | T]) when T = [] ->
%   io:format("EOF~n").
%
%
