#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t p;
  printf("Starting the fork\n");
  p = fork();
  // block code for the child process
  if(p == 0) {
	  printf("I am a child process: %d\n", getpid());
	  printf("My parent id is %d\n", getppid());
  }

  // block of code for the parent process
  else {
  	printf("I am parent process: %d\n", getpid());
	  printf("My child id is %d\n", p);
	  sleep(15);
  	wait(NULL);
  }
}
