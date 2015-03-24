#include <pthread.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int iglobal = 100;

struct Params
{
	int i1;
	int i2;
};

void * doSomething(void * info)
{
	Params * pI = (Params *)info;
	for (int i = 0; i < 10; i++)
	{
		iglobal = iglobal + 1;
		int sum = pI->i1 + pI->i2;
		cout << "thread calculated " << sum << endl; 
		cout << "iglobal = " << iglobal << endl;
		sleep(1);
	}
}

int main()
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	cout << "in main thread, creating new thread" << endl;
	pthread_t tid1;
	pthread_t tid2;
	Params info1;
	info1.i1 = 10;
	info1.i2 = 20;
	Params info2;
	info2.i1 = 100;
	info2.i2 = 200;
	pthread_create(&tid1, &attr, doSomething, &info1);
	pthread_create(&tid2, &attr, doSomething, &info2);
	cout << "new thread created..." << endl;
	cout << "waiting for thread to end" << endl;
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	cout << "ok, thread is done!" << endl;
}