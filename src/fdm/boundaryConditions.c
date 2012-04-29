/*
 * boundaryConditions.c
 *
 *  Created on: Apr 27, 2012
 *      Author: andre
 */

#include "../../wavePropagationSimulator.h"

void loadExtVectorOnInitialTime(structMatrix **extV,char *sourceFile) {
	FILE *sourceWaveFileP = fopen(sourceFile,"r");
	printf("%s\n",sourceFile);
	fseek(sourceWaveFileP,5,SEEK_SET);
	for(int i=0; i< N_HNODES; i++) {
		for(int j=0; j< N_VNODES; j++) {
			fscanf(sourceWaveFileP,"%f",&extV[0][0]->matrix[i*N_VNODES+j][0]);
		}
		fseek(sourceWaveFileP,2,SEEK_CUR);
	}
	fseek(sourceWaveFileP,8,SEEK_CUR);
	for(int i=0; i< N_HNODES; i++) {
		for(int j=0; j< N_VNODES; j++) {
			fscanf(sourceWaveFileP,"%f",&extV[0][1]->matrix[i*N_VNODES+j][0]);
		}
		fseek(sourceWaveFileP,2,SEEK_CUR);
	}
	fclose(sourceWaveFileP);

}

structMatrix *loadExtVectorTimeDerivative(void (*waveFunction)(structMatrix,structMatrix,structMatrix,structMatrix)) {
	structMatrix *v_0;
	v_0 = (structMatrix*) calloc(2,sizeof(structMatrix));
	for(int i=0; i < 2; i++) {
		v_0[i] = initMatrix(N_HNODES,N_VNODES);

	}
	// Initiating mesh
	structMatrix mesh_hmatrix,mesh_vmatrix;
	mesh_hmatrix = initMatrix(N_HNODES,N_VNODES);
	mesh_vmatrix = initMatrix(N_HNODES,N_VNODES);
	loadMesh(mesh_hmatrix,mesh_vmatrix);

	waveFunction(mesh_hmatrix,mesh_vmatrix,v_0[0],v_0[1]);

	destroyMatrix(mesh_hmatrix);
	destroyMatrix(mesh_vmatrix);
	return v_0;
}
