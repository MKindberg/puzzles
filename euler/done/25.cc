#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <vector>

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();

  vector<int> ds[2];
  ds[0] = {1};
  ds[1] = {1};

  int digit_goal = 1000;
  int count = 2;
  while(ds[0].size() < digit_goal && ds[1].size() < digit_goal) {
    int rest = 0;
    for(int i = 0; i < ds[count%2].size(); ++i) {
      int n = ds[0][i] + ds[1][i]  + rest;
      ds[count%2][i] = n % 10;
      rest = n / 10;
    }
    if(ds[count%2].size() < ds[(count+1)%2].size())
      rest += ds[(count+1)%2][ds[(count+1)%2].size()-1];
    while(rest != 0) {
      ds[count%2].push_back(rest%10);
      rest /= 10;
    }
    ++count;
  }

  cout << count << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

