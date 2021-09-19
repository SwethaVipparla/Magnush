#include "headers.h"
#include "colours.h"

void fg(char **argv)
{
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid < 0)
        perror(red "Error: Fork Failure\n" reset);

    else if (pid == 0)
    {
        if (execvp(argv[0], argv) < 0)
            printf(red "Command not found" reset ": " bold "%s\n" noBold, argv[0]);
        exit(0);
    }
    
    else
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

