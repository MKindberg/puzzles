#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <fstream>
#include <math.h>

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();

  fstream f;
  f.open("13.in", ios::in);
  if(!f) {
    cout << "Failed to open file" << endl;
    return 1;
  }

  string numbers[100];
  int i = 0;
  string line;
  while(getline(f, line))
    numbers[i++] = line;
  f.close();

  long sum = 0;
  int e = 0;
  for(int j = 49; j >= 0; --j) {
    for(i = 0; i < 100; ++i)
      sum += (numbers[i][j] - 48) * pow(10, e);
    e += 1;
    while(sum > 9999999999) {
      sum /= 10;
      e -= 1;
    }
  }
  cout << sum << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

