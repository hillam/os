#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(){
	//process identifier
	//clone this process in memory, and start running it at the same time
	pid_t pid(fork());
	//process that called fork() has pid = 0, child process has pid equal
	//to it's id
	if(pid == 0)
		cout << "I am a forker" << endl;
	else
		cout << "I got forked" << endl;

	cout << "Hello from " << getpid() << endl;
}