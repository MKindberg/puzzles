fibonacci a b = [a] ++ fibonacci b (a + b)
main = do print . sum . takeWhile (<4000000) $ filter even $ fibonacci 1 2
