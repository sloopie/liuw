import Data.Char (digitToInt)
import Data.Char (isDigit)

asInt :: String -> Int

loop :: Int -> String -> Int

asInt xs = loop 0 xs

loop acc [] = acc -- `acc' stands for `accumulate'
loop acc (x:xs) = let acc' = acc * 10 + digitToInt x
                  in loop acc' xs

type ErrorMsg = String
asInt_either :: String -> Either Int ErrorMsg
asInt_either xs | and (map isDigit xs) = Left (loop 0 xs)
                | not (and (map isDigit xs)) = Right "error"