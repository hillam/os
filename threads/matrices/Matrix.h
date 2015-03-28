#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix{
public:
	Matrix(int r,int c): rows(r),columns(c){
		m_matrix = new int*[r];
		for(int i(0);i<rows;i++)
			m_matrix[i] = new int[c];
	}
	~Matrix(){
		for(int i(0);i<rows;i++)
			delete[] m_matrix[i];
		delete[] m_matrix;
	}
	int getRows() const {return rows;}
	int getColumns() const {return columns;}

	friend Matrix* operator*(const Matrix& lhs, const Matrix& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

private:
	int rows;
	int columns;
	int** m_matrix;
};

#endif