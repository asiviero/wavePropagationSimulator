/*
 * CSR.c
 *
 *  Created on: Apr 14, 2012
 *      Author: andre
 */
#include "../../wavePropagationSimulator.h"



CSR_Matrix initCSRMatrix(int dimension) {

	int nonZeros,nBoundary;
	nBoundary = 4*(sqrt(dimension)-1);
	nonZeros = nBoundary+5*(dimension-nBoundary);

	CSR_Matrix csrm;
	csrm = (CSR_Matrix)malloc(sizeof(struct CSR_Matrix));
	csrm->fValuesVector = (float*)calloc(nonZeros,sizeof(float));
	csrm->columnVector = (int*)calloc(nonZeros,sizeof(int));
	csrm->in_rowVector = (int*)calloc(dimension+1,sizeof(int));

	csrm->m_rows = csrm->m_columns = dimension;
	csrm->dimension = dimension;
	csrm->nonZeros = nonZeros;
	return csrm;
}

void printCSRMatrix(CSR_Matrix csrm) {
	for(int i=0; i< csrm->nonZeros; i++) printf("%.2f ",csrm->fValuesVector[i]);
	printf("\n");
	for(int i=0; i< csrm->nonZeros; i++) printf("%d ",csrm->columnVector[i]);
	printf("\n");
	for(int i=0; i< csrm->dimension; i++) printf("%d ",csrm->in_rowVector[i]);
	printf("\n");
}

void destroyCSRMatrix(CSR_Matrix csrm) {
	free(csrm->columnVector); free(csrm->in_rowVector); free(csrm->fValuesVector);
	free(csrm);
	csrm = NULL;
}

structMatrix CSRmatrixMultiplicationByVector(CSR_Matrix csrm, structMatrix vector) {
	// initing the resulting vector
	// it has the same row-size as the parameter matrix and 1 column
	structMatrix resultVector;
	resultVector = initMatrix(csrm->dimension,1);

	int currentIndex=0;
	int line_number;
	// First loop must run for dimension times
	for(int i=0;i<csrm->dimension;i++) {
		//verify how many nonzeros elements the i-th has
		int nonZerosOnith = csrm->in_rowVector[i+1] - csrm->in_rowVector[i];
		// in this quantity, perform the multiplication element by element, result is then cast to resultVector
		for(int j=0; j<nonZerosOnith; j++) {
			line_number = csrm->columnVector[currentIndex];
			resultVector->matrix[i][0] += csrm->fValuesVector[currentIndex]*vector->matrix[line_number][0];
			currentIndex++;
		}
	}
	return resultVector;
}
