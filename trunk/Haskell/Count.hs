module Count where

import Char

count1 p l = length (filter p l)
count2 p l = foldr (\x c -> if p x then c+1 else c) 0 l
