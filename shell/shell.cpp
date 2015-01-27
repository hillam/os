#include <iostream>
#include <syscall.h>
#include <dirent.h>
using namespace std;

int main(){
	string inpt = "";
	bool active = true;

	cout << "Welcome to seashell!" << endl;
	while (active){
		cout << "seashell> ";
		cin >> inpt;
		if(inpt == "l" || inpt == "list"){
			cout << "";
		}
		else if(inpt == "d" || inpt == "down"){
			cout << "";
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