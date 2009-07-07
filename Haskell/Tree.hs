data Tree a = Node a (Tree a) (Tree a)
            | Empty
              deriving (Show)
rootTree = Node "root" Empty Empty
simpleTree = Node "root" (Node "left" Empty Empty)
             (Node "right" Empty Empty)

data NewTree a = Node a (Maybe (NewTree a)) (Maybe (NewTree a))
                 deriving (Show)