#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

#include <iostream>

using namespace std;

int loop();

int main()
{
	pid_t pid = 0;
	pid = fork();

	if (pid < 0)
	{
		cout << "Fork failed" << endl;
		return -1;
	}
	
	if (pid == 0)
	{
 		loop();
   	}
	else
	{
	
		pid = fork();

		if (pid < 0)
		{
			cout << "Fork failed" << endl;
			return -1;
		}
	
		if (pid == 0)
		{
	   		loop();
	   	}
	   	else
	   	{
			pid = fork();

			if (pid < 0)
			{
				cout << "Fork failed" << endl;
				return -1;
			}
	
			if (pid == 0)
			{
		   		loop();
		   	}
			else
			{
				cout << "All forks have been executed, parent exiting..." 
					 << endl;
			}
		}
	}
	return 0;
}

int loop()
{
	for (int sec = 0; sec < 10; sec++)
	{
		cout << "greetings from pid " << getpid() << endl;
		sleep(1);
	}
}
