#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

void swap(int* array, int i, int j)
{
  int temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

int permutations(int (*perms)[5], int index, int* seq, int current, int len)
{
  if(current == len-1)
    memcpy(perms[index++], seq, len*sizeof(int));

  for(int i = current; i < len; ++i) {
    swap(seq, current, i);
    index = permutations(perms, index, seq, current+1, len);
    swap(seq, current, i);
  }
  return index;
}

int getParam(int* cmds, int pos, int cmd, int param)
{
  int mode = cmd/((int)pow(10, param+1)) % 10;
  if(mode == 0)
    return cmds[cmds[pos]];
  else if(mode == 1)
    return cmds[pos];

  fprintf(stderr, "Invalid mode\n");
  exit(1);
}

int execute(int* cmds, int cmdlen, int* cmdN, int* input, int inlen, int* output)
{
  int p1, p2, p3, in, outlen = 1, incount = 0;

  while(*cmdN < cmdlen) {
    int cmd = cmds[(*cmdN)++];
    switch(cmd % 100) {
      case 1: // Add
        p1 = getParam(cmds, (*cmdN)++, cmd, 1);
        p2 = getParam(cmds, (*cmdN)++, cmd, 2);
        p3 = cmds[(*cmdN)++];
        cmds[p3] = p1 + p2;
        break;
      case 2: // Multiply
        p1 = getParam(cmds, (*cmdN)++, cmd, 1);
        p2 = getParam(cmds, (*cmdN)++, cmd, 2);
        p3 = cmds[(*cmdN)++];
        cmds[p3] = p1 * p2;
        break;
      case 3: // Input
        p1 = cmds[(*cmdN)++];
        if(inlen-- == -1) {
          fprintf(stderr, "Error: no data for input");
          return 2;
        } else {
          cmds[p1] = input[inlen];
        }
        break;
      case 4: // Output
        p1 = getParam(cmds, (*cmdN)++, cmd, 1);
        *output = p1;
        return 1;
        break;
      case 5: // Jump if true
        p1 = getParam(cmds, (*cmdN)++, cmd, 1);
        p2 = getParam(cmds, (*cmdN)++, cmd, 2);
        if(p1)
          (*cmdN) = p2;
        break;
      case 6: // Jump if false
        p1 = getParam(cmds, (*cmdN)++, cmd, 1);
        p2 = getParam(cmds, (*cmdN)++, cmd, 2);
        if(!p1)
          (*cmdN) = p2;
        break;
      case 7: // Less than
        p1 = getParam(cmds, (*cmdN)++, cmd, 1);
        p2 = getParam(cmds, (*cmdN)++, cmd, 2);
        p3 = cmds[(*cmdN)++];
        cmds[p3] = p1 < p2;
        break;
      case 8: // Equals
        p1 = getParam(cmds, (*cmdN)++, cmd, 1);
        p2 = getParam(cmds, (*cmdN)++, cmd, 2);
        p3 = cmds[(*cmdN)++];
        cmds[p3] = p1 == p2;
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
  int count = 1;
  int dummy;
  // Read length of data
  while(fscanf(fp, "%d,", &dummy)>0)
    ++count;
  rewind(fp);

  int* commands = malloc(count*sizeof(int));
  count = 0;
  // Read data
  while(fscanf(fp, "%d,", &commands[count++])>0);

  int (*perms)[5] = malloc(120*5*sizeof(int));

  int input[2] = {0};
  int output, status, max = 0;
  //int seq[5] = {0,1,2,3,4};
  int seq[5] = {5,6,7,8,9};
  int index = permutations(perms, 0, seq, 0, 5);
  int *perm;
  int *cmds[5], cmdN[5];
  for(int i = 0; i < 5; ++i)
    cmds[i] = malloc(count*sizeof(int));

  for(int j = 0; j < 120; ++j) {
    perm = perms[j];
    input[0] = 0;
    int inlen = 2;
    // Reset cmds
    for(int i = 0; i < 5; ++i) {
      memcpy(cmds[i], commands, count*sizeof(int));
      cmdN[i] = 0;
    }
    do {
      for(int i = 0; i < 5; ++i) {
        input[1] = perm[i];
        status = execute(cmds[i], count, &cmdN[i], input, inlen, &output);
        input[0] = output;
      }
      inlen = 1;
    } while(status == 1);

    if (output > max)
      max = output;
  }

  printf("\nLargest output: %d\n", max);

  return 0;
}
