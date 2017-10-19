/*
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXARGS 20  /* the number of arguments */
#define ARGLEN  100 /* the length of a argument */

/* begin Malloc */
void *Malloc(size_t size) {
    void *p;
    p = malloc(size);
    if (p == NULL) {
        fprintf(stderr, "malloc allocated error!");
        exit(1);
    }
    return p;
}
/* end Malloc */

char *makestring();
int execute(char *arglist[]);

int main()
{
    char *arglist[MAXARGS], argbuf[ARGLEN];
    char numargs = 0;

    while(numargs < MAXARGS) {
        printf("arg[%d] = ", numargs);
        /* argbuf store argument */
        if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
            arglist[numargs++] = makestring(argbuf);
        else { /* *argbuf only is '\n' */
            if (numargs > 0) {
                arglist[numargs] = NULL; // the last argument must be null!
                execute(arglist); // execute arglist[0];
                numargs = 0; // reset
            }
        }
    }
    return 0;
}

int execute(char *arglist[])
{
    execvp(arglist[0], arglist);
    perror("execvp failed");
    exit(1);
}

char *makestring(char *buf)
{
    char *cp;

    /* only keep character */
    buf[strlen(buf)-1] = '\0';
    /* because strlen doesn't count '\0' */
    cp = Malloc(strlen(buf)+1);
    strcpy(cp, buf);
    return cp;
}
