/*
 * CSR.h
 *
 *  Created on: Apr 14, 2012
 *      Author: andre
 */

#ifndef CSR_H_
#define CSR_H_

struct CSR_Matrix {
	float *CSRVector[3];
	int m_rows,m_columns;
	int dimension;
	int nonZeros;
};
typedef struct CSR_Matrix* CSR_Matrix;

CSR_Matrix initCSRMatrix();
void printCSRMatrix(CSR_Matrix csrm);
void destroyCSRMatrix(CSR_Matrix csrm);

#endif /* CSR_H_ */
