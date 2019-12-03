#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int calcFuel(int mass)
{
  return mass/3-2;
}
int calcFuelFuel(int mass)
{
  int sum = 0;
  int fuel = mass;
  while((fuel = calcFuel(fuel)) > 0)
    sum += fuel;
  return sum;
}

int main(int argc, const char* argv[])
{
  if(argc < 2) {
    fprintf(stderr, "Please supply a file with input\n");
    return 1;
  }
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL) {
    fprintf(stderr, "Couldn't open file %s: %s", argv[1], strerror(errno));
    return 1;
  }

  int massFuel = 0;
  int fuelFuel = 0;
  char buf[10];
  while(fgets(buf, 10, fp)) {
    int mass = atoi(buf);
    int fuel = calcFuel(mass);
    fuelFuel += calcFuelFuel(fuel);
    massFuel += fuel;
  }
  fclose(fp);

  printf("Sum of fuel requirements for modules: %d\n", massFuel);
  printf("Sum of fuel requirements for modules and fuel: %d\n", massFuel + fuelFuel);

  return 0;
}
