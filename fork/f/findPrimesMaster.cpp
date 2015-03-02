#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
using namespace std;

double timedif(struct timeval start, struct timeval end);

void forkChild(const string& num){
    pid_t pid = 0;
    pid = fork();

    if (pid < 0)
    {
        cout << "Fork failed" << endl;
    }
    if (pid == 0)
    {
        execl("./hello.o", "hello.o", num.c_str(),NULL);
        cout << "Error calling execl" << endl;
    }
}

int main()
{
    struct timeval start;
    struct timeval end;

    int segment_id = 0;
    vector<int>* pBuff = NULL;
    const int size = 4096;
    
    segment_id = shmget(IPC_PRIVATE, size, S_IRUSR | S_IWUSR);
    
    pBuff = (vector<int>*) shmat(segment_id, NULL, 0);
    
    printf("Parallel:\n");

    gettimeofday(&start, NULL);

    forkChild("1");
    
    gettimeofday(&end, NULL);
    printf("running time = %f\n", timedif(start, end));

    /*printf("\nSeries:\n");

    gettimeofday(&start, NULL);

    forkChild("1");
    wait(NULL);
    forkChild("2");
    wait(NULL);
    forkChild("3");
    wait(NULL);
    forkChild("4");
    wait(NULL);
    forkChild("5");
    wait(NULL);
    forkChild("6");
    wait(NULL);
    forkChild("7");
    wait(NULL);
    forkChild("8");
    wait(NULL);
    
    gettimeofday(&end, NULL);
    printf("running time = %f\n", timedif(start, end));*/
}

double timedif(struct timeval start, struct timeval end)
{
    float time1 = start.tv_sec * 1000000 + start.tv_usec;
    float time2 = end.tv_sec * 1000000 + end.tv_usec;
    return (time2 - time1) / 1000000;
}