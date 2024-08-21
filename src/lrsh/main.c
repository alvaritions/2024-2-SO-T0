
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../input_manager/manager.h"

int main(int argc, char const *argv[])
{
  char** input = read_user_input();
  printf("Holaaa\n");
  //int pid = fork();

  //printf("%d\n", pid);


  free_user_input(input);
}
