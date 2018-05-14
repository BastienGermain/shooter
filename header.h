#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h>

#define VITESSE_DEFILEMENT 0.02
#define TAILLE_VAISSEAU 0.5
#define TAILLE_ENEMY 0.5

//static int PIXELS_PAR_BLOC = 40;

typedef struct BoundingBox {
	float pMinX, pMinY, pMaxX, pMaxY;
	int tabEnd; // bool : utile pour tester la fin du tableau dans le main (pour le bg)
	int levelEnd; // bool : la case est une case de la ligne d'arrivée (pour le bg)
} BoundingBox;

typedef struct Enemy {
	float posX, posY;
	int sens; // sens du déplacement (1 vers le haut; -1 vers le bas)
	BoundingBox box;
} Enemy;

BoundingBox* drawPPM(FILE *fp, float startX);

int checkCollision(BoundingBox box1, BoundingBox box2);

void drawEnemy(float x, float y);
Enemy* createEnemy();
void moveEnemy(Enemy *enemy);


#endif