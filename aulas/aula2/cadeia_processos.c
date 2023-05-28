// gcc cadeia_processos.c -o cadeia_processos && ./cadeia_processos 20
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    pid_t childpid = 0;
    int i, n;
    if (argc != 2){ /* check for valid number of command-line arguments */
        fprintf(stderr, "Usage: %s processes\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);//take the integer argument
    for (i = 1; i < n; i++)
        if (childpid = fork())//if value != 0 -> True
            break;
    // fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
    fprintf(stdout, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
    i, (long)getpid(), (long)getppid(), (long)childpid);
    return 0;
}