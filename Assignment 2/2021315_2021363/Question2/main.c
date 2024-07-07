#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sched.h>
#include <sys/resource.h>
#include <stdlib.h>

void Countother() {
    struct sched_param param;
    param.sched_priority = 0;
    int ret=sched_setscheduler(0, SCHED_OTHER, &param);
    if (ret==0)
    {
        setpriority(PRIO_PROCESS, 0, 0);
        execl("./counter", "counter", NULL);
    }
    else 
    {
        perror ("Scheduling not set!");
    }
}

void CountRR(pid_t pid2) {
    struct sched_param param;
    param.sched_priority = 30;
    int ret=sched_setscheduler(pid2, SCHED_RR, &param);
    if (ret==0)
    {    
        execl("./counter", "counter", NULL);
    }
    else 
    {
        perror ("Scheduling not set!");
    }
}

void CountFIFO(pid_t pid3) {
    struct sched_param param;
    param.sched_priority = 60;
    int ret=sched_setscheduler(pid3, SCHED_FIFO, &param);
    if (ret==0)
    {    
        execl("./counter", "counter", NULL);
    }
    else 
    {
        perror ("Scheduling not set!");
    }
}

int main(int argc, char **argv) {
    pid_t pid1, pid2, pid3;
    struct timespec start1, finish1;

    double elapsed1;
    clock_gettime(CLOCK_REALTIME, &start1);
    pid1 = fork();
    if (pid1 == 0) {
        // Child process 1
        Countother();
        return 0;
    }
    else if (pid1<0)
    {
        perror ("Fork");
        exit(EXIT_FAILURE);
    }


    struct timespec start2, finish2;
    
    double elapsed2;
    clock_gettime(CLOCK_REALTIME, &start2);
    pid2 = fork();
    if (pid2 == 0) {
        // Child process 2
        CountRR(pid2);
        return 0;
    }
    else if (pid2<0)
    {
        perror ("Fork");
        exit(EXIT_FAILURE);
    }
	
    struct timespec start3, finish3;
    
    double elapsed3;
    clock_gettime(CLOCK_REALTIME, &start3);
    pid3 = fork();
    if (pid3 == 0) {
        // Child process 3
        CountFIFO(pid3);
        return 0;
    }
    else if (pid3<0)
    {
        perror ("Fork");
        exit(EXIT_FAILURE);
    }

    // Parent process
    int status;
    waitpid(pid1, &status, 0);
    clock_gettime(CLOCK_REALTIME, &finish1);
    elapsed1 = (finish1.tv_sec - start1.tv_sec);
    elapsed1 += (finish1.tv_nsec - start1.tv_nsec) / 1000000000.0;
    printf("OTHER: %lf\n", (double)elapsed1);
    
    waitpid(pid2, &status, 0);
    clock_gettime(CLOCK_REALTIME, &finish2);
    elapsed2 = (finish2.tv_sec - start2.tv_sec);
    elapsed2 += (finish2.tv_nsec - start2.tv_nsec) / 1000000000.0;
    printf("RR: %lf\n", (double)elapsed2);
    
    waitpid(pid3, &status, 0);
    clock_gettime(CLOCK_REALTIME, &finish3);
    elapsed3 = (finish3.tv_sec - start3.tv_sec);
    elapsed3 += (finish3.tv_nsec - start3.tv_nsec) / 1000000000.0;
    printf("FIFO: %lf\n", (double)elapsed3);

    return 0;
}
