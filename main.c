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

	loadUKP1CSR(CSRM_UKP1,0,waveSpeed);

	// Generating the Grid. This function uses the constants set in constants.h to do it
	generateGridToFile("mesh.m");

	// These functions generate series of wavefields, they should be uncommented on further tests
	//generateWaveBenchmark("wave1.m",wave1);
	generateWaveBenchmarkTimeVariant("wave2","wave2",wave2);


	// Trying to establish time variance for u
	//
	// Now u must be a vector of extended 2d-vectors, since every "row" in u corresponds to a time step
	// An extended vector is a matrix shaped to store every node with a special mapping scheme, in which
	// they're stored line by line.

	// Initiating uVectorTimeVariant
	structMatrix *uVectorTimeVariant[2];
	for(int i=0; i < 2; i++)	{
		uVectorTimeVariant[i] = (structMatrix*) calloc(N_TIME_STEPS,sizeof(structMatrix));
		for(int j = 0; j < N_TIME_STEPS; j++) uVectorTimeVariant[i][j] = initMatrix(intNTotalNodes,1);
	}


	// u_0 is a prescript value, since we know how the wave behaves when it starts propagating
	// Its initial values shall be stored in the testbench folder, for whatever wave used
	// In this initial test, we will use the "wave2", for its the one that already has time variance
	loadExtVectorOnInitialTime(uVectorTimeVariant,"../testbench/wave2/wave2_0.m");
	//printMatrix(uVectorTimeVariant[0][0]);
	//printMatrix(uVectorTimeVariant[0][1]);

	// Calculating u_1
	// u_1 is calculated via Taylor series, using both u_0, v_0 (u_0 derivative on time) - both of these are known
	// in advance - and the space derivatives on X and Y axis (this is easily extensible to a 3rd dimension), which
	// corresponds to the laplacian of u_0 and are calculated via Finite Differences. Once again, we use "wave2" as
	//a case test.
	// The Taylor series expression to u_1 is:

	// u_1 = u_0 + delta_time * v_0 + (delta_time^2/2) * (d^2 u/dx^2 + d^2 u/dy^2) * (waveSpeed(t=0)^2 * delta_time^2) / 2
	// u_0 is already done in uVectorTimeVariant[0]
	// v_0 is easily calculated:
	structMatrix *v_0_m,v_0[2],laplacian[2];
	v_0_m = loadExtVectorTimeDerivative(wave2TimeDerivative);
	laplacian[0] = initMatrix(intNTotalNodes,1);
	laplacian[1] = initMatrix(intNTotalNodes,1);

	float *boundaryVector;
	boundaryVector = calloc((2*(N_HNODES + N_VNODES -2)),sizeof(float));


	for(int i=0; i < 2; i++) {
		//matrixSumDestined(uVectorTimeVariant[i][1],uVectorTimeVariant[i][0]);

		v_0[i] = matrixToExtVector(v_0_m[i]);
		destroyMatrix(v_0_m[i]);


		matrixTimesScalar(v_0[i],DELTA_TIME);

		laplacianViaFD(laplacian[i],uVectorTimeVariant[i][1]);
		correctLaplacian(laplacian[i],0);

		// Now summing up the factors
		matrixSumDestined(uVectorTimeVariant[i][1],v_0[i]);
		matrixSumDestined(uVectorTimeVariant[i][1],laplacian[i]);

		// at the end, apply the boundary conditions on u_1
		generateBoundaryVectorFromFunction(boundaryVector,DELTA_TIME,i,wave2Returnable);
		//matrixTimesScalar(uVectorTimeVariant[i][1],0.5); // WHY
		applyBoundaryConditions(uVectorTimeVariant[i][1],boundaryVector);
	}

	// todo assemble the linear system
	int k=1;
	/*structMatrix vectorB,UKL1;
	structMatrix tmp_Multiplier;
	UKL1 = initMatrix(intNTotalNodes,intNTotalNodes);
	tmp_Multiplier = initMatrix(intNTotalNodes,1);
	vectorB = initMatrix(intNTotalNodes,1);

	copyMatrix(vectorB,uVectorTimeVariant[X_AXIS][k]);
	applyWaveSpeedTimeStepIntoMatrix(vectorB,DELTA_TIME,waveSpeed);

	loadUKL1(UKL1,(k-1)*DELTA_TIME,waveSpeed);
	matrixMultiplicationDestined(tmp_Multiplier,UKL1,uVectorTimeVariant[X_AXIS][k-1]);

	matrixSumDestined(vectorB,tmp_Multiplier);

	generateBoundaryVectorFromFunction(boundaryVector,(k+1)*DELTA_TIME,0,wave2Returnable);
	applyBoundaryConditions(vectorB,boundaryVector);


	// todo SOR method in CSR matrix


	printf("%d\n",uVectorTimeVariant[0][k+1]->m_columns);
	//sleep(1);
	CSR_SOR(uVectorTimeVariant[0][k+1],CSRM_UKP1,vectorB,1);*/


	printMatrix(uVectorTimeVariant[0][k]);
	printCSRMatrix(CSRM_UKP1);


	// Memory Freeing
	destroyCSRMatrix(CSRM_UKP1);
	/*destroyMatrix(vectorB);
	destroyMatrix(UKL1);
	destroyMatrix(tmp_Multiplier);
*/
	for (int i=0; i < 2; i++) {
		destroyMatrix(laplacian[i]);
		destroyMatrix(v_0[i]);
		for(int j = 0; j < N_TIME_STEPS; j++) destroyMatrix(uVectorTimeVariant[i][j]);
		free(uVectorTimeVariant[i]);
	}
	free(v_0_m);
	free(boundaryVector);
}


