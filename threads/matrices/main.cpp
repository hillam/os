#include "Matrix.h"
#include "FileReader.h"
#include "StringFunctions.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

int main(){
	
	vector<string> temp;

	cout << "Reading in A.matrix and B.matrix.." << endl;

	FileReader a("A.matrix");
	vector<string> dim1 = StringFunctions::split(a.readLine()," ");
	Matrix m1(atoi(dim1[0].c_str()),atoi(dim1[1].c_str()));
	int a_rows[m1.getRows()][m1.getColumns()];

	for(int i(0);i<m1.getRows();i++){
		temp = StringFunctions::split(a.readLine(),", ");
		for(int j(0);j<m1.getColumns();j++){
			a_rows[i][j] = atoi(temp[j].c_str());
		}
		m1.addRow(a_rows[i]);
	}
	
	FileReader b("B.matrix");
	vector<string> dim2 = StringFunctions::split(b.readLine()," ");
	Matrix m2(atoi(dim2[0].c_str()),atoi(dim2[1].c_str()));
	int b_rows[m2.getRows()][m2.getColumns()];

	for(int i(0);i<m2.getRows();i++){
		temp = StringFunctions::split(b.readLine(),", ");
		for(int j(0);j<m2.getColumns();j++){
			b_rows[i][j] = atoi(temp[j].c_str());
		}
		m2.addRow(b_rows[i]);
	}

	cout << "Calculating C.matrix.." << endl;

	Matrix c = (m1*m2);	

	cout << "Writing C.matrix.." << endl;

	ofstream matrix_file;
	matrix_file.open("C.matrix");
	matrix_file << c << endl;
	matrix_file.close();
}