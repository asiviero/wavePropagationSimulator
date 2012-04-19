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
