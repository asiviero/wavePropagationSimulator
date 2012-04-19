/*
 * dominantDiagonal.c
 *
 *  Created on: Apr 5, 2012
 *      Author: andre
 */

void testForDominantDiagonal() {
	float dx,dy,dt,c,md,rd;
	dx = dy = dt = 0.1;
	c = 340;

	while(dx > 0.01) {
		md = (-c/(dx*dx)-c/(dy*dy)+2/(dt*dt));
		rd = c*(1/(dx*dx)+1/(dy*dy));
		printf("dx: %.2f | dy: %.2f | dt: %.1f | md: %f | rd: %f | %d\n",dx,dy,dt,md,rd,md>rd);
		dx -=0.01;
		dy = dx;
	}
	dx = dy = dt = 0.1;

	printf("--\n");

	while(dt > 0.01) {
		md = (-c/(dx*dx)-c/(dy*dy)+2/(dt*dt));
		rd = c*(1/(dx*dx)+1/(dy*dy));
		printf("dx: %.2f | dy: %.2f | dt: %.1f | md: %f | rd: %f | %d\n",dx,dy,dt,md,rd,md>rd);
		dt -=0.01;
	}


}
