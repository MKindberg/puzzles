#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();

  fstream f;
  f.open("67.in", ios::in);
  if(!f) {
    cout << "Failed to open file" << endl;
    return 1;
  }

  int size = 100;
  int pyramid[size][size+1];
  for(int i = 0; i < size; ++i)
    for(int j = 0; j < size+1; ++j)
      pyramid[i][j] = -1;

  int row = 0;
  int col = 1;
  string line;
  while(getline(f, line)) {
    stringstream ss(line);
    string number;
    while(getline(ss, number, ' ')) {
      pyramid[row][col++] = atoi(number.c_str());
    }
    col = 1;
    ++row;
  }
  f.close();

  for(int i = 1; i < size; ++i){
    for(int j = 1; j < size+1 && pyramid[i][j] != -1; ++j){
      pyramid[i][j] += max(pyramid[i-1][j-1], pyramid[i-1][j]);
    }
  }
  int m = 0;
  for(int s : pyramid[size-1])
    if(m < s)
      m = s;

  cout << m << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

