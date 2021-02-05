#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <numeric>

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();
  int n = 1;
  int d = 1;

  int count = 0;
  for(int i = 10; i < 99; ++i)
    for(int j = i+1; j < 99; ++j)
      if(i%10 == (j/10) && j%10 != 0 && (double)i/j == (double)(i/10)/(j%10) && (double)(i/10)/(j%10) < 1){
        n *= i;
        d *= j;
      }
  cout << d/gcd(n, d) << endl;



  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

