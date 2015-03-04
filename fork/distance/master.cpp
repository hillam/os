#include "point_utils.h"
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

int forkChild(const int& id);

int main(){
	// maximum rng value
	const int max = 1000;
	point ref = {500,500};

	/*------------------------------------------------------------------------*/

	// init points randomly
	point all_points[500000];
	for(int i(0);i<499999;i++){
		all_points[i].x = rand() % max;
		all_points[i].y = rand() % max;
	}
	// init last (known) point
	all_points[499999].x = 5;
	all_points[499999].y = 5;

	/*------------------------------------------------------------------------*/

	// size of shared memory seg
    const int size = sizeof(setop);

    // initialize 100 shared memory segs
    int segment_ids[100];
    setop* data[100];
    for(int i(0);i<100;i++){
    	segment_ids[i] = shmget(IPC_PRIVATE, size, S_IRUSR | S_IWUSR);
    	data[i] = (setop*) shmat(segment_ids[i], NULL, 0);
    }

    /*------------------------------------------------------------------------*/

    // break all_points into subsets, and initialize all 100 pieces of 'data'
    setop subsets[100];
    for(int i(0);i<100;i++){
    	for(int j(i*5000);j<(i*5000)+5000;j++)
    		subsets[i].points[j] = all_points[j];
    	setop values;
	    values.num_points = 5000;
	    values.ref = ref;
	    memcpy(values.points,&subsets[i],sizeof(values.points));
	    *data[i] = values;
    }

    /*------------------------------------------------------------------------*/

    // fork children
	for(int i(0);i<100;i++)
		forkChild(segment_ids[i]);
	for(int i(0);i<100;i++)
		wait(NULL);

    for(int i(0);i<100;i++)
    	cout << data[i]->closest.x << " " << data[i]->closest.y << endl;
}

int forkChild(const int& id){
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
		sprintf(arg, "%d", id);
		execl("./child.o", "child.o", arg, NULL);
		cout << "Error calling execl" << endl;
		return -1;
	}
}