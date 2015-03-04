#include "point_utils.h"
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <ctime>

using namespace std;

int forkChild(const int& id);

int main(){
	// maximum rng value
	const int max = 100;
	srand(time(NULL));

	point ref = {8,8};

	/*------------------------------------------------------------------------*/

	// init points randomly
	point all_points[500000];
	for(int i(0);i<500000;i++){
		point p = {(rand() % max)+10,(rand() % max)+10};
		all_points[i] = p;
	}
	// init last (known) point
	{
		//point p = {80,80};
		//all_points[0] = p;
	}
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
    	//cout << i*5000 << " -> " << (i*5000)+5000 << endl;

    	// for subset[i], initialize all points
    	for(int j(i*5000);j<(i*5000)+5000;j++)
    		subsets[i].points[j] = all_points[j];
    	setop values;
	    values.num_points = 5000;
	    values.ref = ref;
	    memcpy(values.points,&subsets[i],sizeof(values.points));
	    
	    // does the same as memcpy (effectively)
	    //for(int j(0);j<5000;j++)
	    //	values.points[j] = subsets[i].points[j];
	    
	    *data[i] = values;
    }

    /*------------------------------------------------------------------------*/

    // fork children
	for(int i(0);i<100;i++)
		forkChild(segment_ids[i]);
	for(int i(0);i<100;i++)
		wait(NULL);

	// print closest 100 points (for debugging)
    //for(int i(0);i<100;i++)
    //	cout << data[i]->closest.x << " " << data[i]->closest.y << endl;

    point close;
    close.x = data[0]->closest.x;
    close.y = data[0]->closest.y;

    for(int i(0);i<100;i++){
    	point p;
    	p.x = data[i]->closest.x;
    	p.y = data[i]->closest.y;
    	if(dist(ref,p) < dist(ref,close)){
    		close.x = p.x;
    		close.y = p.y;
    	}
    }

    cout << "Closest point to reference point (" << ref.x << "," << ref.y << ") is ";
	cout << "(" << close.x << "," << close.y << ")" << endl;
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