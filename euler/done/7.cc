#!/bin/bash
tail +3 $0 | g++ -std=c++17 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <math.h>

using namespace std::chrono;
using namespace std;

bool is_prime(int n)
{
  if(n == 2)
    return true;
  if(n % 2 == 0)
    return false;

  for(int i = 3; i < sqrt(n)+1; i += 2)
    if(n % i == 0)
      return false;
  return true;
}

int main()
{
  auto t1 = high_resolution_clock::now();
  int c = 1;
  int p = 3;
  int limit = 10001;
  for(; c < limit; p += 2)
    if(is_prime(p))
      c+=1;
  cout << p-2 << endl;
  
  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

