#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
//#include <wait.h>

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

	if(pid == 0)
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
		cout << "Child is wrting to output.txt" << endl;
		ofstream output;
		output.open("output.txt");
		if (output.is_open())
		{
		    for (int i = 0; i < 10; i++)
		    {
		        output << i << endl;
		    }
		}
		else 
		{
		    cout << "can't open file" << endl;
		}
		output.close();
   	}

	return 0;
}
