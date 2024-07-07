#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork(); // Creating the child process using fork().

    if (pid == 0)
    {
        // This is the Child process
        printf("C) Child is having ID %d\n", getpid());
        printf("D) My Parent ID is %d\n", getppid());
        
    }
    else if (pid > 0)
    {
        // This is the Parent process
        printf("A) Parent (P) is having ID %d\n", getpid());

        // Waiting for the child process to complete the task.
        wait(NULL);

        printf("B) ID of P's Child is %d\n", pid);

    }
    else
    {
        printf("child process not created due to some error\n");
        return 1;
    }

    return 0;
}
