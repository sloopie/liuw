module CPS where

cfold' f z [] = z
cfold' f z (x:xs) = f x z (\y -> cfold' f y xs)

--cfold f z l = cfold' (\x t g -> f x (g t)) z l

myfunc f = \x t g -> f x (g t)

cfold f z l = cfold' (myfunc f) z l