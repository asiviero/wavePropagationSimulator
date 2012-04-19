/*
 * main.c
 *
 *  Created on: Apr 5, 2012
 *      Author: andre
 */

#include "wavePropagationSimulator.h"

void debug() {
	printf("passei\n");
}

int main(int argc, char **argv) {

	int intNTotalNodes = N_HNODES*N_VNODES;

	// Initializing matrix for instant K, in order to calculate u(k+1) nodes
	structMatrix matrixP;
	//matrixUKP1 = initMatrix(intNTotalNodes,intNTotalNodes);
	matrixP = initMatrix(intNTotalNodes,intNTotalNodes);

	// Load the "A" matrix for the linear system on time step K
	loadUKP1(matrixP);

	//printMatrix(matrixP);

	destroyMatrix(matrixP);

	// CSR tests
	CSR_Matrix csrm;
	//printf("intNTotalNodes: %d\n",intNTotalNodes);
	csrm = initCSRMatrix(intNTotalNodes);

	loadUKP1CSR(csrm);
	//printCSRMatrix(csrm);

	structMatrix testVector,testResult;
	testVector = initMatrix(intNTotalNodes,1);
	for(int i=0; i< intNTotalNodes; i++) testVector->matrix[i][0]=1;

	//printMatrix(testVector);
	testResult = CSRmatrixMultiplicationByVector(csrm,testVector);

	//printMatrix(testResult);
	destroyCSRMatrix(csrm);

	destroyMatrix(testVector);
	destroyMatrix(testResult);

	generateGridToFile("mesh.m");

	generateWaveBenchmark("wave1.m",wave1);

}


