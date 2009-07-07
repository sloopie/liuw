safeSnd :: [a] -> Maybe a
safeSnd [] = Nothing
safeSnd xs = if null (tail xs)
             then Nothing
             else Just (head (tail xs))

tidySnd :: [a] -> Maybe a
tidySnd (_:x:_) = Just x
tidySnd _ = Nothing