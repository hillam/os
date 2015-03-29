#include "Matrix.h"
#include "FileReader.h"
#include "StringFunctions.h"
#include <iostream>
#include <vector>

using namespace std;

int* toArray(string s){

}

int main(){
	/*Matrix m1(2,3);
	int data1[][3] = {{1,2,3},
					 {4,5,6}};
	m1.addRow(data1[0]);
	m1.addRow(data1[1]);
	cout << m1 << endl;

	Matrix m2(3,4);
	int data2[][4] = {{7,10,13,16},
					 {8,11,14,17},
					 {9,12,15,18}};
	m2.addRow(data2[0]);
	m2.addRow(data2[1]);
	m2.addRow(data2[2]);

	cout << m2 << endl;*/

	FileReader a("A.matrix");
	vector<string> dim1 = StringFunctions::split(a.readLine()," ");
	Matrix m1(atoi(dim1[0].c_str()),atoi(dim1[1].c_str()));
	
	FileReader b("B.matrix");
	vector<string> dim2 = StringFunctions::split(a.readLine()," ");
	Matrix m2(atoi(dim1[0].c_str()),atoi(dim2[1].c_str()));

	//cout << (m1*m2) << endl;
}