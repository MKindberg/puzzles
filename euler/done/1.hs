main = do
  print . sum . takeWhile (<1000) $ filter ( \ x -> mod x 3 == 0 || mod x 5 == 0 ) [1..]
