#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to calculate factorial
int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    if (n == 1)
    {
        return 1;
    }

    return n * factorial(n - 1);
}

int main()
{
    pid_t pid;
    pid = vfork(); // Creating the child process using vfork()

    if (pid == 0)
    {
        // This is the Child process
        wait(NULL); // Waiting for the parent process to complete the task
        printf("Factorial of 4: %d\n", factorial(4));
        _exit(0);
    }
    else if (pid > 0)
    {
        // This is the Parent process

        int first = 0;
        int second = 1;
        int temp1;
        int i = 0;
        printf("First 16 elements in Fibonacci Series: ");
        while (i < 16)
        {
            printf("%d ", first);
            temp1 = first; 
            temp1 += second;
            first = second;
            second = temp1;
            i++;
        }
        printf("\n");
    }
    else
    {
        perror("child process not created due to some error\n");
        return 1;
    }

    return 0;
}
