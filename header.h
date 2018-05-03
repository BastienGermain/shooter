#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h>

//static int PIXELS_PAR_BLOC = 40;

typedef struct BoundingBox {
	float pMinX, pMinY, pMaxX, pMaxY;
	int end; // utile pour tester la fin du tableau dans le main
} BoundingBox;


BoundingBox* drawPPM(FILE *fp, float startX);

int checkCollision(BoundingBox box1, BoundingBox box2);

#endif