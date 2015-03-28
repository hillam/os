#include "Matrix.h"
#include <iostream>

using namespace std;

int main(){
	Matrix m1(2,3);
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

	cout << m2 << endl;

	//Matrix m3(2,4);
	//m3 = m1*m2;

	cout << (m1*m2) << endl;
}