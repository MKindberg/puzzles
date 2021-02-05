#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <vector>

using namespace std::chrono;
using namespace std;

int ways_to_2(vector<int> coins, int idx, int val)
{
  if(idx == coins.size())
    return val == 200 ? 1 : 0;

  
  int count = 0;
  int v;
  for(v = val; v < 200; v += coins[idx])
  {
    count += ways_to_2(coins, idx+1, v);
  }
  if(v == 200)
    count += 1;
  return count;
}

int main()
{
  auto t1 = high_resolution_clock::now();

  vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200};

  cout << ways_to_2(coins, 0, 0) << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

