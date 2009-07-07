-module(lib_misc).
-compile([export_all]).

qsort([]) ->
    [];
qsort([Pivot|T]) ->
    qsort([X || X <- T,
		X < Pivot])
	++Pivot++
	qsort([X || X <- T,
		    X >= Pivot]).

pythag(N) ->
    [{A,B,C} ||
	A <- lists:seq(1,N),
	B <- lists:seq(1,N),
	C <- lists:seq(1,N),
	A+B+C =< N,
	A*A+B*B =:= C*C
	   ].

perms([]) ->
    [[]];
perms(L) ->
    [[H|T] || H <- L,
	      T <- perms(L--[H])].

odds_and_evens_acc(L) ->
    odds_and_evens_acc(L,[],[]).

odds_and_evens_acc([H|T], Odds, Evens) ->
    case (H rem 2) of
	1 ->
	    odds_and_evens_acc(T, [H|Odds], Evens);
	2 ->
	    odds_and_evens_acc(T, Odds, [H|Evens])
    end;
odds_and_evens_acc([], Odds, Evens) ->
    {lists:reverse(Odds), lists:reverse(Evens)}.


sqrt(X) when X < 0 ->
    erlang:error({squareRootNegativeArgument, X});
sqrt(X) ->
    math:sqrt(X).

sleep(T) ->
    receive
    after T ->
	    true
    end.

flush_buffer() ->
    receive
	_Any ->
	    flush_buffer()
    after 0 ->
	    true
    end.

priority_receive() ->
    receive
	{alarm, X} ->
	    {alarm, X}
    after 0 ->
	    receive
		Any ->
		    Any
	    end
    end.

on_exit(Pid, Fun) ->
    spawn(fun() ->
		  process_flag(trap_exit, true),
		  link(Pid),
		  receive
		      {'EXIT', Pid, Why} ->
			  Fun(Why)
		  end
	  end).

keep_alive(Name, Fun) ->
    register(Name, Pid = spawn(Fun)),
    on_exit(Pid, fun(_Why) ->
			 keep_alive(Name, Fun) end).

consult(File) ->
    case file:open(File, read) of
	{ok, S} ->
	    Val = consult1(S),
	    file:close(S),
	    {ok, Val};
	{error, Why} ->
	    {error, Why}
    end.

consult1(S) ->
    case io:read(S, '') of
	{ok, Term} ->
	    [Term | consult1(S)];
	eof ->
	    [];
	Error ->
	    Error
    end.
