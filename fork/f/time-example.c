#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
using namespace std;

double timedif(struct timeval start, struct timeval end);

int main()
{
    struct timeval start;
    struct timeval end;
    
    gettimeofday(&start, NULL);

	pid_t pid = 0;
    pid = fork();

    if (pid < 0)
    {
        cout << "Fork failed" << endl;
        return -1;
    }

    if(pid > 0)
    {
        int status = 0;
        wait(&status);
        cout << "Child done, here is what it wrote to file" << endl;
        
        ifstream input;
        input.open("output.txt");
        if (input.is_open())
        {
            double num;
            (input >> num).get();
            while (input.good())
            {   
                cout << num << endl;
                (input >> num).get();
            }
        }
        else 
        {
            cout << "file not found" << endl;
        }
        input.close();

    }
    else
    {
        execl("./hello.o", "hello.o", NULL);
        cout << "Error calling execl" << endl;
    }
	
    gettimeofday(&end, NULL);
    printf("running time = %f\n", timedif(start, end));
}

double timedif(struct timeval start, struct timeval end)
{
    float time1 = start.tv_sec * 1000000 + start.tv_usec;
    float time2 = end.tv_sec * 1000000 + end.tv_usec;
    return (time2 - time1) / 1000000;
}