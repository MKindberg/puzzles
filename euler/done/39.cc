#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <cmath>

using namespace std::chrono;
using namespace std;

int count_triangles(int perimeter)
{
  int count = 0;
  for(int a = 1; a < perimeter/2; ++a)
    for(int b = 1; b < a; ++b) {
      int c = perimeter - a - b;
      if(a*a + b*b == c*c)
        ++count;
    }
  return count;
}

int main()
{
  auto t1 = high_resolution_clock::now();

  int max = 0;
  int maxP = 0;
  int limit = 1000;
  for(int p = 10; p < limit; ++p) {
    int c = count_triangles(p);
    if(max < c) {
      max = c;
      maxP = p;
    }
  }

  cout << maxP << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

