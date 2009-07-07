module Test where
roots a b c = 
	let 	det = sqrt (b*b - 4*a*c)
		twice_a = 2 * a
	in	((-b + det) / twice_a, (-b - det) / twice_a)

my_length [] = 0
my_length (x:xs) = 1 + my_length xs

signum x =
	if x < 0
		then -1
		else if x > 0
			then 1
			else 0
fib 1 = 1
fib 2 = 1
fib x = fib (x-2) + fib(x-1)

mult a 0 = 0
mult a 1 = a
mult a b = mult a (b-1) + a

my_map p [] = []
my_map p (x:xs) = 
	p x : my_map p xs

square = \x -> x*x
f = \x y -> 2*x+y
