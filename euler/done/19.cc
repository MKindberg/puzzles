#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <vector>

using namespace std::chrono;
using namespace std;

bool is_leap(int y)
{
  return y % 4 == 0 && y % 100 != 0 || y % 100 == 0 && y % 400 == 0;
}
int main()
{
  auto t1 = high_resolution_clock::now();

  vector<int> months {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int day = 365;
  int sundays = 0;
  for(int m = 0; m < 12*100; ++m){
    if(day % 7 == 6)
      ++sundays;
    if(is_leap(m/12 + 1901) && m % 12 == 1)
      day += 29;
    else
      day += months[m % 12];
  }

  cout << sundays << endl;




  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

