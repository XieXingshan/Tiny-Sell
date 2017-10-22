#include <unistd.h>

/* begin Fork() */
pid_t Fork(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
	perror("fork error!!!");
    return pid;
}
/* end For() */


