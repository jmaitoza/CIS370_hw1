#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid, pid1;
  // fork a child process
  pid = fork();

  if (pid > 0) {
    // parent process
    wait(NULL);
    pid1 = getpid();
    printf("parent: pid = %d\n", pid);   // A
    printf("parent: pid1 = %d\n", pid1); // B
  }

  else if (pid == 0) {
    // child process
    pid1 = getpid();
    printf("child: pid = %d\n", pid);   // C
    printf("child: pid1 = %d\n", pid1); // D
  }

  else {
    // error occured
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  return 0;
}
