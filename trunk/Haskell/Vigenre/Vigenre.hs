-- file: Vegenre.hs
-- author: LIU Wei liuw@liuw.name
module Vigenre (encrypt, decrypt)
    where

import Data.List
import Char

-----------------------------------------------------------------
-- helper functions

alphaString :: String
alphaString = ['A'..'Z']

line :: Int -> String
line n = b ++ a
    where 
      (a, b) = splitAt n alphaString

indexOfElement :: Char -> Int -> Int
indexOfElement e n = i
    where
      (Just i) = elemIndex e (line n)

offset :: Char -> Int
offset x = ord x - ord 'A'

adjustKey :: String -> String -> String
adjustKey m k = map toUpper ((concat $ replicate quotient k) 
                             ++ take remainder k)
    where
      quotient =  length m `div` length k
      remainder = length m `mod` length k

-----------------------------------------------------------------

encrypt :: String -> String -> String
encrypt msgString keyString = zipWith encrypt' msgString' keyString'
    where
      encrypt' m k = (line $ offset k) !! (offset m)
      keyString' = map toUpper (adjustKey msgString keyString)
      msgString' = map toUpper msgString
      
decrypt :: String -> String -> String
decrypt msgString keyString = zipWith decrypt' msgString' keyString'
    where
      decrypt' m k = chr (indexOfElement m (offset k) + ord 'A')
      keyString' = map toUpper (adjustKey msgString keyString)
      msgString' = map toUpper msgString
