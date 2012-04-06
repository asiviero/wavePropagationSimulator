/*
 * constants.h
 *
 *  Created on: Mar 8, 2012
 *      Author: andre
 *
 *  This file will contain several constants, mostly physical and mathematical
 *  constants, such as Pi, Euler Number, the Gravitational Constant and many
 *  others usually present in physical equations that govern movement
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
#define N_HNODES 5
#define N_VNODES 5
#define MESH_HLENGTH 1.0
#define MESH_VLENGTH 1.0

// Time-step
#define DELTA_TIME 0.1

#endif /* CONSTANTS_H_ */
