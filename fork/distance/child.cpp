#include "point_utils.h"
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char ** argv){
	int segment_id  = atoi(argv[1]);

	setop* data = (setop*) shmat(segment_id, NULL, 0);

	closest(*data);
}