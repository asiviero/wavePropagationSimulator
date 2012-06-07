/*
 * timeStep.c
 *
 *  Created on: Apr 5, 2012
 *      Author: andre
 */

#include "../../wavePropagationSimulator.h"

void loadUKP1(structMatrix sM,float time, float (*waveSpeedFunction)(int,float)) {

	float fDelta[3];
	fDelta[X_AXIS] = MESH_HLENGTH/N_HNODES;
	fDelta[Y_AXIS] = MESH_VLENGTH/N_VNODES;

	loadIdentityMatrix(sM);

	// Load indexes for inner nodes
	for(int i=1;i<(N_HNODES-1);i++) {
		for(int j=1;j<(N_VNODES-1);j++) {
			int index = i*N_HNODES+j;
			sM->matrix[index][index] = (-1/(pow(fDelta[X_AXIS],2)) -1/(pow(fDelta[Y_AXIS],2)) + 2/(waveSpeed(index,time)*pow(DELTA_TIME,2)));
			sM->matrix[index][index-1] = sM->matrix[index][index+1] = 1/(2*pow(fDelta[X_AXIS],2));
			sM->matrix[index][index-N_HNODES] = sM->matrix[index][index+N_HNODES] = 1/(2*pow(fDelta[Y_AXIS],2));
		}
	}
}

// This function loads the CSR version for U[k+1] matrix. It's a little tricky but I've tried
// to use comprehensible variable names.
void loadUKP1CSR(CSR_Matrix csrm,float time, float (*waveSpeedFunction)(int,float)) {

	int sqrtdim = sqrt(csrm->dimension);
	float fDelta[3];
	fDelta[X_AXIS] = MESH_HLENGTH/N_HNODES;
	fDelta[Y_AXIS] = MESH_VLENGTH/N_VNODES;

	int line_number,in_row_index,column_number,in_row_value;
	int index;

	in_row_index=1; column_number=0;
	in_row_value=0;

	// This loop fills the first N_HNODES from the matrix
	// since they're all in a boundary condition, they're
	// all 1s, one at each line, so it gets quite simple.
	// It also has the side effect to alter the value of line_number
	// This is the only loop with side effects
	for(line_number=0; line_number<sqrtdim; line_number++) {
		csrm->fValuesVector[line_number] = 1;
		csrm->columnVector[line_number] = line_number;
		csrm->in_rowVector[in_row_index] = ++in_row_value;
		in_row_index++; column_number++;
	}

	// Once the "lower bound" is filled, we proceed to fill the other lines from the mesh
	// Since we fill it horizontally, the first and last nodes are boundary nodes, which
	// will be clear in the code below. Then we fill the inner nodes, whose lines on the
	// matrix will have 5 non zero elements (bi-dimensional case).
	for(int i=0; i<sqrtdim-2;i++) {

		// First node, boundary condition
		csrm->fValuesVector[line_number] = 1;
		csrm->columnVector[line_number] = column_number;
		csrm->in_rowVector[in_row_index] = ++in_row_value;

		in_row_index++; line_number++; column_number++;

		// Inner nodes. In square meshes, there're are sqrtdim-2 inner nodes per line.
		for(int j=0; j < sqrtdim -2; j++) {
			in_row_value += 5;
			csrm->fValuesVector[line_number] = 1/(2*pow(fDelta[Y_AXIS],2));
			csrm->columnVector[line_number] = column_number-sqrtdim;

			csrm->fValuesVector[line_number+1] = 1/(2*pow(fDelta[X_AXIS],2));
			csrm->columnVector[line_number+1] = column_number-1;

			index = line_number*sqrtdim+line_number;
			csrm->fValuesVector[line_number+2] = (-1/(pow(fDelta[X_AXIS],2)) -1/(pow(fDelta[Y_AXIS],2)) - 1/(pow(waveSpeedFunction(index,time),2)*pow(DELTA_TIME,2)));
			csrm->columnVector[line_number+2] = column_number;

			csrm->fValuesVector[line_number+3] = 1/(2*pow(fDelta[X_AXIS],2));
			csrm->columnVector[line_number+3] = column_number+1;

			csrm->fValuesVector[line_number+4] = 1/(2*pow(fDelta[Y_AXIS],2));
			csrm->columnVector[line_number+4] = column_number+sqrtdim;
			csrm->in_rowVector[in_row_index] = in_row_value;
			line_number+=5;
			in_row_index++; column_number++;
		}

		// Last node in the line, it's also a boundary node
		csrm->fValuesVector[line_number] = 1;
		csrm->columnVector[line_number] = column_number;
		csrm->in_rowVector[in_row_index] = ++in_row_value;

		in_row_index++; line_number++; column_number++;
	}

	// Once the inner lines are filled, we proceed to the last line, whose nodes are boundary nodes. This loop is similar to
	// the first one, however the iterators have changed
	for(int i=0; i<sqrtdim; i++) {
		csrm->fValuesVector[line_number] = 1;
		csrm->columnVector[line_number] = column_number++;
		csrm->in_rowVector[in_row_index] = ++in_row_value;
		in_row_index++; line_number++;
	}
}

// This is an auxiliary function in order to assemble the linear system
// It performs the multiplication of a function of the wave speed and
// delta time to a vector in time I, so I+1 can be calculated
void applyWaveSpeedTimeStepIntoMatrix(structMatrix extV, float time, float (*waveSpeedFunction)(int,float)) {
	// Check if extV is actually a matrix in extended vector format
	if(extV->m_columns != 1) {
		printf("Invalid call to apply wave speed and time step. Aborting...\n");
		exit(3);
	}
	for(int i=0; i< extV->m_rows; i++) {
		extV->matrix[i][0] *= -2/pow(DELTA_TIME,2);
		extV->matrix[i][0] /= pow(waveSpeedFunction(i,time),2);
	}
}

void loadUKL1(structMatrix UKL1,float time, float (*waveSpeedFunction)(int,float)) {
		float fDelta[3];
		fDelta[X_AXIS] = MESH_HLENGTH/N_HNODES;
		fDelta[Y_AXIS] = MESH_VLENGTH/N_VNODES;

		loadIdentityMatrix(UKL1);

		// Load indexes for inner nodes
		for(int i=1;i<(N_HNODES-1);i++) {
			for(int j=1;j<(N_VNODES-1);j++) {
				int index = i*N_HNODES+j;
				UKL1->matrix[index][index] = (1/(pow(fDelta[X_AXIS],2)) + 1/(pow(fDelta[Y_AXIS],2)) + 1/(pow(waveSpeedFunction(index,time),2)*pow(DELTA_TIME,2)));
				UKL1->matrix[index][index-1] = UKL1->matrix[index][index+1] = -1/(2*pow(fDelta[X_AXIS],2));
				UKL1->matrix[index][index-N_HNODES] = UKL1->matrix[index][index+N_HNODES] = -1/(2*pow(fDelta[Y_AXIS],2));
			}
		}
}
