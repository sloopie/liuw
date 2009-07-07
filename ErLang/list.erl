-module(list).
-compile(export_all).

create(Name) ->
    register(Name, spawn(fun() ->
				 loop([]) end)).

loop(L) ->
    receive
	{store, Value} ->
	    loop([Value | L]);
	{remove, Value} ->
	    L1 = remove1(Value, L),
	    loop(L1);
	{print} ->
	    print1(L),
	    loop(L)
    end.

remove1(Value, [Value | T]) ->
    T;
remove1(Value, [H | T]) ->
    [H | remove1(Value, T)];
remove1(_, []) ->
    [].


print1([]) ->
    ok;
print1([H | T]) ->
    io:format("~p ", [H]),
    print1(T).
%print1([]) ->
%    ok.
