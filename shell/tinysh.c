#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "tinysh.h"

#define DFL_PROMPT "-->"

/* skip blank and tab */
#define is_delim(x) ((x) == ' ' || (x) == '\t')

int main()
{
    char *cmdline, *prompt, **arglist;

    prompt = DFL_PROMPT;
    setup();

    while((cmdline = next_cmd(prompt, stdin)) != NULL) {
        if ((arglist = splitline(cmdline)) != NULL) {
            execute(arglist);
            freelist(arglist);
        }
        Free(cmdline);
    }
    return 0;
}

int execute(char *argv[])
{
    pid_t pid;
    int child_info = -1;

    if (argv[0] == NULL)
        return 0;

    pid = Fork();
    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        execvp(argv[0], argv);
        /* not return */
        perror("can't execute command");
        exit(1);
    }
    else {
        Wait(&child_info);
    }
    
    return child_info;
}

char *next_cmd(char *prompt, FILE *fp)
{
    char *buf;          // the buffer
    int bufspace = 0;   // total size of buffer
    int pos = 0;        // current position
    int c;              // input char 

    printf("%s ", prompt);

    while ((c = getc(fp)) != EOF) { // get char from input
        /* handle buffer size*/
        if (pos + 1 >= bufspace) {
            if (bufspace == 0)
                buf = Malloc(BUFSIZ); // initialization
            else 
                buf = Realloc(buf, bufspace + BUFSIZ); // increase buffer size
            bufspace += BUFSIZ; // increase buffer size
        }
        /* only handle one line*/        
        if (c == '\n')
            break;
        buf[pos++] = c;
    }
    /* handle EOF */
    if (c == EOF && pos == 0)
        return NULL;
    buf[pos] = '\0'; // the last char must be '\0'
    return buf;
}

char **splitline(char *line)
{
    char **args;
    int argsize = 0, bufspace = 0, argnum = 0, len = 0;
    char *cp, *start;
    cp = line;
    
    if (line == NULL)
        return NULL;
    
    args = Malloc(BUFSIZ);
    bufspace = BUFSIZ;
    argsize = BUFSIZ/(sizeof(char *));

    while (*cp != '\0') {
        while (is_delim(*cp))
            cp++;           /* skip spaces */
        if (*cp == '\0')
            break;
        // char pointer size decide how many arguments
        if (argnum + 1 >= argsize) {
            args = Realloc(args, bufspace + BUFSIZ);
            bufspace += BUFSIZ;
            argsize += BUFSIZ/sizeof(char *);
        }

        start = cp;
        len = 1;
        while (*++cp != '\0' && !is_delim(*cp))
             len++;
        args[argnum++] = copystr(start, len);
    }
    args[argnum] = NULL;            // the last element must be NULL
    return args;
}

void setup()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
    fprintf(stderr, "Error: %s, %s\n", s1, s2);
    exit(n);
}

/* construct a string, the string end with '\0'*/
char *copystr(char *s, int l)
{
    char *rv = Malloc(l + 1);
    rv[l] = '\0';
    strncpy(rv, s, l);
    return rv;
}

void freelist(char **list)
{
    char **cp;
    cp = list;
    while (*cp)
        free(*cp++);
    free(list);
}
