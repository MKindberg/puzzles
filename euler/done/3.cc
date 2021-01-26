#!/bin/bash
tail +3 $0 | g++ -x c++ - && exec ./a.out

#include <iostream>
#include <math.h>

using std::cout;
using std::endl;

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
  long n = 600851475143;
  int p = 3;
  for(; n > 1; p += 2)
    if(is_prime(p))
      while(n % p == 0)
        n /= p;
  cout << p-2 << endl;

  
  return 0;
}

