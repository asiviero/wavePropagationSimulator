/*
 * auxFunctions.c
 *
 *  Created on: Apr 5, 2012
 *      Author: andre
 */

#include "../../wavePropagationSimulator.h"

float waveSpeed(int I,float time) {
	return 1.25;
}

void generateBVector(structMatrix bVector, CSR_Matrix csrm) {
	if(bVector->m_rows != csrm->m_rows) {
		printf("Illegal generateBVector call, unmatching matrixes. Aborting...\n");
		exit(3);
	}
	resetMatrix(bVector);
	int inRow,count=0;
	for(int i=0; i < csrm->m_rows; i++) {
		inRow = csrm->in_rowVector[i+1] - csrm->in_rowVector[i];
		for(int j=0; j < inRow; j++) {
			bVector->matrix[i][0] += csrm->fValuesVector[count];
			count++;
		}
	}
	printf("\n");
}
