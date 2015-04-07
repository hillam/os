/*------------------------------------------------------------------------------
Distance between points x1,y1 and x2,y2:
sqrt((x1-x2)^2 + (y1-y2)^2)

For 1000 pts, controller spawns 10 child processes
which check 100 points each

Each child takes a range, the reference point, and the set of pts
Returns closest point

Controller chooses between 10 closest all_points
------------------------------------------------------------------------------*/

//Controller has array of segment of ids
int segments[N];

//Controller has structure for pointers
struct point{
	int x;
	int y;
};
point closest_pts[N];

//Controller keeps track of a reference point, and set of all points
point ref_point;
point all_points[N];

struct xyz{
	int num_points;
	point ref;
	point points[N];
	point closest;
};

//init thing
xzy data:
	data.num_points=12;
	data.ref = myPoint;

//with a pointer, use -> to access members rather than .
xyz* p;
p->num_points = 10;

//returns number of bytes that the data type takes up
sizeof(int);

/*------------------------------------------------------------------------------

controller.cpp
controller.h
child.cpp
child.h

point_utils.cpp
point_utils.h

------------------------------------------------------------------------------*/