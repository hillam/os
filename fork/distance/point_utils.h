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
	point points[10];
	point closest;
	int distance;
};

double distance(point p1, point p2);
void closest(setop& set);

#endif