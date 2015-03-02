#ifndef CLOSEST_POINT_H
#define CLOSEST_POINT_H

struct point{
	int x;
	int y;
};

//set of points
struct setop{
	int num_points;
	point ref;
	point points[];
};

double distance(point p1, point p2);
point closest(setop& set);

#endif