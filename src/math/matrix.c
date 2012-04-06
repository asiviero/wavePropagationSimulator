/*
 * matrix.c
 *
 *  Created on: Apr 5, 2012
 *      Author: andre
 */

void initMatrix(float **matrix, int dimension) {
	matrix = (float**)calloc(dimension,sizeof(float*));
	for(int i=0;i<dimension;i++) matrix[i] = (float*)calloc(dimension,sizeof(float));
}

void destroyMatrix(float **matrix, int dimension) {
	for(int i=0; i<dimension; i++) free(matrix[i]);
	free(matrix);
}

void resetMatrix(float **matrix) {
	bzero(*matrix,sizeof(*matrix));
}
