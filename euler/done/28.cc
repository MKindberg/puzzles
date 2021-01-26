#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();

  int s = 1;
  int n = 1;
  for(int step_size = 2; step_size < 1001; step_size += 2)
    for(int step = 0; step < 4; ++step){
      n += step_size;
      s += n;
    }

  cout << s << endl;


  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

