/*
 * timeStep.c
 *
 *  Created on: Apr 5, 2012
 *      Author: andre
 */

#include "../../wavePropagationSimulator.h"

void loadUKP1(float **matrix,int dimension) {

	float fDelta[3];
	fDelta[X_AXIS] = MESH_HLENGTH/N_HNODES;
	fDelta[Y_AXIS] = MESH_VLENGTH/N_VNODES;

	// Reset matrix for security reasons
	resetMatrix(matrix);

	// Load Identity
	for(int i=0;i<dimension;i++) matrix[i][i] = 1;

	// Load indexes for inner nodes
	for(int i=1;i<(N_HNODES-1);i++) {
		for(int j=1;j<(N_VNODES-1);j++) {
			int t = i*N_HNODES+j;
			matrix[t][t] = (-1/(pow(fDelta[X_AXIS],2)) -1/(pow(fDelta[Y_AXIS],2)) + 2/(waveSpeed(t,0)*pow(DELTA_TIME,2)));
			matrix[t][t-1] = matrix[t][t+1] = 1/(2*pow(fDelta[X_AXIS],2));
			matrix[t][t-N_HNODES] = matrix[t][t+N_HNODES] = 1/(2*pow(fDelta[Y_AXIS],2));
		}
	}
}
