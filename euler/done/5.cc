#!/bin/bash
tail +3 $0 | g++ -std=c++17 -x c++ - && exec ./a.out

#include <iostream>
#include <numeric>

using namespace std;

int main()
{
  int n = 1;
  int limit = 20;
  for(int i = 1; i < limit; ++i)
    n = lcm(n, i);
  cout << n << endl;
  return 0;
}

