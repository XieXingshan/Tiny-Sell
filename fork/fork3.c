#include <stdio.h>
#include <unistd.h>
#include "Fork.h"

int main()
{
    pid_t fork_rv;

    printf("before fork(): my pid is %d\n", getpid());

    fork_rv = Fork();

    if (fork_rv == 0) // child process
        printf("I am the child process. my pid = %d\n", getpid());
    else              // parent process
        printf("I am the parent process. my child is %d\n", fork_rv); 
    return 0;
}
