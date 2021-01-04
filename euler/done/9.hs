main = do print . product . head $ [[x, y, 1000-x-y] | x <- [1..500], y <- [x..500], x^2 + y^2 == (1000-x-y)^2]
