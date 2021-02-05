#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 

using namespace std::chrono;
using namespace std;

int fac_sum(int n)
{
  int sum = 0;
  while(n > 0) {
    int d = n % 10;
    int p = 1;
    for(int i = 1; i <= d; ++i)
      p *= i;
    sum += p;
    n /= 10;
  }
  return sum;
}

int main()
{
  auto t1 = high_resolution_clock::now();

  int sum = 0;
  for(int i = 10; i < 50000; ++i)
    if(i == fac_sum(i))
      sum += i;

  cout << sum << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

