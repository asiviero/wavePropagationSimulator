// A simple function to generate a mesh based on the code's constants
// it's roughly equivalent to Octave's or Matlab's meshgrid

#include "../../wavePropagationSimulator.h"

void generateGridToFile(char *file) {
	FILE *gridFile = fopen(file,"w");
		float interval = MESH_HLENGTH / N_HNODES;
		fprintf(gridFile,"x = [");
		for(int j=0; j < N_HNODES; j++) {
			for(int i=0; i < N_HNODES ; i++) fprintf(gridFile,"%f ",i*interval);
			fprintf(gridFile,";");
		}
		fprintf(gridFile,"];\n");

		fprintf(gridFile,"y = [");
			for(int i=0; i < N_HNODES; i++) {
				for(int j=0; j < N_HNODES ; j++) fprintf(gridFile,"%f ",i*interval);
				fprintf(gridFile,";");
		}
		fprintf(gridFile,"];\n");


	fclose(gridFile);
}

// Same as above, however this puts the mesh in matrixes X and Y instead of
// a .m file
void loadMesh(structMatrix x, structMatrix y) {


	float interval = MESH_HLENGTH / N_HNODES;
	for(int i=0; i < N_HNODES; i++) {
		for(int j=0; j < N_HNODES ; j++) {
			x->matrix[i][j] = j*interval;
		}
	}
	for(int i=0; i < N_HNODES; i++) {
		for(int j=0; j < N_HNODES ; j++) {
			y->matrix[i][j] = i*interval;
		}
	}
}












