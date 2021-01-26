import Data.Array.Unboxed

primes :: Int -> [Int]
primes n = 2 : [ fst p | p <- assocs a, snd p]
  where a = f 3 $ array (2, n) [(i, mod i 2 == 1) | i <- [2..n]]
        f :: Int -> UArray Int Bool -> UArray Int Bool
        f p l | p*p > n = l
              | l ! p = f (p+2) $ l // [(i, False) | i <- [p*p,p*p+p..n]]
              | otherwise = f (p+2) l

main = do print . sum $ primes 2000000
