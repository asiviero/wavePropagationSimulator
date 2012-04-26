/*
 * output.h
 *
 *  Created on: Apr 18, 2012
 *      Author: andre
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

void generateGridToFile(char *file);
void loadMesh(structMatrix x, structMatrix y);
void generateWaveBenchmark(char *destinyFileName,void (*waveFunction)(structMatrix,structMatrix,structMatrix,structMatrix));
void generateWaveBenchmarkTimeVariant(char *destinyFileName,char *folderName,void (*waveFunction)(structMatrix,structMatrix,structMatrix a[],structMatrix b[]));
void wave1(structMatrix mesh_hmatrix,structMatrix mesh_vmatrix,structMatrix u_matrix,structMatrix v_matrix);
void wave2(structMatrix mesh_hmatrix,structMatrix mesh_vmatrix,structMatrix u_matrix[],structMatrix v_matrix[]);
void generateFileNames(char path_matrix[][40], char *destinyFileName, char *folderName);
#endif /* OUTPUT_H_ */
