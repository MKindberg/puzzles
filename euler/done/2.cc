#!/bin/bash
tail +3 $0 | g++ -x c++ - && exec ./a.out

#include <iostream>

using std::cout;
using std::endl;

int main()
{
  int sum = 2;
  int a = 1;
  int b = 2;
  int limit = 4000000;
  while(a + b < limit) {
    int n = a+b;
    a = b;
    b = n;
    if(n % 2 == 0)
      sum += n;
  }
  cout << sum << endl;
  return 0;
}

