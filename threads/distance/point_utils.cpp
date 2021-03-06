#include "point_utils.h"
#include <math.h>
#include <unistd.h>
#include <climits>
#include <iostream>
#include <stdlib.h>

double dist(const point& p1,const point& p2){
	return sqrt((pow(p1.x-p2.x,2))+(pow(p1.y-p2.y,2)));
}

void * closest(void* s){
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