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

void init_points(point* all_points);

// MAXimum rng value
const int MAX = 10000;

int main(int argc, char ** argv){
	point ref = {50,50};
	cout << "Setting reference point at (" << ref.x << "," << ref.y << 
		")...." << endl;

	/*------------------------------------------------------------------------*/

	// init points randomly
	point all_points[TOTAL_POINTS];
	srand(time(NULL));

	init_points(all_points);
	// assign known point
	{
		point p = {ref.x,ref.y};
		all_points[0] = p;
	}

    /*------------------------------------------------------------------------*/

    // break all_points into subsets, and initialize all 100 pieces of 'data'
    setop* data[TOTAL_CHILDREN];

    setop subsets[TOTAL_CHILDREN];
    int per_child = TOTAL_POINTS/TOTAL_CHILDREN;

    cout << "Populating shared data...." << endl;
    for(int i(0);i<TOTAL_CHILDREN;i++){
    	//cout << i*5000 << " -> " << (i*5000)+5000 << endl;

    	// for subset[i], initialize all points]
    	for(int j(i*per_child);j<((i*per_child)+per_child);j++){
    		//printf("%d %d\n",i,j);
    		subsets[i].points[j % per_child].x = all_points[j].x;
    		subsets[i].points[j % per_child].y = all_points[j].y;
    	}
    	setop values;
	    values.num_points = per_child;
	    values.ref = ref;
	    
	    // use this instead of memcpy
	    for(int j(0);j<per_child;j++){
    		//printf("%d\n",j);
	    	values.points[j] = subsets[i].points[j];
	    }
    	printf("%d\n",i);
	    *data[i] = values;
    	printf("test\n");
    }

    /*------------------------------------------------------------------------*/

	// print closest points (for debugging)
	// pass command line -l
	if(argc > 1 && argv[1] == string("-l")){
		cout << TOTAL_CHILDREN << " closest points returned by "<< TOTAL_CHILDREN 
			<<" children:" << endl << "x\ty\tdistance" << endl << 
			"---------------------------" << endl;
		for(int i(0);i<TOTAL_CHILDREN;i++)
			cout << data[i]->closest.x << "\t" << data[i]->closest.y << 
				"\t" << data[i]->distance << endl;
	}
	else
		cout << "Use command line option -l to show the " << TOTAL_CHILDREN
			<< " closest points." << endl;

    point close;
    close.x = data[0]->closest.x;
    close.y = data[0]->closest.y;

    for(int i(0);i<TOTAL_CHILDREN;i++){
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

void init_points(point* all_points){
	cout << "Generating " << TOTAL_POINTS << " random points (MAX value = " << 
		MAX << ")...." << endl;
	for(int i(0);i < TOTAL_POINTS;i++){
		point p = {rand() % MAX,rand() % MAX};
		all_points[i] = p;
	}
}
