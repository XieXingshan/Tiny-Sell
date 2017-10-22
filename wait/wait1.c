#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Wait.h"
#include "Fork.h"

void child_code(int);
void parent_code(pid_t);

#define TIME 2

int main(void)
{
    pid_t newpid;

    printf("before fork(): my pid is %d\n", getpid());

    newpid = Fork();
    if(newpid == 0)
        child_code(TIME);
    else parent_code(newpid);
    
    return 0;
}

void child_code(int delay)
{
    printf("child %d is here. will sleep for %d seconds...\n", getpid(), delay);
    sleep(delay);
    printf("child done. will exit...\n");
    exit(0);
}

void parent_code(pid_t childpid)
{
    pid_t wait_rv;
    wait_rv = Wait(NULL);
    printf("waiting for %d. Wait() return from: %d\n", childpid, wait_rv);
}
