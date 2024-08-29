
#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../input_manager/manager.h"

void forkexample() 
{ 
    pid_t p;
    pid_t pp;
    pp = getpid();
    printf("Hellooooo! %d\n", pp);
    p = fork();
    int x = 10;
    if(p<0) 
    { 
      perror("fork fail"); 
      exit(1); 
    } 
    // child process because return value zero 
    else if ( p == 0) {
        x++;
        printf("Hello from Child! %d (%d)\n", p, getpid()); 
        printf("\tMy Father is: %d\n", getppid());
        printf("\tx = %d\n", x);
    }

    else if ( p == pp) {
      printf("Hellooooo! %d\n", pp);
      printf("\tx = %d\n", x);
    }
  
    // parent process because return value non-zero. 
    else {
        x--;
        printf("Hello from Parent! %d (%d)\n", p, getpid()); 
        printf("\tMy Father is: %d\n", getppid());
    }
    printf("\n");
    printf("\tx = %d (%d)\n", x, getpid());
}

void waitexample() {
    pid_t pid;

    // Create a new process using fork()
    pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is running...\n", getpid());
        sleep(2); // Simulate some work by sleeping for 2 seconds
        printf("Child process (PID: %d) is exiting...\n", getpid());
        exit(0);  // Child process exits
    } else {
        // Parent process
        printf("Parent process (PID: %d) is waiting for the child process (PID: %d) to finish...\n", getpid(), pid);
        
        // Wait for the child process to complete
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Child process (PID: %d) exited with status: %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("Child process (PID: %d) did not exit successfully.\n", pid);
        }
        
        printf("Parent process (PID: %d) is exiting...\n", getpid());
    }
}

int main(int argc, char const *argv[])
{
  //char** input = read_user_input();

  //printf("%s\n", input[0]);
  //printf("%s\n", input[1]);

  //if (!strcmp("hello", input[0])) {
  //  write(1, "World\n", 6);
    // write (
    //   1 -> escribir en consola,
    //   "mensaje",
    //   6 -> len("mensaje")
    // )
  //}
  //free_user_input(input);

  //forkexample();
  waitexample();
  
  return 0;
}
/*
*/
