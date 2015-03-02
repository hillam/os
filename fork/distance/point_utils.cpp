#include "point_utils.h"
#include <math.h>
#include <unistd.h>

double distance(point p1,point p2){
	return sqrt(((p1.x-p2.x)^2)+((p1.y-p2.y)^2));
}

point closest(setop& set){
	if(set.num_points > 0){
		point close = set.points[0];

		for(int i(0);i<set.num_points;i++)
			if(distance(set.ref,set.points[i]))
				close = set.points[i];

		return close;
	}
	
	point p = {0,0};
	return p;
}