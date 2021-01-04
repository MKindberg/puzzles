is_palindrome n = (==) (show n) (reverse $ show n)

main = do print . (foldl max 0) . (filter is_palindrome) $ [x*y | x <- [999, 998..100], y <- [999, 998..100]]
