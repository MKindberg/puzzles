#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <vector>
#include <cmath>

using namespace std::chrono;
using namespace std;

vector<bool> primes_below(int max)
{
  int count = 1;
  vector<bool> numbers(max, false);
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

  return numbers;
}

bool prime_left(vector<bool>& is_prime, int n)
{
  while(n > 0) {
    if(!is_prime[n])
      return false;
    n /= 10;
  }
  return true;
}

bool prime_right(vector<bool>& is_prime, int n)
{
  int l = log10(n);
  while(l >= 0) {
    if(!is_prime[n])
      return false;
    n = n % (int)pow(10, l--);
  }
  return true;
}

int main()
{
  auto t1 = high_resolution_clock::now();

  vector<bool> is_prime = primes_below(1000000);
  int sum = 0;
  for(int i = 9, count = 0; count < 11; ++i)
    if(prime_left(is_prime, i) && prime_right(is_prime, i)) {
      ++count;
      sum += i;
    }

  cout << sum << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

