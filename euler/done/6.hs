main = do 
  let limit = 100
  print . (-) ((sum [1..limit])^2) $ sum $ map (^2) [1..limit] 
