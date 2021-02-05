#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std::chrono;
using namespace std;

int score(string word)
{
  int s = 0;
  for(char c : word)
    s += c - 'A' + 1;

  return s;
}

int triangle(int n)
{
  return(n / 2.0 * (n + 1));
}

int main()
{
  auto t1 = high_resolution_clock::now();

  fstream f;
  f.open("42.in", ios::in);
  if(!f) {
    cout << "Failed to open file" << endl;
    return 1;
  }

  int limit = 200;
  vector<bool> triangles(limit, false);
  int i = 1;
  while(triangle(i) < limit)
    triangles[triangle(i++)] = true;

  int count = 0;
  string word;
  while(getline(f, word, ',')){
    cout << word.substr(1, word.length()-2) << endl;
    if(triangles[score(word.substr(1, word.length() - 2))])
      ++count;
  }
  f.close();

  cout << count << endl;


  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

