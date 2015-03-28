#include "Matrix.h"
#include <iostream>

using namespace std;

//dot product......... POSSIBLY not using this..
Matrix* operator*(const Matrix& lhs, const Matrix& rhs){
	//if inner dimension is not equal, don't allow
	if(lhs.columns != rhs.rows){
		cout << "error, cannot perform dot product on these matrices" << endl;
		return NULL;
	}

	
}

std::ostream& operator<<(std::ostream& os, const Matrix& m){
	os << m.rows << " " << m.columns;
	for(int i(0);i<m.rows;i++){
		for(int j(0);j<m.columns;j++){
			os << m.m_matrix[i][j];
			if(j != m.columns-1)
				os << ", ";
		}
	}
}