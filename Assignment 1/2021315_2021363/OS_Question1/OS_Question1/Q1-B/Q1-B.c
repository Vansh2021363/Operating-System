#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// This Function is to calculate factorial of 4.
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
    pid = vfork(); // Here we are Creating  a child process using vfork()
    if (pid == 0)
    {
        // This is the Child process
        printf("Factorial of 4: %d\n", factorial(4));
        _exit(0);
    }
    else if (pid > 0)
    {
        // This is the Parent process
        int temp;
        wait(NULL); // Waiting  for the child process to complete the task first

        // The below block of code is for printing the fibonacci series
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
        printf("child process not created due to some error\n");
        return 1;
    }

    return 0;
}
