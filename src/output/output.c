/*
 * output.c
 *
 *  Created on: 19/04/2012
 *      Author: andre
 *
 */
#include "../../wavePropagationSimulator.h"

/*void generateWaveBenchmark(char *destinyFileName,void (*waveFunction)(structMatrix,structMatrix,structMatrix,structMatrix)) {
	/*
	 *	Initiating the mesh
	 *

	structMatrix mesh_hmatrix,mesh_vmatrix,u_matrix,v_matrix;
	structMatrix u_matrix_timeV[N_TIME_STEPS],v_matrix_timeV[N_TIME_STEPS];
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
}*/

void generateWaveBenchmarkTimeVariant(char *destinyFileName,char *folderName,void (*waveFunction)(structMatrix,structMatrix,structMatrix*,structMatrix*)) {
	/*
	 *	Initiating the mesh
	 */

	structMatrix mesh_hmatrix,mesh_vmatrix;
	structMatrix u_matrix_timeV[N_TIME_STEPS],v_matrix_timeV[N_TIME_STEPS];

	// Initiating mesh
	mesh_hmatrix = initMatrix(N_HNODES,N_VNODES);
	mesh_vmatrix = initMatrix(N_HNODES,N_VNODES);
	loadMesh(mesh_hmatrix,mesh_vmatrix);

	char path[N_TIME_STEPS][MAX_FILENAME_LENGTH];
	generateFileNames(path,destinyFileName,folderName);



	for(int i=0; i< N_TIME_STEPS; i++) {
		//printf("path[%d]: %s\n",i,path[i]);
		// Initializing u and v matrixes
		u_matrix_timeV[i] = initMatrix(N_HNODES,N_VNODES);
		v_matrix_timeV[i] = initMatrix(N_HNODES,N_VNODES);
	}


	// Calculations are handled via callback
	// This function must calculate for every time-step!
	waveFunction(mesh_hmatrix,mesh_vmatrix,u_matrix_timeV,v_matrix_timeV);


	// Printing matrixes to files
	for(int i=0; i< N_TIME_STEPS; i++) {
		char indexu[4],indexv[4],quiverexp[30];
		sprintf(indexu,"u%d",i);
		sprintf(indexv,"v%d",i);
		sprintf(quiverexp,"quiver(x,y,%s,%s)\n",indexu,indexv);
		printMatrixToFile(u_matrix_timeV[i],path[i],indexu);
		printMatrixToFile(v_matrix_timeV[i],path[i],indexv);
		printMatrixToFile(mesh_hmatrix,path[i],"x");
		printMatrixToFile(mesh_vmatrix,path[i],"y");
		// At the end, print the "quiver" function
		FILE *destinyFile = fopen(path[i],"a");
		fprintf(destinyFile,"%s",quiverexp);
		fclose(destinyFile);
	}

	// Memory freeing
	for(int i=0; i< N_TIME_STEPS; i++) {
		destroyMatrix(u_matrix_timeV[i]);
		destroyMatrix(v_matrix_timeV[i]);
	}
	destroyMatrix(mesh_hmatrix);
	destroyMatrix(mesh_vmatrix);

	// Generate the plotter script
	char plotterName[MAX_FILENAME_LENGTH];
	FILE *plotter;
	strcpy(plotterName,"../testbench/");
	strcat(plotterName,folderName);
	strcat(plotterName,"/");
	strcat(plotterName,destinyFileName);
	strcat(plotterName,"_plotter.m");
	plotter = fopen(plotterName,"w");

		for(int i=0; i< N_TIME_STEPS; i++ ) {
			fprintf(plotter,"%s_%d \nprint -djpg %s_%d.jpg\n",destinyFileName,i,destinyFileName,i);
		}

	fclose(plotter);
}

void generateFileNames(char path_matrix[][MAX_FILENAME_LENGTH], char *destinyFileName, char *folderName) {
	for(int i=0; i< N_TIME_STEPS; i++) {
			strcpy(path_matrix[i],"../testbench/");
			strcat(path_matrix[i],folderName);
			strcat(path_matrix[i],"/");
			strcat(path_matrix[i],destinyFileName);
			char *tmp = (char*)calloc(10,sizeof(char));
			sprintf(tmp,"_%d.m",i);
			strcat(path_matrix[i],tmp);
			free(tmp);
		}
}

void exportWaveFieldToFile(structMatrix h_field,structMatrix v_field,int timeStep, char *destinyFile, char *folderName) {
	/*
		 *	Initiating the mesh
		 */

		structMatrix mesh_hmatrix,mesh_vmatrix;
		structMatrix u_matrix_timeV[N_TIME_STEPS],v_matrix_timeV[N_TIME_STEPS];

		// Initiating mesh
		mesh_hmatrix = initMatrix(N_HNODES,N_VNODES);
		mesh_vmatrix = initMatrix(N_HNODES,N_VNODES);
		loadMesh(mesh_hmatrix,mesh_vmatrix);

		char path[50] = "../testbench/";
		strcat(path,folderName);
		strcat(path,"/");
		strcat(path,destinyFile);
		char indexu[4],indexv[4],quiverexp[30],time_index[2];
		sprintf(time_index,"%d",timeStep);
		strcat(path,"_");
		strcat(path,time_index);
		strcat(path,"_c.m");


		sprintf(indexu,"u%d",timeStep);
		sprintf(indexv,"v%d",timeStep);
		sprintf(quiverexp,"quiver(x,y,%s,%s)\n",indexu,indexv);
		printMatrixToFile(h_field,path,indexu);
		printMatrixToFile(v_field,path,indexv);
		printMatrixToFile(mesh_hmatrix,path,"x");
		printMatrixToFile(mesh_vmatrix,path,"y");
		// At the end, print the "quiver" function
		FILE *destinyFileP = fopen(path,"a");
		fprintf(destinyFileP,"%s",quiverexp);
		fclose(destinyFileP);


		// Generate the plotter script
		char plotterName[MAX_FILENAME_LENGTH];
		FILE *plotter;
		strcpy(plotterName,"../testbench/");
		strcat(plotterName,folderName);
		strcat(plotterName,"/");
		strcat(plotterName,destinyFile);
		strcat(plotterName,"_c_plotter.m");
		plotter = fopen(plotterName,"w");
		for(int i=0; i< N_TIME_STEPS; i++ ) {
			fprintf(plotter,"%s_%d_c \nprint -djpg %s_%d_c.jpg\n",destinyFile,i,destinyFile,i);
		}
		fclose(plotter);


		// Memory Freeing
		destroyMatrix(mesh_hmatrix);
		destroyMatrix(mesh_vmatrix);
}
