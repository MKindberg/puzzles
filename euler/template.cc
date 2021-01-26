#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();



  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

