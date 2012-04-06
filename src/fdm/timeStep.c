/*
 * timeStep.c
 *
 *  Created on: Apr 5, 2012
 *      Author: andre
 */

#include "../../wavePropagationSimulator.h"

void loadUKP1(structMatrix sM) {

	float fDelta[3];
	fDelta[X_AXIS] = MESH_HLENGTH/N_HNODES;
	fDelta[Y_AXIS] = MESH_VLENGTH/N_VNODES;

	loadIdentityMatrix(sM);

	// Load indexes for inner nodes
	for(int i=1;i<(N_HNODES-1);i++) {
		for(int j=1;j<(N_VNODES-1);j++) {
			int t = i*N_HNODES+j;
			sM->matrix[t][t] = (-1/(pow(fDelta[X_AXIS],2)) -1/(pow(fDelta[Y_AXIS],2)) + 2/(waveSpeed(t,0)*pow(DELTA_TIME,2)));
			sM->matrix[t][t-1] = sM->matrix[t][t+1] = 1/(2*pow(fDelta[X_AXIS],2));
			sM->matrix[t][t-N_HNODES] = sM->matrix[t][t+N_HNODES] = 1/(2*pow(fDelta[Y_AXIS],2));
		}
	}
}
