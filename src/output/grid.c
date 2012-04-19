// A simple function to generate a mesh based on the code's constants
// it's roughly equivalent to Octave's or Matlab's meshgrid

#include "../../constants.h"
#include <stdio.h>

void generateGridToFile(char *file) {
	FILE *gridFile = fopen(file,"w");
		float interval = MESH_HLENGTH / N_HNODES;
		fprintf(gridFile,"x = [");
		for(int j=0; j <= N_HNODES; j++) {
			for(int i=0; i <= N_HNODES ; i++) fprintf(gridFile,"%f ",i*interval);
			fprintf(gridFile,";");
		}
		fprintf(gridFile,"];\n");

		fprintf(gridFile,"y = [");
			for(int i=0; i <= N_HNODES; i++) {
				for(int j=0; j <= N_HNODES ; j++) fprintf(gridFile,"%f ",i*interval);
				fprintf(gridFile,";");
		}
		fprintf(gridFile,"];\n");


	fclose(gridFile);
}
