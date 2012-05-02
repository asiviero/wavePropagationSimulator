/*
 * waveFunctions.c
 *
 *  Created on: 19/04/2012
 *      Author: gerente
 */
#include "../../wavePropagationSimulator.h"

void wave1(structMatrix mesh_hmatrix,structMatrix mesh_vmatrix,structMatrix u_matrix,structMatrix v_matrix) {
	for(int i=0; i<mesh_hmatrix->m_rows; i++) {
		for(int j=0; j< mesh_hmatrix->m_columns; j++) {
			u_matrix->matrix[i][j] = mesh_hmatrix->matrix[i][j];//5*cos(-8*mesh_hmatrix->matrix[i][j]);
			v_matrix->matrix[i][j] = mesh_vmatrix->matrix[i][j];//;4*cos(-8*mesh_hmatrix->matrix[i][j]);
		}
	}
}

void wave2(structMatrix mesh_hmatrix,structMatrix mesh_vmatrix,structMatrix u_matrix[],structMatrix v_matrix[]) {
	for(int t=0; t < N_TIME_STEPS; t++) {
		for(int i=0; i<mesh_hmatrix->m_rows; i++) {
			for(int j=0; j< mesh_hmatrix->m_columns; j++) {
				u_matrix[t]->matrix[i][j] = 5*cos(10*(t*DELTA_TIME)-8*mesh_hmatrix->matrix[i][j]);
				v_matrix[t]->matrix[i][j] = 4*cos(10*(t*DELTA_TIME)-8*mesh_hmatrix->matrix[i][j]);
			}
		}
	}
}

void wave2TimeDerivative(structMatrix mesh_hmatrix,structMatrix mesh_vmatrix,structMatrix u_matrix,structMatrix v_matrix) {
		for(int i=0; i<mesh_hmatrix->m_rows; i++) {
			for(int j=0; j< mesh_hmatrix->m_columns; j++) {
				u_matrix->matrix[i][j] = 50*sin(8*mesh_hmatrix->matrix[i][j]);
				v_matrix->matrix[i][j] = 40*sin(8*mesh_hmatrix->matrix[i][j]);
			}
		}
}

float wave2Returnable(int axis, float x,float y, float t) {
	switch(axis) {
		case X_AXIS:
			printf("Entrei, valor de retorno: %f\n",(5*cos(10*t-8*x)));
			return(5*cos(10*t-8*x));
		case Y_AXIS:
			return(4*cos(10*t-8*x));
	}
}
