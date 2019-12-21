#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#define MEMSIZE (10000)

long* getParam(long* cmds, int pos, int relBase, long cmd, short param)
{
  int mode = cmd/((int)pow(10, param+1)) % 10;
  int ret = 0;
  switch(mode) {
    case 0:
      ret = cmds[pos];
      break;
    case 1:
      ret = pos;
      break;
    case 2:
      ret = relBase+cmds[pos];
      break;
    default:
      fprintf(stderr, "Invalid mode %d\n", mode);
      exit(1);
  }
  if(ret > MEMSIZE || ret < 0) {
    fprintf(stderr, "Trying to read outside memory %d", ret);
    exit(1);
  }
  return &cmds[ret];
}

int execute(long* cmds, int* cmdN, long* input, int inlen, long* output)
{
  int outlen = 1, incount = 0, relBase = 0;
  long p1, p2, *pp1;

  while(*cmdN < MEMSIZE) {
    int cmd = cmds[(*cmdN)++];
    switch(cmd % 100) {
      case 1: // Add
        p1 = *getParam(cmds, (*cmdN)++, relBase, cmd, 1);
        p2 = *getParam(cmds, (*cmdN)++, relBase, cmd, 2);
        pp1 = getParam(cmds, (*cmdN)++, relBase, cmd, 3);
        *pp1 = p1 + p2;
        break;
      case 2: // Multiply
        p1 = *getParam(cmds, (*cmdN)++, relBase, cmd, 1);
        p2 = *getParam(cmds, (*cmdN)++, relBase, cmd, 2);
        pp1 = getParam(cmds, (*cmdN)++, relBase, cmd, 3);
        *pp1 = p1 * p2;
        break;
      case 3: // Input
        pp1 = getParam(cmds, (*cmdN)++, relBase, cmd, 1);
        if(inlen-- == -1) {
          fprintf(stderr, "Error: no data for input");
          return 2;
        } else {
          *pp1 = input[inlen];
        }
        break;
      case 4: // Output
        p1 = *getParam(cmds, (*cmdN)++, relBase, cmd, 1);
        *output = p1;
        printf("%ld\n", *output);
        break;
      case 5: // Jump if true
        p1 = *getParam(cmds, (*cmdN)++, relBase, cmd, 1);
        p2 = *getParam(cmds, (*cmdN)++, relBase, cmd, 2);
        if(p1)
          (*cmdN) = p2;
        break;
      case 6: // Jump if false
        p1 = *getParam(cmds, (*cmdN)++, relBase, cmd, 1);
        p2 = *getParam(cmds, (*cmdN)++, relBase, cmd, 2);
        if(!p1)
          (*cmdN) = p2;
        break;
      case 7: // Less than
        p1 = *getParam(cmds, (*cmdN)++, relBase, cmd, 1);
        p2 = *getParam(cmds, (*cmdN)++, relBase, cmd, 2);
        pp1 = getParam(cmds, (*cmdN)++, relBase, cmd, 3);
        *pp1 = p1 < p2;
        break;
      case 8: // Equals
        p1 = *getParam(cmds, (*cmdN)++, relBase, cmd, 1);
        p2 = *getParam(cmds, (*cmdN)++, relBase, cmd, 2);
        pp1 = getParam(cmds, (*cmdN)++, relBase, cmd, 3);
        *pp1 = p1 == p2;
        break;
      case 9: // Set relative base
        p1 = *getParam(cmds, (*cmdN)++, relBase, cmd, 1);
        relBase += p1;
        break;
      case 99: // Exit
        return 0;
      default: // Error
        fprintf(stderr, "Something went wrong\n");
        return 2;
    }
  }
  return 0;
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

  long* commands = calloc(MEMSIZE, sizeof(int));
  int count = 0;
  // Read data
  while(fscanf(fp, "%ld,", &commands[count++])>0);
  fclose(fp);

  int cmdN = 0;
  long input[1] = {2}, output = 0;
  int inlen = 1;
  execute(commands, &cmdN, input, inlen, &output);

  return 0;
}
