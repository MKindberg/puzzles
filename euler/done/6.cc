#!/bin/bash
tail +3 $0 | g++ -std=c++17 -x c++ - && exec ./a.out

#include <iostream>

using namespace std;

int main()
{
  int sum = 0;
  int ssum = 0;
  int limit = 100;
  for(int i = 1; i <= limit; ++i) {
    sum += i;
    ssum += i*i;
  }
  cout << sum*sum - ssum << endl;

  return 0;
}

