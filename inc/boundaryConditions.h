/*
 * boundaryConditions.h
 *
 *  Created on: Apr 27, 2012
 *      Author: andre
 */

#ifndef BOUNDARYCONDITIONS_H_
#define BOUNDARYCONDITIONS_H_


#endif /* BOUNDARYCONDITIONS_H_ */

void loadExtVectorOnInitialTime(structMatrix **extV,char *sourceFile);
structMatrix *loadExtVectorTimeDerivative(void (*waveFunction)(structMatrix,structMatrix,structMatrix,structMatrix));
void laplacianViaFD(structMatrix destiny, structMatrix extV);
void correctLaplacian(structMatrix laplacian, float time);
void applyBoundaryConditions(structMatrix extV, float *boundaryVector);
void generateBoundaryVectorFromFunction(float *boundaryVector,float time, float axis, float (*waveFunction)(int,float,float,float));
