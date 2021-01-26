#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 

using namespace std::chrono;
using namespace std;

int modpow(int b, int e, int m)
{
  int n = 1;
  while(e-- > 0)
    n = n * b % m;

  return n;
}

int main()
{
  auto t1 = high_resolution_clock::now();
  int max = 0;
  int max_p = 0;

  for(int p = 3; p < 1000; p += 2)
    for(int k = 1; k < p; ++k) {
      int r = modpow(10, k, p);
      if(r == 0)
        break;
      if(r == 1) {
        if(max < k) {
          max = k;
          max_p = p;
        }
        break;
      }
    }

  cout << max_p << endl;


  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

