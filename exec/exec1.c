/*
 * exec1.c - run a program in a program
 */
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    /* arglist is a array, its element is char pointer*/
    char *arglist[3];

    arglist[0] = "ls";
    arglist[1] = "-l";
    arglist[2] = NULL; // the last element must be null!

    printf("*** use exec to run shell command ls -l ***\n");
    execvp(arglist[0], arglist);
    printf("*** it doesn't print this message! ***");
}
