-module(exhausted).
-compile(export_all).

loop() ->
    sleep(100),
    loop(),
    someFun().

someFun() ->
    void.

sleep(T) ->
    receive
	after T ->
		true
	end.
