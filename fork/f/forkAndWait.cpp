#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	pid_t pid = 0;
	pid = fork();

	if (pid < 0)
	{
		cout << "Fork failed" << endl;
		return -1;
	}

	if(pid > 0)
	{
		int status = 0;
		wait(&status);
		cout << "Child done, here is what it wrote to file" << endl;
		
	    ifstream input;
		input.open("output.txt");
		if (input.is_open())
		{
		    double num;
		    (input >> num).get();
		    while (input.good())
		    {   
		        cout << num << endl;
		        (input >> num).get();
		    }
		}
		else 
		{
		    cout << "file not found" << endl;
		}
		input.close();

	}
	else
	{
		execl("./hello.o", "hello.o", NULL);
		cout << "Error calling execl" << endl;
	}
	
	return 0;
}
