/*
 * matrix.c
 *
 *  Created on: Apr 5, 2012
 *      Author: andre
 */

/*void initMatrix(float **matrix, int dimension) {
	matrix = (float**)calloc(dimension,sizeof(float*));
	for(int i=0;i<dimension;i++) matrix[i] = (float*)calloc(dimension,sizeof(float));
}*/

#include "../../wavePropagationSimulator.h"

structMatrix initMatrix(int h_dimension, int v_dimension) {
	//float **matrix;
	structMatrix sM;
	sM = (structMatrix)malloc(sizeof(struct sM));
	sM->matrix = (float**)calloc(h_dimension,sizeof(float*));

	for(int i=0;i<h_dimension;i++) sM->matrix[i] = (float*)calloc(v_dimension,sizeof(float));

	//sM.matrix = matrix;
	sM->m_rows = h_dimension;
	sM->m_columns = v_dimension;
	//resetMatrix(sM);
	return sM;
}


void loadIdentityMatrix(structMatrix sM) {
	resetMatrix(sM);
	for(int i=0;i< (sM->m_rows);i++) sM->matrix[i][i] = 1;
}

void destroyMatrix(structMatrix smatrix) {
	for(int i=0; i<smatrix->m_columns; i++) free(smatrix->matrix[i]);
	free(smatrix->matrix);
	free(smatrix);
}

void resetMatrix(structMatrix sM) {
	bzero(*(sM->matrix),sizeof*(sM->matrix));
}

// This function performs m1*m2, returning the result. It also checks the validity of the operation
structMatrix matrixMultiplication(structMatrix m1, structMatrix m2) {
	// Check for validity of operation
	if(m1->m_columns != m2->m_rows) {
		printf("Invalid matrix multiplication. Aborting...\n");
		exit(2);
	}
	// Allocating the resulting matrix
	structMatrix result;
	result = initMatrix(m1->m_rows,m2->m_columns);
	for(int i=0; i < m1->m_rows ; i++) {
		for(int j=0; j < m2->m_rows ; j++) {
			for(int k = 0; k < m2->m_columns; k++) {
				result->matrix[i][k] += m1->matrix[i][j]*m2->matrix[j][k];
			}
		}
	}
	return result;
}

structMatrix matrixSum(structMatrix m1, structMatrix m2) {
	// Check for validity of operation
	if((m1->m_rows != m2->m_rows) || (m1->m_columns != m2->m_columns)) {
		printf("Invalid matrix sum. Aborting...\n");
		exit(2);
	}
	structMatrix result;
	result = initMatrix(m1->m_rows,m1->m_columns);

	for(int i=0; i< m1->m_rows; i++) {
		for(int j=0; j< m1->m_columns; j++) {
			result->matrix[i][j] = m1->matrix[i][j] + m2->matrix[i][j];
		}
	}

	return result;
}

void matrixTimesScalar(structMatrix m1,float scalar) {
	printf("\n--%f--\n",scalar);
	for(int i=0; i< m1->m_rows; i++) {
			for(int j=0; j< m1->m_columns; j++) {
				m1->matrix[i][j] *= scalar;
			}
		}
}

void printMatrix(structMatrix sM) {
	printf("Rows: %d, Columns: %d\n",sM->m_rows,sM->m_columns);
	for(int i=0;i < sM->m_rows;i++) {
		for(int j=0; j<sM->m_columns; j++) {
			printf("%.2f ",sM->matrix[i][j]);
		}
		printf("\n");
	}
}


