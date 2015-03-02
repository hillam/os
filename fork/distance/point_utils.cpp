#include "point_utils.h"
#include <math.h>

double distance(point p1,point p2){
	return sqrt(((p1.x-p2.x)^2)+((p1.y-p2.y)^2));
}

void closest(setop& set){
	if(set.num_points > 0){
		point close = set.points[0];

		for(int i(0);i<set.num_points;i++)
			if(distance(set.ref,set.points[i]))
				close = set.points[i];

		set.closest = close;
	}
}