#include <sys/types.h>
#include <sys/wait.h>

/* begin Wait() */
pid_t Wait(int *status)
{
    pid_t pid;

    if ((pid  = wait(status)) < 0)
       perror("wait error!!!");
    return pid;
}
/* end Wait() */
