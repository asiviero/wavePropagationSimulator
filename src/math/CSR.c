/*
 * CSR.c
 *
 *  Created on: Apr 14, 2012
 *      Author: andre
 */
#include "../../wavePropagationSimulator.h"



CSR_Matrix initCSRMatrix(int dimension) {

	int nonZeros,nBoundary;
	nBoundary = 4*(sqrt(dimension)-1);
	nonZeros = nBoundary+5*(dimension-nBoundary);

	CSR_Matrix csrm;
	csrm = (CSR_Matrix)malloc(sizeof(struct CSR_Matrix));
	csrm->CSRVector[VALUES] = (float*)calloc(nonZeros,sizeof(float));
	csrm->CSRVector[COLUMN] = (float*)calloc(nonZeros,sizeof(float));
	csrm->CSRVector[IN_ROW] = (float*)calloc(dimension+1,sizeof(float));

	csrm->m_rows = csrm->m_columns = sqrt(dimension);
	csrm->dimension = dimension;
	csrm->nonZeros = nonZeros;
	return csrm;
}

void printCSRMatrix(CSR_Matrix csrm) {
	for(int i=0; i< csrm->nonZeros; i++) printf("%d: %.2f | %.2f\n",i,csrm->CSRVector[VALUES][i],csrm->CSRVector[COLUMN][i]);
	printf("\n");
	/*for(int i=0; i< csrm->nonZeros; i++) printf("%.2f ",csrm->CSRVector[COLUMN][i]);
	printf("\n");*/
	for(int i=0; i< csrm->dimension; i++) printf("%.2f ",csrm->CSRVector[IN_ROW][i]);
	printf("\n");
}

void destroyCSRMatrix(CSR_Matrix csrm) {
	for(int i=0;i<3;i++) free(csrm->CSRVector[i]);
	free(csrm);
	csrm = NULL;
}
