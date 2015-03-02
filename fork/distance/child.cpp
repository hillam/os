#include "point_utils.h"

using namespace std;

int main(int argc,char * argv[]){
	int segment_id  = atoi(argv[1]);
	int range = atoi(argv[2]);

	setop data = (setop*) shmat(segment_id, NULL, 0);

	
}