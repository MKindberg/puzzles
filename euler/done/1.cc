#!/bin/bash
tail +3 $0 | g++ -x c++ - && exec ./a.out

#include <iostream>

using std::cout;
using std::endl;

int sum(int multiple, int below)
{
  int max = (below-1) - (below-1) % multiple;
  return (double)(multiple + max)/2 * max/multiple;
}
int main()
{
  int limit = 1000;
  cout << sum(3, limit) + sum(5, limit) - sum(15, limit) << endl;
  return 0;
}

