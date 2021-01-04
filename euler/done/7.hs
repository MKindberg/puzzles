is_prime :: (Integral a) => a -> Bool
is_prime 1 = False
is_prime 2 = True
is_prime n = mod n 2 /= 0 && all ((0 /=) . (mod n)) [3, 5.. floor . sqrt $ fromIntegral n]

main = do print . last . (take 10001) $ filter is_prime $ 2:[3, 5..]
