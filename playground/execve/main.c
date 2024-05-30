#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char *binaryPath = "/bin/ls";
    char *args[] = {"ls", "-l", NULL};
    char *envp[] = {NULL};

    execve(binaryPath, args, envp);
    perror("execve");
    exit(EXIT_FAILURE);
}
