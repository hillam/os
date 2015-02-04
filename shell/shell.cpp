#include <iostream>
#include <syscall.h>
#include <dirent.h>
#include <sys/stat.h> 
using namespace std;

void list(){
	DIR *dp;
  	struct dirent *dirp;
  	dp = opendir(".");
	if ( dp == NULL)
	{
		cout << "error opening current directory" << endl;
	}
	else
	{
		dirp = readdir(dp);
		struct stat fileStat;
		while (dirp != NULL)
		{
			stat(dirp->d_name, &fileStat);
			if (string(dirp->d_name) != "." && string(dirp->d_name) != "..")
			{
				if(S_ISDIR(fileStat.st_mode))
			    	cout << "\t(d) " << dirp->d_name << endl;
			    else
					cout << "\t(f) " << dirp->d_name << endl;
			}
			dirp = readdir(dp);
		}
	}
	closedir(dp);
}

void down(string str){
	int index = 0;
	if(str[1] == ' ')
		index = 2;
	else 
		index = 5;

	chdir(str.substr(index).c_str());
}

int main(){
	string inpt = "";
	bool active = true;

	cout << "Welcome to seashell!" << endl;
	while (active){
		cout << "seashell> ";
		getline(cin,inpt);
		if(inpt == "l" || inpt == "list"){
			list();
		}
		else if(inpt.substr(0,1) == "d" || inpt.substr(0,4) == "down"){
			down(inpt);
		}
		else if(inpt == "u" || inpt == "up"){
			chdir("..");
		}
		else if(inpt == "w" || inpt == "wai"){
			cout << get_current_dir_name() << endl;
		}
		else if(inpt == "e" || inpt == "exit"){
			cout << "kbye.." << endl;
			return 0;
		}
		else{
			cout << "\t(l)ist: lists contents of current directory" << endl;
			cout << "\t(d)own [dir]: moves into the specified child directory" << endl;
			cout << "\t(u)p: moves to the parent directory" << endl;
			cout << "\t(w)ai: prints the current directory" << endl;
			cout << "\t(e)xit: exits the shell" << endl;
			cout << "\t(h)elp: prints a list of the supported commands" << endl;
		}
	}
}