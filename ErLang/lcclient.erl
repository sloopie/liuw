-module(lcclient).
-compile(export_all).

start(Nick) ->
    spawn(fun() ->
		  loop(Nick) end).

loop(Nick) ->
    receive
	{join} ->
	    lcserver ! {join, {self(), Nick}},
	    loop(Nick);
	{quit} ->
	    lcserver ! {quit, {self(), Nick}},
	    loop(Nick);
	{send, {Msg}} ->
	    lcserver ! {send, {Nick, Msg}},
	    loop(Nick);
	{joined, {N}} ->
	    io:format("~p joined the chat~n", [N]),
	    loop(Nick);
	{quited, {N}} ->
	    io:format("~p quited the chat~n", [N]),
	    loop(Nick);
	{msg, {N, M}} ->
	    io:format("~p say: ~p~n", [N, M]),
	    loop(Nick);
	{serverquit} ->
	    io:format("server halted~n", []),
	    exit(serverHalted)
    end.
