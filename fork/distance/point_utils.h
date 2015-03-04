#ifndef CLOSEST_POINT_H
#define CLOSEST_POINT_H

struct point{
	long x;
	long y;
};

//set of points
struct setop{
	int num_points;
	point ref;
	point points[5000];
	point closest;
	double distance;
};

double dist(point p1, point p2);
void closest(setop& set);

#endif