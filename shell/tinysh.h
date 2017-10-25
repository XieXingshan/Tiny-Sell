#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char *next_cmd(char *, FILE *);
char **splitline(char *);
void freelist(char **);
int execute(char **);
void setup(void);
void fatal(char *, char *, int);
char *copystr(char *, int);


/* begin Fork() */
pid_t Fork(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
	    perror("fork error!!!");
    return pid;
}
/* end For() */

/* begin Wait() */
pid_t Wait(int *status)
{
    pid_t pid;

    if ((pid  = wait(status)) < 0)
       perror("wait error!!!");
    return pid;
}
/* end Wait() */

/* begin Free() */
void Free(void *ptr) 
{
    free(ptr);
}
/* end Free() */

/* begin Malloc() */
void *Malloc(size_t size) 
{
    void *p;

    if ((p  = malloc(size)) == NULL)
	    perror("malloc error!!!");
    return p;
}
/* end Malloc() */

/* begin Realloc() */
void *Realloc(void *ptr, size_t size) 
{
    void *p;

    if ((p  = realloc(ptr, size)) == NULL)
	    perror("realloc error!!!");
    return p;
}
/* end Realloc() */
