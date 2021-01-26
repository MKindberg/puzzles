#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();

  int limit = 20;
  long m[limit+1][limit+1];
  for(int i = 0; i < limit+1; ++i){
    m[i][0] = 1;
    m[0][i] = 1;
  }

  for(int i =1; i < limit+1; ++i)
    for(int j = 1; j < limit+1; ++j)
      m[i][j] = m[i-1][j] + m[i][j-1];

  cout << m[limit][limit] << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

