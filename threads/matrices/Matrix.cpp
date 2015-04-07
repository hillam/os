#include "Matrix.h"
#include <iostream>
#include <pthread.h>

using namespace std;

struct row_col{
	Matrix * dest;
	int cell;
	int size;
	int * row;
	int * column;
};

void * calculateCell(void * data){
	row_col* rc = (row_col*) data;

	Matrix * result = rc->dest;
	int cell = rc->cell;
	int value(0);
	for(int i(0);i<rc->size;i++)
		value += rc->row[i] * rc->column[i];
	result->m_matrix[cell/result->columns][cell%result->columns] = value;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs){
	//if inner dimension is not equal, don't allow
	if(lhs.columns != rhs.rows){
		cout << "error, cannot perform dot product on these matrices" << endl;
		throw;
	}

	Matrix result(lhs.rows,rhs.columns);

	//declare data to send to threads
	int cells = lhs.rows * rhs.columns;
	row_col pairs[cells];

	//populate data to send to threads, and then start the threads
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t tids[cells];
	

	int temp_cols[cells][rhs.rows];
	for(int i(0);i<cells;i++){

		pairs[i].dest = &result;
		pairs[i].cell = i;
		pairs[i].size = lhs.columns;
		
		pairs[i].row = lhs.m_matrix[i/rhs.columns];

		for(int j(0);j<rhs.rows;j++){
			temp_cols[i][j] = rhs.m_matrix[j][i%rhs.columns];
		}
		pairs[i].column = temp_cols[i];

		//pthread_create(&tids[i],&attr,calculateCell,&pairs[i]);
		calculateCell(&pairs[i]);
	}

	printf("%s\n","test");
	//for(int i(0);i<cells;i++)
	//	pthread_join(tids[i], NULL);

	return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m){
	os << m.rows << " " << m.columns << endl;
	for(int i(0);i<m.rows;i++){
		for(int j(0);j<m.columns;j++){
			os << m.m_matrix[i][j];
			if(j != m.columns-1)
				os << ", ";
		}
		if(i != m.rows-1)
			os << endl;
	}
	return os;
}
