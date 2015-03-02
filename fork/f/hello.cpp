#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using namespace std;

bool isPrime(int i);
bool isDivisibleBy (int a, int b);

int main(int argc,char * argv[])
{
    int segment_id  = atoi(argv[1]);
    vector<int>* pBuff = (vector<int>*) shmat(segment_id, NULL, 0);
    vector<int>* primes;

    for (int i = 0; i <= 10000; i++)
	{
    	if (isPrime(i) == true)
    	{
        	primes.push_back(i);
   	 	}
	}

    sprintf(pBuff,primes,getpid());
}

//Returns true if i is a prime number
bool isPrime(int i)
{
    bool ret = true;
    
    for (int j = 2; j < i; j++)
    {
        if (isDivisibleBy(i, j))
        {
            ret = false;
            break;
        }
    }
    return ret;
}

//Returns true if a is divisible by b
bool isDivisibleBy (int a, int b)
{
    return (a % b == 0);
}
