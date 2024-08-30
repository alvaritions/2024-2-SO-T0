
#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../input_manager/manager.h"

void lr_hello_world() {
  //
  write(1, "Hello World!\n", 13);
}

void lr_sum(int* nums, int length) {
  //
  int suma = 0;
  for (int i=0; i<length; i++) {
    suma += nums[i];
  }

  // Transformar resultado int a char
  char buffer[20];
  int len_buff = snprintf(buffer, sizeof(buffer),
    "%d\n", suma);
  write(1, buffer, len_buff);
}

void lr_is_prime(int num) {
  //
  bool prime = true;
  for (int i=2; i<num/2 ; i++) {
    if (num % i == 0) {
      prime = false;
    }
  }
  if (prime) write(1, "True\n", 5);
  else write(1, "False\n", 6);
}

void lr_exec() {
  //
}

void lr_list() {
  //
}

void lr_exit() {
  //
}

int get_array_length(char **input) {
    int length = 0;

    // Iterar 
    while (input[length] != NULL) {
        length++;
    }

    return length;
}

int main(int argc, char const *argv[])
{
  char** input;
  while (1) {

    input = read_user_input();


    // Obtener tamaño de array
    int length = get_array_length(input);
    //printf("El array tiene largo: %d\n", length);

    // Si el ID está en 0: Estamos en el proceso hijo
    // Si el ID es > 0: Estamos en el proceso padre
    // fork retorna el id del hijo cuando se está en
    //    el proceso padre.
    pid_t process;
    if (!strcmp("hello", input[0])) {
      process = fork();
      if (process < 0) printf("Error en fork()\n");
      else if (process == 0) // Proceso hijo
      {
        lr_hello_world();
        exit(0);
      }
      else {
        waitpid(process, NULL, 0);
      }
    }

    else if (!strcmp("sum", input[0])) {
      process = fork();
      if (process < 0) printf("Error en fork()\n");
      else if (process == 0) // Proceso hijo
      {
        int* nums_sum = calloc(length - 1, sizeof(int));
        for (int i=1; i<length; i++) {
          nums_sum[i-1] = atoi(input[i]);
        }
        lr_sum(nums_sum, length-1);
        free(nums_sum);
        exit(0);
      }
      else {
        waitpid(process, NULL, 0);
      }
    }

    else if (!strcmp("is_prime", input[0])) {
      process = fork();
      if (process < 0) printf("Error en fork()\n");
      else if (process == 0) // Proceso hijo
      {
        int prime_num = atoi(input[1]);
        lr_is_prime(prime_num);
        exit(0);
      }
      else {
        waitpid(process, NULL, 0);
      }
    }

    else if (!strcmp("lrexec", input[0])) {
    }

    else if (!strcmp("lrist", input[0])) {
    }

    else if (!strcmp("lrexit", input[0])) {
    }

    else if (!strcmp("lrout", input[0])) {
      break;
    }

  }
  free_user_input(input);

  return 0;
}
/*
*/
