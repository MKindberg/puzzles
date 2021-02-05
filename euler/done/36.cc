#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <cmath>

using namespace std::chrono;
using namespace std;

bool dec_palindrome(int n)
{
  int l = log10(n);
  for(int i = 0; i < l; ++i, --l) {
    if((int)(n/pow(10, i)) % 10 != (int)(n/pow(10, l)) % 10)
      return false;
  }
  return true;
}
bool bin_palindrome(int n)
{
  int l = log2(n);
  for(int i = 0; i < l; ++i, --l) {
    if(n/(1<<i) % 2 != n/(1<<l) % 2)
      return false;
  }
  return true;
}

int main()
{
  auto t1 = high_resolution_clock::now();

  int limit = 1000000;
  int sum = 0;
  for(int i = 0; i < limit; ++i)
    if(dec_palindrome(i) && bin_palindrome(i))
      sum += i;

  cout << sum << endl;
  cout << 872187 << endl;
  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

