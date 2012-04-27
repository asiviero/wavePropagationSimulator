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

	// Initiate the CSR Matrix which stands as the coefficients matrix to the linear system
	CSR_Matrix CSRM_UKP1;
	CSRM_UKP1 = initCSRMatrix(intNTotalNodes);

	// TODO UKP1 functions must be changed to include time variance
	loadUKP1CSR(CSRM_UKP1);

	// Generating the Grid. This function uses the constants set in constants.h to do it
	generateGridToFile("mesh.m");

	// These functions generate series of wavefields, they should be uncommented on further tests
	//generateWaveBenchmark("wave1.m",wave1);
	//generateWaveBenchmarkTimeVariant("wave2","wave2",wave2);


	// Trying to establish time variance for u
	//
	// Now u must be a vector of extended vectors, since every "row" in u corresponds to a time step
	// An extended vector is a matrix shaped to store every node with a special mapping scheme, in which
	// they're stored line by line.

	// Initiating uVectorTimeVariant
	structMatrix *uVectorTimeVariant;
	uVectorTimeVariant = (structMatrix*) calloc(N_TIME_STEPS,sizeof(structMatrix));
	for(int i = 0; i < N_TIME_STEPS; i++) uVectorTimeVariant[i] = initMatrix(intNTotalNodes,1);

	// u_0 is a prescript value, since we know how the wave behaves when it starts propagating
	// Its initial values shall be stored in the testbench folder, for whatever wave used
	// In this initial test, we will use the "wave2", for its the one that already has time variance
	loadExtVectorOnInitialTime(uVectorTimeVariant,"../testbench/wave2/wave2_0.m");

	// TODO Next step: calculate u_1 via u_0

	// Memory Freeing
	destroyCSRMatrix(CSRM_UKP1);

	for(int i = 0; i < N_TIME_STEPS; i++) destroyMatrix(uVectorTimeVariant[i]);
	free(uVectorTimeVariant);
}


