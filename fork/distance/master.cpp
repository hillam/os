#include "point_utils.h"
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

void forkChild(){

}

int main(){
	int num = 10;
	int size = sizeof(setop);

	int segment_ids[num/10];

	point ref = {0,0};
	point all_points[] = {
		{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},{10,10}
	};


	//point closest = closest();
}