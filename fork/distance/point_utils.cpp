#include "point_utils.h"
#include <math.h>
#include <unistd.h>
#include <climits>
#include <iostream>

double distance(point p1,point p2){
	return sqrt((pow(p1.x-p2.x,2))+(pow(p1.y-p2.y,2)));
}

void closest(setop& set){
	if(set.num_points > 0){
		set.closest = set.points[0];
		set.distance = distance(set.ref,set.closest);
		int d = INT_MAX;

		for(int i(0);i<set.num_points;i++){			
			d = distance(set.ref,set.points[i]);
			if(d < set.distance){
				set.closest = set.points[i];
				set.distance = d;
			}
		}
	}
}