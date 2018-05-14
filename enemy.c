#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "header.h"

void drawEnemy(float x, float y) {
    glBegin(GL_QUADS);
        glColor3ub(150, 100, 0);
        glVertex2f(x, y);
        glVertex2f(x + TAILLE_ENEMY, y);
        glVertex2f(x + TAILLE_ENEMY, y + TAILLE_ENEMY);
        glVertex2f(x, y + TAILLE_ENEMY);        
    glEnd();
}

Enemy* createEnemy() {
	Enemy *enemy = malloc(sizeof(Enemy));

	enemy->posX = 9;
	enemy->posY = rand() % 11; // random number de 0 à 10
	enemy->sens = 1;

	return enemy;
}

void moveEnemy(Enemy *enemy) {

	// CA FAIT UN ZIGZAG !!!

	if (enemy->sens == 1) {
		enemy->posY += VITESSE_DEFILEMENT*5;
		if (enemy->posY > 8) {
			enemy->sens = -1;
		}
	} else {
		enemy->posY -= VITESSE_DEFILEMENT*5;
		if (enemy->posY < 2){
			enemy->sens = 1;
		}
	}
	
	enemy->posX -= VITESSE_DEFILEMENT*1.5;
}