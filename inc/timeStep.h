/*
 * timeStep.h
 *
 *  Created on: Apr 5, 2012
 *      Author: andre
 */

#ifndef TIMESTEP_H_
#define TIMESTEP_H_

#include "matrix.h"
#include "CSR.h"
void loadUKP1(structMatrix sM,float time, float (*waveSpeedFunction)(int,float));
void loadUKP1CSR(CSR_Matrix csrm,float time, float (*waveSpeedFunction)(int,float));
void applyWaveSpeedTimeStepIntoMatrix(structMatrix extV, float time, float (*waveSpeedFunction)(int,float));
void loadUKL1(structMatrix UKL1,float time, float (*waveSpeedFunction)(int,float));

#endif /* TIMESTEP_H_ */
