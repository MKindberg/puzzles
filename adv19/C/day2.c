#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int execute(int* commands, int len, int noun, int verb)
{
  int* cmds = malloc(len*sizeof(int));
  memcpy(cmds, commands, len*sizeof(int));
  cmds[1] = noun;
  cmds[2] = verb;

  for(int i = 0; i < len; i+=4) {
    int cmd = cmds[i];
    int pos1 = cmds[i+1];
    int pos2 = cmds[i+2];
    int num1 = cmds[pos1];
    int num2 = cmds[pos2];
    int store = cmds[i+3];
    switch(cmd) {
      case 1:
        cmds[store] = num1 + num2;
        break;
      case 2:
        cmds[store] = num1 * num2;
        break;
      case 99:
        goto cleanup;
        break;
      default:
        fprintf(stderr, "Something went wrong");
        exit(1);
      break;
    }
  }

cleanup: ;
  int res = cmds[0];
  free(cmds);
  return res;
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
  int* commands = malloc(200*sizeof(int));
  int count = 0;
  while(fscanf(fp, "%d,", &commands[count++])>0);

  int res = execute(commands, count, 12, 2);
  printf("Result for 1202: %d\n", res);

  int noun = 0, verb = 0;
  for(noun = 0; noun < 100; ++noun)
    for(verb = 0; verb < 100; ++verb){
      if(execute(commands, count, noun, verb) == 19690720)
        goto exit;
    }
exit:
  printf("Code %d gives the correct result\n", 100*noun+verb);

  return 0;
}
