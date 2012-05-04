/*
 * CSR.h
 *
 *  Created on: Apr 14, 2012
 *      Author: andre
 */

#ifndef CSR_H_
#define CSR_H_

struct CSR_Matrix {
	float *fValuesVector;
	int *columnVector,*in_rowVector;
	int m_rows,m_columns;
	int dimension;
	int nonZeros;
};
typedef struct CSR_Matrix* CSR_Matrix;

CSR_Matrix initCSRMatrix();
void printCSRMatrix(CSR_Matrix csrm);
void destroyCSRMatrix(CSR_Matrix csrm);
structMatrix CSRmatrixMultiplicationByVector(CSR_Matrix csrm, structMatrix vector);


#endif /* CSR_H_ */
