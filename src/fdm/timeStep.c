/*
 * timeStep.c
 *
 *  Created on: Apr 5, 2012
 *      Author: andre
 */

#include "../../wavePropagationSimulator.h"

void loadUKP1(structMatrix sM) {

	float fDelta[3];
	fDelta[X_AXIS] = MESH_HLENGTH/N_HNODES;
	fDelta[Y_AXIS] = MESH_VLENGTH/N_VNODES;

	loadIdentityMatrix(sM);

	// Load indexes for inner nodes
	for(int i=1;i<(N_HNODES-1);i++) {
		for(int j=1;j<(N_VNODES-1);j++) {
			int t = i*N_HNODES+j;
			sM->matrix[t][t] = (-1/(pow(fDelta[X_AXIS],2)) -1/(pow(fDelta[Y_AXIS],2)) + 2/(waveSpeed(t,0)*pow(DELTA_TIME,2)));
			sM->matrix[t][t-1] = sM->matrix[t][t+1] = 1/(2*pow(fDelta[X_AXIS],2));
			sM->matrix[t][t-N_HNODES] = sM->matrix[t][t+N_HNODES] = 1/(2*pow(fDelta[Y_AXIS],2));
		}
	}
}

// This function loads the CSR version for U[k+1] matrix. It's a little tricky but I've tried
// to use comprehensible variable names.
void loadUKP1CSR(CSR_Matrix csrm) {

	int sqrtdim = sqrt(csrm->dimension);
	float fDelta[3];
	fDelta[X_AXIS] = MESH_HLENGTH/N_HNODES;
	fDelta[Y_AXIS] = MESH_VLENGTH/N_VNODES;

	int line_number,in_row_index,column_number,in_row_value;
	float t;

	in_row_index=1; column_number=0;
	in_row_value=0;

	// This loop fills the first N_HNODES from the matrix
	// since they're all in a boundary condition, they're
	// all 1s, one at each line, so it gets quite simple.
	// It also has the side effect to alter the value of line_number
	// This is the only loop with side effects
	for(line_number=0; line_number<sqrtdim; line_number++) {
		csrm->CSRVector[VALUES][line_number] = 1;
		csrm->CSRVector[COLUMN][line_number] = line_number;
		csrm->CSRVector[IN_ROW][in_row_index] = ++in_row_value;
		in_row_index++; column_number++;
	}

	// Once the "lower bound" is filled, we proceed to fill the other lines from the mesh
	// Since we fill it horizontally, the first and last nodes are boundary nodes, which
	// will be clear in the code below. Then we fill the inner nodes, whose lines on the
	// matrix will have 5 non zero elements (bi-dimensional case).
	for(int i=0; i<sqrtdim-2;i++) {

		// First node, boundary condition
		csrm->CSRVector[VALUES][line_number] = 1;
		csrm->CSRVector[COLUMN][line_number] = column_number;
		csrm->CSRVector[IN_ROW][in_row_index] = ++in_row_value;

		in_row_index++; line_number++; column_number++;

		// Inner nodes. In square meshes, there're are sqrtdim-2 inner nodes per line.
		for(int j=0; j < sqrtdim -2; j++) {
			in_row_value += 5;
			csrm->CSRVector[VALUES][line_number] = 1/(2*pow(fDelta[Y_AXIS],2));
			csrm->CSRVector[COLUMN][line_number] = column_number-sqrtdim;

			csrm->CSRVector[VALUES][line_number+1] = 1/(2*pow(fDelta[X_AXIS],2));
			csrm->CSRVector[COLUMN][line_number+1] = column_number-1;

			// t is a parameter which identifies the node position and it's used by waveSpeed function
			// todo alter the second parameter of waveSpeed to include time variation. It'll also be needed
			// to change the function parameters
			t = line_number*sqrtdim+line_number;
			csrm->CSRVector[VALUES][line_number+2] = (-1/(pow(fDelta[X_AXIS],2)) -1/(pow(fDelta[Y_AXIS],2)) + 2/(waveSpeed(t,0)*pow(DELTA_TIME,2)));
			csrm->CSRVector[COLUMN][line_number+2] = column_number;

			csrm->CSRVector[VALUES][line_number+3] = 1/(2*pow(fDelta[X_AXIS],2));
			csrm->CSRVector[COLUMN][line_number+3] = column_number+1;

			csrm->CSRVector[VALUES][line_number+4] = 1/(2*pow(fDelta[Y_AXIS],2));
			csrm->CSRVector[COLUMN][line_number+4] = column_number+sqrtdim;
			csrm->CSRVector[IN_ROW][in_row_index] = in_row_value;
			line_number+=5;
			in_row_index++; column_number++;
		}

		// Last node in the line, it's also a boundary node
		csrm->CSRVector[VALUES][line_number] = 1;

		csrm->CSRVector[COLUMN][line_number] = column_number;
		csrm->CSRVector[IN_ROW][in_row_index] = ++in_row_value;
		in_row_index++; line_number++; column_number++;
	}

	// Once the inner lines are filled, we proceed to the last line, whose nodes are boundary nodes. This loop is similar to
	// the first one, however the iterators have changed
	for(int i=0; i<sqrtdim; i++) {
			csrm->CSRVector[VALUES][line_number] = 1;
			csrm->CSRVector[COLUMN][line_number] = line_number;
			csrm->CSRVector[IN_ROW][in_row_index] = ++in_row_value;
			in_row_index++; line_number++;
		}
	//

}
