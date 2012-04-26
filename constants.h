/*
 * constants.h
 *
 *  Created on: Mar 8, 2012
 *      Author: andre
 *
 *
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// True / False
#define TRUE 1
#define FALSE 0

// Constants used in motion vectors, such as position, speed and acceleration
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define TIME 3

// These constans define mesh properties
#define N_HNODES 10
#define N_VNODES 10
#define MESH_HLENGTH 1.0
#define MESH_VLENGTH 1.0

// Time-step
#define DELTA_TIME 0.1
#define N_TIME_STEPS 10

// CSR constants
#define VALUES 0
#define COLUMN 1
#define IN_ROW 2

// Aux Constants
#define MAX_FILENAME_LENGTH 40

#endif /* CONSTANTS_H_ */
