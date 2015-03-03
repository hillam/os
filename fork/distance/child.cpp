#include "point_utils.h"
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char ** argv){
	int segment_id  = atoi(argv[1]);
	int range = atoi(argv[2]);

	setop* data = (setop*) shmat(segment_id, NULL, 0);

	point ref = data->ref;
	cout << "Greetings from child.. ref point is " << ref.x << ref.y << endl;
	cout << "Greetings from child.. num_points: " << data->num_points << endl;

	closest(*data);
}