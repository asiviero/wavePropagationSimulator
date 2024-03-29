/*
 * matrix.h
 *
 *  Created on: Apr 5, 2012
 *      Author: andre
 */

#ifndef MATRIX_H_
#define MATRIX_H_

struct sM {
	float **matrix;
	int m_rows,m_columns;
};
typedef struct sM* structMatrix;

//void initMatrix(float **matrix, int dimension);
structMatrix initMatrix(int h_dimension, int v_dimension);
structMatrix matrixMultiplication(structMatrix m1, structMatrix m2);
structMatrix matrixSum(structMatrix m1, structMatrix m2);
structMatrix tmpMatrixTimesScalar(structMatrix m1,float scalar);
structMatrix extVectorToMatrix(structMatrix m1);
structMatrix matrixToExtVector(structMatrix m1);
structMatrix pointByPointProduct(structMatrix m1,structMatrix m2);


void matrixSubtractionDestined(structMatrix result, structMatrix m1, structMatrix m2);
void copyMatrix(structMatrix result,structMatrix sM);
void matrixMultiplicationDestined(structMatrix result, structMatrix m1, structMatrix m2);
void matrixSumDestinedMIPSFormat(structMatrix result, structMatrix m1, structMatrix m2);
void matrixSumDestined(structMatrix result, structMatrix toBeAdded);
void matrixTimesScalar(structMatrix m1,float scalar);
void loadIdentityMatrix(structMatrix sM);
void printMatrix(structMatrix sM);
void printMatrixToFile(structMatrix sM,char *destinyFileName,char *matrixName);
void destroyMatrix(structMatrix sM);
void resetMatrix(structMatrix sM);
float maxVector(structMatrix extV);

#endif /* MATRIX_H_ */
