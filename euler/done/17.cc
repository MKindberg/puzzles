#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <string>

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();

  int singles = string("one""two""three""four""five""six""seven""eight""nine").length();
  int teens = string("ten""eleven""twelve""thirteen""fourteen""fifteen""sixteen""seventeen""eighteen""nineteen").length();
  int tens = string("twenty""thirty""fourty""fifty""sixty""seventy""eighty""ninety").length()*10 + singles*8;
  int hundreds = singles + string("hundred").length()*9 + (singles + string("hundred""and").length() *9)*99+ (singles + teens + tens)*9;
  int thousand = string("one""thousand").length();

  int letters = singles + teens + tens + hundreds + thousand;

  cout << letters << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

