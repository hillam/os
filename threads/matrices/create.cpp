#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(){
	srand (time(NULL));
	int m = (rand() % 50) + 50;
	int k = (rand() % 50) + 50;
	int n = (rand() % 50) + 50;

	ofstream file;
	file.open("A.matrix");
	file << m << " " << k << endl;
	for(int i(0);i<m;i++){
		for(int j(0);j<k;j++){
			file << (rand() % 50) + 50;
			if(j != k-1)
				file << ", ";
		}
		file << endl;
	}
	file.close();

	file.open("B.matrix");
	file << k << " " << n << endl;
	for(int i(0);i<k;i++){
		for(int j(0);j<n;j++){
			file << (rand() % 50) + 50;
			if(j != n-1)
				file << ", ";
		}
		file << endl;
	}
	file.close();
}