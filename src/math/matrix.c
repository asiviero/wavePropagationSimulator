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
	//printf("n columns: %d\n",smatrix->m_columns);
	for(int i=0; i<smatrix->m_rows; i++) free(smatrix->matrix[i]);
	free(smatrix->matrix);
	free(smatrix);
}

void resetMatrix(structMatrix sM) {
	for(int i=0; i< sM->m_rows; i++) {
			for(int j=0; j< sM->m_columns; j++) {
				sM->matrix[i][j] = 0;
			}
		}
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

// This function performs m1*m2, returning the result. It also checks the validity of the operation
void matrixMultiplicationDestined(structMatrix result, structMatrix m1, structMatrix m2) {
	// Check for validity of operation
	if(m1->m_columns != m2->m_rows) {
		printf("Invalid matrix multiplication. Aborting...\n");
		exit(2);
	}
	resetMatrix(result);
	for(int i=0; i < m1->m_rows ; i++) {
		for(int j=0; j < m2->m_rows ; j++) {
			for(int k = 0; k < m2->m_columns; k++) {
				result->matrix[i][k] += m1->matrix[i][j]*m2->matrix[j][k];
			}
		}
	}
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
	for(int i=0; i< m1->m_rows; i++) {
			for(int j=0; j< m1->m_columns; j++) {
				m1->matrix[i][j] *= scalar;
			}
		}
}

structMatrix tmpMatrixTimesScalar(structMatrix m1,float scalar) {
	structMatrix result;
	result = initMatrix(m1->m_rows,m1->m_columns);
	for(int i=0; i< m1->m_rows; i++) {
		for(int j=0; j< m1->m_columns; j++) {
			result->matrix[i][j] = scalar*m1->matrix[i][j];
		}
	}
	return result;
}

void printMatrix(structMatrix sM) {
	for(int i=0;i < sM->m_rows;i++) {
		for(int j=0; j<sM->m_columns; j++) {
			printf("%.2f ",sM->matrix[i][j]);
		}
		printf("\n");
	}
}

void printMatrixToFile(structMatrix sM,char *destinyFileName,char *matrixName) {
	FILE *destinyFile = fopen(destinyFileName,"a");
	fprintf(destinyFile,"%s = [",matrixName);
	for(int i=0;i < sM->m_rows;i++) {
		for(int j=0; j<sM->m_columns; j++) {
			fprintf(destinyFile,"%.2f ",sM->matrix[i][j]);
		}
		fprintf(destinyFile,";");
	}
	fprintf(destinyFile,"];\n");
	fclose(destinyFile);
}

// This function turns a n^2 vector into a n x n, in order to do calculations
// in this form
structMatrix extVectorToMatrix(structMatrix m1) {
	structMatrix result;
	int n =	sqrt(m1->m_rows);
	result = initMatrix(n,n);
	for(int i=0; i < n; i++) {
		for(int j=0; j < n; j++) {
			result->matrix[i][j] = m1->matrix[i*n+j][0];
		}
	}
	return result;
}

// This function does the opposite, turning a n x n matrix in a n^2 vector
structMatrix matrixToExtVector(structMatrix m1) {
	structMatrix result;
	int n =	m1->m_rows;
	result = initMatrix(n*n,1);
	for(int i=0; i < n; i++) {
		for(int j=0; j < n; j++) {
			result->matrix[i*n+j][0] = m1->matrix[i][j];
		}
	}
	return result;
}

structMatrix pointByPointProduct(structMatrix m1,structMatrix m2) {
	if((m1->m_rows == m2->m_rows) && (m1->m_columns == m2->m_columns) && (m1->m_columns==1)) {
		structMatrix result = initMatrix(m1->m_rows,1);
		for(int i=0; i<m1->m_rows ; i++) {
			result->matrix[i][0] = m1->matrix[i][0] * m2->matrix[i][0];
		}
		return result;
	}
	else {
		printf("Invalid point by point product call. Aborting...");
		exit(2);
	}
}

// This function adds "toBeAdded" into result, without need to allocate more resources
void matrixSumDestined(structMatrix result, structMatrix toBeAdded) {
	// check for validity of operation
	if((result->m_rows != toBeAdded->m_rows) && (result->m_columns != toBeAdded->m_columns)) {
		printf("Invalid matrix sum, aborting...\n");
		exit(2);
	}
	for(int i = 0; i < result->m_rows; i++) {
		for(int j = 0; j < result->m_columns; j++) {
			result->matrix[i][j] += toBeAdded->matrix[i][j];
		}
	}
}


void copyMatrix(structMatrix result,structMatrix sM) {
	if(result->m_rows != sM->m_rows || result->m_columns != sM->m_columns) {
		printf("Invalid matrix copy operation. Aborting...\n");
		exit(4);
	}

	for(int i=0; i< sM->m_rows; i++) {
		for(int j=0; j< sM->m_columns; j++) {
			result->matrix[i][j] = sM->matrix[i][j];
		}
	}
}

float maxVector(structMatrix extV) {
	float max = extV->matrix[0][0];
	int i,rows;
	rows = extV->m_rows;
	for(i=1;i< rows;i++) {
		if(extV->matrix[i][0]>max) max = extV->matrix[i][0];
	}
	return max;
}

void matrixSubtractionDestined(structMatrix result, structMatrix m1, structMatrix m2) {
	// check for validity of operation
	if((m1->m_rows != m2->m_rows) && (m1->m_columns != m2->m_columns) && (m1->m_rows != result->m_rows) && (m1->m_columns != result->m_columns)) {
		printf("Invalid matrix sum on MIPS format, aborting...\n");
		exit(2);
	}
	for(int i = 0; i < result->m_rows; i++) {
		for(int j = 0; j < result->m_columns; j++) {
			result->matrix[i][j] = m1->matrix[i][j] - m2->matrix[i][j];
		}
	}
}

void matrixSumDestinedMIPSFormat(structMatrix result, structMatrix m1, structMatrix m2) {
	// check for validity of operation
	if((m1->m_rows != m2->m_rows) && (m1->m_columns != m2->m_columns) && (m1->m_rows != result->m_rows) && (m1->m_columns != result->m_columns)) {
		printf("Invalid matrix sum on MIPS format, aborting...\n");
		exit(2);
	}
	for(int i = 0; i < result->m_rows; i++) {
		for(int j = 0; j < result->m_columns; j++) {
			result->matrix[i][j] = m1->matrix[i][j] + m2->matrix[i][j];
		}
	}
}








