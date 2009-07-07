module Main where

import Syntax

main = do
     hSetBuffering stdin LineBuffering
     putStrLn "Please enter your name:"
     name <- getLine
     putStrLn ("Hello, " ++ name ++ ", how are you?")

f x = length x
square :: Int -> Int
square x = x*x

data Pair a b = Pair a b
pairFst (Pair x y) = x
pairSnd (Pair x y) = y

data Triple a b c = Triple a b c
tripleFst (Triple a b c) = a
tripleSnd (Triple a b c) = b
tripleTrd (Triple a b c) = c

--data Maybe a = Nothing | Just a

firstElement :: [a] -> Maybe a
firstElement [] = Nothing
firstElement (x:xs) = Just x

findElement :: (a -> Bool) -> [a] -> Maybe a
findElement p [] = Nothing
findElement p (x:xs) = 
	if p x then Just x
	else findElement p xs

data Tuple a b c d = 
	One a
	| Two a b
	| Three a b c
	| Four a b c d

tuple1 (One a) = Just a
tuple1 (Two a b) = Just a
tuple1 (Three a b c) = Just a
tuple1 (Four a b c d) = Just a

tuple2 (One a) = Nothing
tuple2 (Two a b) = Just b
tuple2 (Three a b c) = Just b
tuple2 (Four a b c d) = Just b

tuple3 (One a) = Nothing
tuple3 (Two a b) = Nothing
tuple3 (Three a b c) = Just c
tuple3 (Four a b c d) = Just c

tuple4 (One a) = Nothing
tuple4 (Two a b) = Nothing
tuple4 (Three a b c) = Nothing
tuple4 (Four a b c d) = Just d

data BinaryTree a
	= Leaf a
	| Branch (BinaryTree a) a (BinaryTree a)

--data Leaf a = Leaf a

--data Branch a b = Branch a b a



