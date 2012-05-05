/*
 * solver.h
 *
 *  Created on: May 5, 2012
 *      Author: andre
 */

#ifndef SOLVER_H_
#define SOLVER_H_

void CSR_SOR(structMatrix resultVector,CSR_Matrix CoefficientsMatrix, structMatrix extV_IndependentTerms, float floatWParameter);

#endif /* SOLVER_H_ */
