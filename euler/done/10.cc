#!/bin/bash
tail +3 $0 | g++ -std=c++17 -g -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <vector>
#include <utility>
#include <math.h>

using namespace std::chrono;
using namespace std;

vector<int> primes_below(int max)
{
  int count = 1;
  bool numbers[max];
  for(int i = 0; i < max; ++i)
    numbers[i] = i%2 == 1;
  numbers[1] = false;
  numbers[2] = true;
  for(int i = 3; i < sqrt(max); i += 2) {
    if(numbers[i]){
      count += 1;
      for(int j = i*i; j < max; j += i){
        numbers[j] = false;
      }
    }
  }
  vector<int> primes;
  primes.reserve(count);
  primes.push_back(2);
  int idx = 2;
  for(int i = 3; i < max; i += 2)
    if(numbers[i])
      primes.push_back(i);
    
  return primes;
}

int main()
{
  auto t1 = high_resolution_clock::now();

  vector<int> primes = primes_below(2000000);
  long sum = 0;
  for(int p : primes)
    sum += p;

  cout << sum << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

