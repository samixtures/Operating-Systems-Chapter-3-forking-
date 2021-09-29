//
//  main.c
//  fork
//
//  Created by William McCarthy on 1/26/19.
//  Copyright © 2019 William McCarthy. All rights reserved.
//

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, const char * argv[]) {
  pid_t pid;
  
  pid = fork();   // fork a child process
  
  if (pid < 0) {
    fprintf(stderr, "Fork failed\n");
    return 1;
  } else if (pid == 0) {
    execlp("/bin/ls", "ls", NULL);    // child process
    
    printf("these lines of code will never be run!\n");
    printf("    because execlp(...) completely replaces the child's code\n");
    printf("    with its own code\n");
  } else {   // parent process
    printf("the child's pid: %d, and parent's pid: %d\n\n", pid, getpid());
    wait(NULL);
    printf("************************************* Child complete\n");
  }
  
  printf("Parent complete\n\n");
  return 0;
}
/*
Name: Sami Bajwa      Class: CPSC 351-02 13500
DateClient.java
DateServer.java
fig3-30
fig3-30.c
fig3-31.c
fig3-32.c
fig3-33.c
fig3-34.c
fig3-35.c
fork
fork.cpp
fork.txt
multi-fork
multi-fork.c
newproc-posix.c
newproc-win32.c
pid.c
shm-posix-consumer.c
shm-posix-producer.c
simple-shell.c
unix_pipe.c
win32-pipe-child.c
win32-pipe-parent.c
the child's pid: 10953, and parent's pid: 10952

************************************* Child complete
Parent complete

*/