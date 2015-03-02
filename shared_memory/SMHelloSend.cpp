#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <iostream>

using namespace std;

int main()
{
	int segment_id = 0;
	char * pBuff = NULL;
	const int size = 4096;
	
	segment_id = shmget(IPC_PRIVATE, size, S_IRUSR | S_IWUSR);
	
	pBuff = (char *) shmat(segment_id, NULL, 0);
	
	sprintf(pBuff, "Hello from parent pid %d!", getpid());
	
	pid_t pid = 0;
	pid = fork();

	if (pid < 0)
	{
		cout << "Fork failed" << endl;
		return -1;
	}

	if (pid == 0)
	{
		char arg[10];
		sprintf(arg, "%d", segment_id); 
		execl("./SMHelloRcv.o", "SMHelloRcv.o", arg, NULL);
		cout << "Error calling execl" << endl;
		return -1;
	}
	
	cout << "Parent waiting..." << endl;
	wait(NULL);

	cout << "Parent: " << pBuff << endl;
	cout << "Parent Exiting" << endl;
	
	shmdt(&segment_id);

	shmctl(segment_id, IPC_RMID, NULL);
	
	return 0;
}
