/*
 * boundaryConditions.c
 *
 *  Created on: Apr 27, 2012
 *      Author: andre
 */

#include "../../wavePropagationSimulator.h"
//"../testbench/wave2/wave2_0.m"
void loadExtVectorOnInitialTime(structMatrix *extV,char *sourceFile) {
	FILE *sourceWaveFileP = fopen(sourceFile,"r");
	printf("%s\n",sourceFile);
	fseek(sourceWaveFileP,5,SEEK_SET);
	for(int i=0; i< N_HNODES; i++) {
		for(int j=0; j< N_VNODES; j++) {
			fscanf(sourceWaveFileP,"%f",&extV[0]->matrix[i*N_VNODES+j][0]);
		}
		fseek(sourceWaveFileP,2,SEEK_CUR);
	}
	fclose(sourceWaveFileP);

}
