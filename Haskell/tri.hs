import System.Environment
import Data.List

f' 1 = [0]
f' n = prefix ++ middle ++ postfix
    where
        half = n `div` 2
        (prefix, postfix) = splitAt half $ f' (n-1)
        middle = if odd n then [half] else [half-1]

f'' _ 0 = []
f'' offset n = f'' (offset+1) (n-1) ++ [thisLine]
    where
        thisLine = white ++ (concat $ intersperse " " items)
        white = replicate offset ' '
        items = map (show) (f' n)

f n = mapM_ (putStrLn) $ f'' 0 n

main = do
    [str] <- getArgs
    let n = read str
    f n

