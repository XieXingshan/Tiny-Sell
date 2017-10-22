#include <stdio.h>
#include <unistd.h>
#include "Fork.h"

int main()
{
    printf("my pid is %d\n", getpid());
    Fork();
    Fork();
    Fork();
    printf("my pid is %d\n", getpid());
}
