/*
 * wave1.c
 *
 *  Created on: 19/04/2012
 *      Author: andre
 *
 *      This file computes the analyitical solution to
 *      E = 50*cos(10^9*t - 8*x) âx + 40*sin(10^9*t - 8*x) ây
 *
 *      in a mesh defined by the parameters on constants.h
 */
#include "../wavePropagationSimulator.h"

void generateWaveBenchmark(char *destinyFileName,void (*waveFunction)(structMatrix,structMatrix,structMatrix,structMatrix)) {
	/*
	 *	Initiating the mesh
	 */

	structMatrix mesh_hmatrix,mesh_vmatrix,u_matrix,v_matrix;
	// Initiating mesh
	mesh_hmatrix = initMatrix(N_HNODES,N_VNODES);
	mesh_vmatrix = initMatrix(N_HNODES,N_VNODES);
	loadMesh(mesh_hmatrix,mesh_vmatrix);

	char path[40] = "../testbench/";
	strcat(path,destinyFileName);

	printMatrixToFile(mesh_hmatrix,path,"x");
	printMatrixToFile(mesh_vmatrix,path,"y");

	// Initializing u and v matrixes
	u_matrix = initMatrix(N_HNODES,N_VNODES);
	v_matrix = initMatrix(N_HNODES,N_VNODES);

	// Calculations are handled via callback
	waveFunction(mesh_hmatrix,mesh_vmatrix,u_matrix,v_matrix);

	// Printing matrixes to file
	printMatrixToFile(u_matrix,path,"u");
	printMatrixToFile(v_matrix,path,"v");

	// At the end, print the "quiver" function
	FILE *destinyFile = fopen(path,"a");
	fprintf(destinyFile,"quiver(x,y,u,v)\n");
	fclose(destinyFile);

	// Memory freeing
	destroyMatrix(u_matrix);
	destroyMatrix(v_matrix);
	destroyMatrix(mesh_hmatrix);
	destroyMatrix(mesh_vmatrix);
}
