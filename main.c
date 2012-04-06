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
	float **matrixUKP1;
	matrixUKP1 = (float**)calloc(intNTotalNodes,sizeof(float*));
	for(int i=0;i<intNTotalNodes;i++) matrixUKP1[i] = (float*)calloc(intNTotalNodes,sizeof(float));

	// Load the "A" matrix for the linear system on time step K
	loadUKP1(matrixUKP1,intNTotalNodes);

	// Debug prints are commented below
	/*for(int i=0;i<(N_HNODES);i++) {
		for(int j=0;j<N_VNODES;j++) printf("%2d ",i*N_HNODES+j);
		printf("\n");
	}
	printf("\n");


	for(int i=1;i<(N_HNODES-1);i++) {
		for(int j=1;j<(N_VNODES-1);j++) printf("%2d ",i*N_HNODES+j);
		printf("\n");
	}
	printf("\n");

	int i,j;
	for(i=0;i<(intNTotalNodes);i++) {
		for(j=0;j<intNTotalNodes;j++) printf("%.1f ",matrixUKP1[i][j]);
		printf("\n");
	}
	printf("\n");
	*/

	// Memory Freeing
	destroyMatrix(matrixUKP1,intNTotalNodes);
}
