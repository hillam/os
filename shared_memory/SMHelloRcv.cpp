#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	int segment_id  = atoi(argv[1]);
	char * pBuff = (char *) shmat(segment_id, NULL, 0);
	cout << "Child: " << pBuff << endl;

	sprintf(pBuff, "Hello from child pid %d!", getpid());
	cout << "Child " << getpid() << " exiting" << endl;

	return 0;
}
