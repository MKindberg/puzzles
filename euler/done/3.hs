is_prime :: (Integral a) => a -> Bool
is_prime 1 = False
is_prime 2 = True
is_prime n = mod n 2 /= 0 && all ((0 /=) . (mod n)) [3, 5.. floor . sqrt $ fromIntegral n]

prime_factors_rec :: (Integral a) => a -> [a] -> [a]
prime_factors_rec 1 _ = []
prime_factors_rec n (p:ps)
  | mod n p == 0 = (:) p $ prime_factors_rec (div n p) (p:ps)
  | otherwise = prime_factors_rec n ps
 
prime_factors :: (Integral a) => a -> [a]
prime_factors n = prime_factors_rec n $ filter is_prime (2:[3, 5..])

main = do print . last . prime_factors $ 600851475143
