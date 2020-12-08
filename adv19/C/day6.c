#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int find(char (*data)[10], int count, char* item)
{
  int i = 0;
  int len = strlen(item);
  for(i = 0; i < count; ++i)
    if(!strncmp(data[i], item, len))
      break;
  return i;
}
int find2(char (*data)[10], int count, char* item)
{
  int i = 0;
  int len = strlen(item);
  for(i = 0; i < count; ++i) {
    const char* beg = strchr(data[i], ')');
    if(beg != NULL && !strncmp(beg+1, item, len))
      break;
  }
  return i;
}

int done(char (*data)[10], int count)
{
  for(int i = 0; i < count; ++i)
    if(data[i][0] != '\0'){
      return 0;
    }
  return 1;
}

int countLvls(char (*d)[10], int count)
{
  char (*data)[10] = malloc(count*10);
  memcpy(data, d, count*10);
  int c = 0, level = 1, cc = 1, cn = 0;
  char (*curr)[5] = malloc(5*100);
  char (*next)[5] = malloc(5*100);

  strncpy(curr[0], data[find(data, count, "COM")], 5);

  while(!done(data, count)) {
    // Find the children of all objects on this level
    for(int i = 0; i < cc; ++i) {
      int index;
      while((index = find(data, count, curr[i])) != count) {
        const char* pos = strchr(data[index], ')');
        strncpy(next[cn++], pos+1, 5);
        data[index][0] = '\0';
      }
    }
    c += cn*level++; // each object has 1 direct level-1 indirect links
    cc = cn;
    cn = 0;
    // Go down a level
    memcpy(curr, next, 5*100);
    memset(next, 0, 5*100);
  }
  return c;
}

int getParents(char (*d)[10], int count, char (*parents)[10], char* obj)
{
  char (*data)[10] = malloc(count*10);
  memcpy(data, d, count*10);
  int parent = find2(data, count, obj);
  int c = 0;
  strcpy(parents[c++], strtok(data[parent], ")"));
  while(strcmp(parents[c-1], "COM")) {
    parent = find2(data, count, parents[c-1]);
    strcpy(parents[c++], strtok(data[parent], ")"));
  }
  free(data);
  return c;
}

int main(int argc, char* argv[])
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

  char buf[10];
  int count = 0;
  while(fgets(buf, 10, fp))
    count++;
  char (*data)[10] = calloc(count, 10);
  rewind(fp);
  count = 0;
  while(fgets(data[count++], 10, fp)) {
    char *pos;
    if ((pos=strchr(data[count-1], '\n')) != NULL)
      *pos = '\0';
  }

  int links = countLvls(data, count);
  printf("Links: %d\n", links);

  char (*parentsS)[10] = malloc(10*300);
  char (*parentsY)[10] = malloc(10*300);
  int lenS = getParents(data, count, parentsS, "SAN");
  int lenY = getParents(data, count, parentsY, "YOU");
  int i, j;
  for(i = 0; i < lenS; ++i)
    for(j = 0; j < lenY; ++j)
      if(!strcmp(parentsS[i], parentsY[j]))
        goto found;

found:
  printf("%d steps\n", i+j);

  free(data);
  return 0;
}
