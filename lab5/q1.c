#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        printf("im a child. PID=%d, PPID=%d\n", getpid(), getppid());
    }
    else if (pid > 0)
    {
        printf("im a parent. PID=%d, PPID=%d\n", getpid(), getppid());
    }
    else
    {
        perror("Fork failed!");
        return 1;
    }

    return 0;
}
