#include "point_utils.h"
#include <math.h>
#include <unistd.h>
#include <climits>
#include <iostream>

double distance(point p1,point p2){
	return sqrt(((p1.x-p2.x)^2)+((p1.y-p2.y)^2));
}

void closest(setop& set){
	std::cout << "num_points: " << set.points[1].x << std::endl;
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

		//for debugging
		point close = set.closest;
		std::cout << "Closest: " << close.x << " " << close.y << std::endl;
	}
}