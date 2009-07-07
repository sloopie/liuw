-module(lcserver).
-compile(export_all).

start() ->
    register(lcserver, spawn(fun() ->
				     loop([]) end)).
loop(L) ->
    receive
	{join, {Pid, Nick}} ->
	    L1 = [{Pid, Nick} | L],
	    foreach(fun({P, _N}) ->
			    P ! {joined, {Nick}} end, L1),
	    loop(L1);
	{quit, {Pid, Nick}} ->
	    L1 = remove(Pid, L),
	    foreach(fun({P, _N}) ->
			    P ! {quited, {Nick}} end, L1),
	    loop(L1);
	
	{send, {Nick, Msg}} ->
	    foreach(fun({P, _N}) ->
			    P ! {msg, {Nick, Msg}} end, L),
	    loop(L);
	{halt} ->
	    foreach(fun({P, _N}) ->
			    P ! {serverquit} end, L),
	    exit(halt)
    end.

stop() ->
    case whereis(lcserver) of
	undefined ->
	    io:format("lcserver did not start~n", []),
	    void;
	Pid ->
	    lcserver ! {halt},
	    io:format("lcserver: ~p stopped~n", [Pid])
    end.


remove(_, []) ->
    [];
remove(Pid, [{Pid, _N} | T]) ->
    T;
remove(Pid, [H | T]) ->
    [H | remove(Pid, T)].

foreach(_, []) ->
    [];
foreach(F, [H | T]) ->
    [F(H) | foreach(F, T)].
