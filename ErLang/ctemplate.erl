-module(ctemplate).
-compile(export_all).

start() ->
    spawn(fun() ->
		  loop([]) end).

rpc(Pid, Requset) ->
    Pid ! {self(), Requset},
    receive
	{Pid, Response} ->
	    Response
    end.

loop(X) ->
    receive
	Any ->
	    io:format("Received msg: ~p~n", [Any]),
	    loop(X)
    end.
