#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <cmath>

using namespace std::chrono;
using namespace std;


long d5sum(int n)
{
  long sum = 0;
  while(n > 0) {
    sum += pow(n % 10, 5);
    n /= 10;
  }
  return sum;
}
int main()
{
  auto t1 = high_resolution_clock::now();

  int sum = 0;
  for(int i = 10; i < 200000; ++i) {
    long s = d5sum(i);
    if(s == i) {
      cout << i << endl;
      sum += i;
    }
  }

    cout << sum << endl;


  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

