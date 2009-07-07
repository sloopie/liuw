-module(mylists).
-compile([export_all]).

map(_, []) ->
    [];
map(F, [H|T]) ->
    [F(H) | map(F, T)].

sum([]) ->
    0;
sum([H|T]) ->
    H + sum(T).
