#ifndef CLOSEST_POINT_H
#define CLOSEST_POINT_H

const long TOTAL_POINTS = 50000;
const int TOTAL_CHILDREN = 100;

struct point{
	long x;
	long y;
};

//set of points
struct setop{
	int num_points;
	point ref;
	point points[TOTAL_POINTS/TOTAL_CHILDREN];
	point closest;
	double distance;
};

double dist(const point& p1, const point& p2);
void * calcClosest(void* s);

#endif