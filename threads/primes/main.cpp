#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

bool isPrime(int i);
bool isDivisibleBy (int a, int b);

struct limits{
	int start;
	int end;
};

void * findPrimes(void* index){
	limits* lim = (limits*) index;
	for (int i = lim->start; i <= lim->end; i++)
	{
    	if (isPrime(i) == true)
    	{
        	cout << i << endl;
   	 	}
	}
}

int main(){
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_t tid1;
	pthread_t tid2;
	limits info1;
	info1.start = 0;
	info1.end = 9999;
	limits info2;
	info2.start = 10000;
	info2.end = 19999;
	pthread_create(&tid1, &attr, findPrimes, &info1);
	pthread_create(&tid2, &attr, findPrimes, &info2);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	cout << "ok, thread is done!" << endl;
}

/*----------------------------------------------------------------------------*/

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