/*
 * this program use to test fork()
 * fork() returns two values, we can know parent or child process
 */

#include <stdio.h>
#include <unistd.h>
#include "Fork.h"

int main()
{
    pid_t fork_rv, mypid;
    mypid = getpid(); // get process id
    printf("before fork(): my pid is %d\n", mypid);

    fork_rv = Fork(); // wrap fork() 

    sleep(1);
    printf("after  fork(): my pid is %d, fork() reture value is %d\n", getpid(), fork_rv);
}
