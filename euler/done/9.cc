#!/bin/bash
tail +3 $0 | g++ -std=c++17 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();

  for(int a = 1; a < 1000; ++a)
    for(int b = 1; b < a; ++b) {
      int c = 1000 - a - b;
      if(a*a + b*b == c*c) {
        cout << a*b*c << endl;
        goto done;
      }
    }

done:
  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

