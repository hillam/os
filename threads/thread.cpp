#include <pthread.h>
#include <iostream>
using namespace std;

void * dosomething(void * info){
	int* j = (int*) info;
	for(int i(0);i<10;i++){
		cout << "thread " << *j << " running " << i << endl;
		sleep(1);
	}
}

int main(){
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	cout << "In main thread, creating new thread" << endl;
	pthread_t tid1;
	pthread_t tid2;
	int info1 = 1;
	int info2 = 2;
	//start running the thread
	pthread_create(&tid1, &attr, dosomething, &info1);
	pthread_create(&tid2, &attr, dosomething, &info2);
	cout << "new thread created..." << endl;
	cout << "waiting..." << endl;
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	cout << "thread is done" << endl;
}