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
#include <climits>
#include <math.h>
#include <pthread.h>
#include <cstdint>

using namespace std;

// MAXimum rng value
const int MAX = 1000;

int main(int argc, char ** argv){
	srand(time(NULL));
	
	point ref = {50,51};
	cout << "Setting reference point at (" << ref.x << "," << ref.y << 
		")...." << endl;

	/*------------------------------------------------------------------------*/

	// init points randomly
	point all_points[TOTAL_POINTS];

	cout << "Generating " << TOTAL_POINTS << " random points (MAX value = " << 
		MAX << ")...." << endl;
	for(int i(0);i < TOTAL_POINTS;i++){
		point p = {rand() % MAX,rand() % MAX};
		all_points[i] = p;
	}

	// assign known point
	{
		point p = {ref.x,ref.y};
		all_points[0] = p;
	}

    /*------------------------------------------------------------------------*/

    // break all_points into subsets, and initialize all 100 pieces of 'data'
    setop* data[TOTAL_CHILDREN];
    for(int i(0);i<TOTAL_CHILDREN;i++)
    	data[i] = (setop*) new setop();

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
    	//printf("%d\n",i);
	    *data[i] = values;
    	//printf("test\n");
    }

    /*--------------------------------------------------------------------------

		THREAD STUFF

    --------------------------------------------------------------------------*/

    pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t tids[per_child];

	for(int i(0);i<per_child;i++)
		pthread_create(&tids[i],&attr,calcClosest,data[i]);
	for(int i(0);i<per_child;i++)
		pthread_join(tids[i], NULL);


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

	for(int i(0);i<TOTAL_CHILDREN;i++)
    	delete data[i];
}

double dist(const point& p1,const point& p2){
	return sqrt((pow(p1.x-p2.x,2))+(pow(p1.y-p2.y,2)));
}

void * calcClosest(void* s){
	setop* set = (setop*) s;
	set->closest = set->points[0];
	set->distance = dist(set->ref,set->closest);
	double d = INT_MAX;

	for(int i(0);i<set->num_points;i++){			
		d = dist(set->ref,set->points[i]);
		if(d < set->distance){
			set->closest.x = set->points[i].x;
			set->closest.y = set->points[i].y;
			set->distance = d;
		}
	}
}