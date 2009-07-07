module List where

data List a = Nil
            | Cons a (List a)

listLength Nil = 0
listLength (Cons x xs) = 1 + listLength xs

listHead Nil = Nothing
listHead (Cons x xs) = x

--listTail Nil = Nothing
--listTail (Cons x xs) = xs