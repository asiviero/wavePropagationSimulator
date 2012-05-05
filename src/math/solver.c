/*
 * solver.c
 *
 *  Created on: May 5, 2012
 *      Author: andre
 *
 *      This file contains the codes for the linear system solvers and functions related to them
 */

#include "../../wavePropagationSimulator.h"
// An implementation to SOR method, taking in account that the coefficients matrix is sparse and is stored in CSR format

void CSR_SOR(structMatrix resultVector,CSR_Matrix CoefficientsMatrix, structMatrix extV_IndependentTerms, float floatWParameter) {
	int intNumberRows = CoefficientsMatrix->m_rows;
	printf("Number of Rows: %d %d\n",intNumberRows,extV_IndependentTerms->m_rows);

	// Ininting the vectors needed
	structMatrix currentX,previousX,differenceVector,mainDiagonal;
	currentX = initMatrix(intNumberRows,1);
	previousX = initMatrix(intNumberRows,1);
	differenceVector = initMatrix(intNumberRows,1);
	mainDiagonal = initMatrix(intNumberRows,1);

	long long int i,xlines,iter,j,count,k,current,line=0;
	i=j=0;

	float error=1;

	// Defining the elements on the main diagonal
	for (i = 0; i < intNumberRows; i++) {
		for (j = line; CoefficientsMatrix->columnVector[j] - 1 != i && j < CoefficientsMatrix->nonZeros; j++);
		mainDiagonal->matrix[i][0] = CoefficientsMatrix->fValuesVector[j];
		line += CoefficientsMatrix->in_rowVector[i + 1] - CoefficientsMatrix->in_rowVector[i];
	}

	// Reset iterators
	iter=j=count=current=0;
	printf("Number of Nonzeros: %d\n",CoefficientsMatrix->nonZeros);

	// Beggining Main Loop - KMAX and EMAX are constants defined in constants.h and mean,
	// respectively, the maximum number of iterations and the maximum error allowed
	for(iter=0; iter<KMAX && error>EMAX ; iter++) {
		current=0;
		for(i=0;i<intNumberRows;i++) {
			//printf("i: %d\n",i);
			currentX->matrix[i][0] = extV_IndependentTerms->matrix[i][0];

			// count variable stores the number of non zero elements in a row
			count = CoefficientsMatrix->in_rowVector[i+1] - CoefficientsMatrix->in_rowVector[i];

			// First Loop, corresponds to the already calculated values to X
			for(j=0; j<i && CoefficientsMatrix->columnVector[current] < i ; j++) {
				xlines = CoefficientsMatrix->columnVector[current]-1;

				currentX->matrix[i][0] -= CoefficientsMatrix->fValuesVector[current]*currentX->matrix[xlines][0];
				current++;
			}

			// Skips the element on the main diagonal

			current++;
			// Runs for the previous elements
			for(k=0;k<count-j-1;k++) {

				xlines = CoefficientsMatrix->columnVector[current]-1;
				currentX->matrix[i][0] -= CoefficientsMatrix->fValuesVector[current]*previousX->matrix[xlines][0];
				current++;

			}
			// Dividing by the maindiagonal coefficient
			currentX->matrix[i][0] /= mainDiagonal->matrix[i][0];

			// SOR Parameter
			currentX->matrix[i][0] = floatWParameter*currentX->matrix[i][0] + (1-floatWParameter)*previousX->matrix[i][0];
		}

		// Defining the difference Vector
		matrixSubtractionDestined(differenceVector,currentX,previousX);

		// Error calculation
		error = fabs(maxVector(differenceVector) / maxVector(currentX));

		// Copying previous X to current X
		copyMatrix(previousX,currentX);


	}
	printf("Iterations: %d, Error: %f\n",iter,error);
	copyMatrix(resultVector,currentX);
	// Memory freeing
	destroyMatrix(currentX);
	destroyMatrix(previousX);
	destroyMatrix(differenceVector);
	destroyMatrix(mainDiagonal);

}
