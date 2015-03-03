#include "point_utils.h"
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int forkChild(const int& id, const string& num);

int main(){
	int num = 10;

	int segment_ids[num/10];

	point ref = {0,0};
	point all_points[] = {{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},{10,10}};

	int segment_id = 0;
    const int size = sizeof(setop);
    
    segment_id = shmget(IPC_PRIVATE, size, S_IRUSR | S_IWUSR);
    setop* data = (setop*) shmat(segment_id, NULL, 0);

    setop values;
    values.num_points = num;
    values.ref = ref;
    memcpy(values.points,all_points,sizeof(values.points));

    *data = values;

	forkChild(segment_id,"1");
	wait(NULL);

    point close = data->closest;
    cout << close.x << " " << close.y << endl;
}

int forkChild(const int& id, const string& num){
	pid_t pid = 0;
	pid = fork();

	if (pid < 0)
	{
		cout << "Fork failed" << endl;
		return -1;
	}

	if (pid == 0)
	{
		char arg[10];
		sprintf(arg, "%d", id);
		execl("./child.o", "child.o", arg, num.c_str(), NULL);
		cout << "Error calling execl" << endl;
		return -1;
	}
}