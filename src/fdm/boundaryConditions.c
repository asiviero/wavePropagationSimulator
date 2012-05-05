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

void laplacianViaFD(structMatrix destiny, structMatrix extV) {
	// Check for extV
	if(extV->m_columns != 1) {
		printf("Laplacian matrix is not on extended vector format. Aborting... \n");
		exit(3);
	}
	resetMatrix(destiny);
	float dx,dy;
	dx = MESH_HLENGTH/N_HNODES;
	dy = MESH_VLENGTH/N_VNODES;
	// It's important to remember that the laplacian is only calculated in the inner nodes
	for(int i=1;i<(N_HNODES-1);i++) {
		for(int j=1;j<(N_VNODES-1);j++) {
			int t = i*N_HNODES+j;
			destiny->matrix[t][0] = (extV->matrix[t-1][0] - 2*extV->matrix[t][0] + extV->matrix[t+1][0]) / (pow(dx,2)) // X-Axis component
										+ (extV->matrix[t-N_HNODES][0] - 2*extV->matrix[t][0] + extV->matrix[t+N_HNODES][0]) / (pow(dy,2)); // Y-axis component
		}
	}
}

void correctLaplacian(structMatrix laplacian, float time) {
	for(int i=0; i<laplacian->m_rows; i++) {
		laplacian->matrix[i][0] *= pow(DELTA_TIME,2) * waveSpeed(i,time);
		laplacian->matrix[i][0] /= 2;
	}
}

void applyBoundaryConditions(structMatrix extV, float *boundaryVector) {
	int count=0;
	// lower nodes
	for(int i=0; i < N_HNODES ; i++) {
		extV->matrix[i][0] = boundaryVector[count];
		count++;
	}
	// side nodes
	int index;
	for(int i=0; i < N_VNODES-2; i++) {
		index = (i+1)*N_HNODES;
		extV->matrix[index][0] = boundaryVector[count];
		count++;
		index += N_HNODES-1;
		extV->matrix[index][0] = boundaryVector[count];
		count++;
	}
	// upper nodes
	for(int i=0; i < N_HNODES ; i++) {
		extV->matrix[(N_VNODES-1)*N_HNODES + i][0] = boundaryVector[count];
		count++;
	}
}

void generateBoundaryVectorFromFunction(float *boundaryVector,float time, float axis, float (*waveFunction)(int,float,float,float)) {
	float dx,dy;
	int count=0;
	dx = MESH_HLENGTH/N_HNODES;
	dy = MESH_VLENGTH/N_VNODES;
	float x_coordinate, y_coordinate;
	// lower nodes
	for(int i=0; i < N_HNODES ; i++) {
		x_coordinate = i*dx;
		y_coordinate = 0;
		boundaryVector[count] = waveFunction(axis,x_coordinate,y_coordinate,time);
		count++;
	}
	// side nodes
	for(int i=0; i < N_VNODES-2; i++) {
		x_coordinate = 0;
		y_coordinate = i*dy;
		boundaryVector[count] = waveFunction(axis,x_coordinate,y_coordinate,time);
		count++;
		x_coordinate = (N_HNODES-1)*dx;
		boundaryVector[count] = waveFunction(axis,x_coordinate,y_coordinate,time);
		count++;
	}
	// upper nodes
	for(int i=0; i < N_HNODES ; i++) {
		x_coordinate = i*dx;
		y_coordinate = (N_VNODES-1)*dy;
		boundaryVector[count] = waveFunction(axis,x_coordinate,y_coordinate,time);
		count++;
	}
}




