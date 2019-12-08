#include <stdio.h>
#include <stdlib.h>

int nextPw(int pw)
{
  ++pw;
  // Both start and end the string with NULL so it's possible to compare one step outside the string.
  char pwS[10] = {0};
  snprintf(&pwS[1], 9, "%d", pw);

  // Make sure digits never decrease
  for(int i = 2; pwS[i]; ++i) {
    if(pwS[i] < pwS[i-1])
      pwS[i] = pwS[i-1];
  }

  // Make sure the pw contains dubble digits (Part 1)
  /*for(int i = 2; pwS[i]; ++i) {
    if(pwS[i] == pwS[i-1])
      return(atoi(&pwS[1]));
  }*/

  // Make sure the pw contains dubble digits but no more than double (Part 2)
  for(int i = 2; pwS[i]; ++i) {
    if(pwS[i] == pwS[i-1] && pwS[i] != pwS[i+1] && pwS[i-1] != pwS[i-2])
      return(atoi(&pwS[1]));
  }

  return nextPw(atoi(&pwS[1]));
}

int main(int argc, char* argv[])
{
  if(argc < 3)
  {
    fprintf(stderr, "Please provide both min and max values");
    return 1;
  }
  int min = atoi(argv[1]);
  int max = atoi(argv[2]);

  int pw = min;
  int count = 0;
  while((pw = nextPw(pw)) < max)
    ++count;

  printf("There are  %d valid passwords in the given range", count);
}
