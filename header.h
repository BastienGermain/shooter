#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h>

//static int PIXELS_PAR_BLOC = 40;

typedef struct BoundingBox {
	float pMinX, pMinY, pMaxX, pMaxY;
	int tabEnd; // bool : utile pour tester la fin du tableau dans le main
	int levelEnd; // bool : la case est une case de la ligne d'arrivée 
} BoundingBox;


BoundingBox* drawPPM(FILE *fp, float startX);

int checkCollision(BoundingBox box1, BoundingBox box2);

#endif