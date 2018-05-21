#include <stdlib.h>
#include <stdio.h>

#include "header.h"

int checkCollision(BoundingBox box1, BoundingBox box2) {

	/*printf("box1 : %f %f %f %f\n", box1.pMinX, box1.pMaxX, box1.pMinY, box1.pMaxY);
	printf("box2 : %f %f %f %f\n", box2.pMinX, box2.pMaxX, box2.pMinY, box2.pMaxY);*/

	/* Collisions par l'avant */
	if (box1.pMaxX > box2.pMinX && box1.pMaxX < box2.pMaxX) {
		
		/* Collisions par dessus */
		if (box1.pMinY < box2.pMaxY && box1.pMinY > box2.pMinY) {
			return 1;
		} 

		/* Collisions par dessous */
		else if (box1.pMaxY > box2.pMinY && box1.pMaxY < box2.pMaxY) {
			return 1;
		}
	}

	/* Collisions par l'arrière */
	else if (box1.pMinX < box2.pMaxX && box1.pMinX > box2.pMinX) {

		/* Collisions par dessus */
		if (box1.pMinY < box2.pMaxY && box1.pMinY > box2.pMinY) {
			return 1;
		} 

		/* Collisions par dessous */
		else if (box1.pMaxY > box2.pMinY && box1.pMaxY < box2.pMaxY) {			
			return 1;
		}
	}

	return 0;
}

// Gère les collisions entre les enemies et les obstacles
void collEnemiesObstacles(ObstacleList *obstacle, EnemyList *enemy) {
    ObstacleList tmp = *obstacle;

    if (tmp != NULL) {
    
        int coll = collEnemies(enemy, tmp->box);

        if (coll == 1) {
            printf("collision avec enemy / décor\n");
        }

        collEnemiesObstacles(&tmp->next, enemy);
    }

}


void collEnemiesMissiles(MissileList *missile, EnemyList *enemy) {
    MissileList tmp = *missile;

    if (tmp != NULL) {
    
        int coll = collEnemies(enemy, tmp->box);

        if (coll == 1) {
            printf("collision avec enemy / missile\n");
            supprimerMissileFromList(tmp, missile);
        }

        collEnemiesMissiles(&tmp->next, enemy);
    }

}

void collObstaclesMissiles(MissileList *missile, ObstacleList *obstacle) {
    MissileList tmp = *missile;

    if (tmp != NULL) {
    
        int coll = collObstacles(obstacle, tmp->box);

        if (coll == 1) {
            printf("collision avec obstacle / missile\n");
            supprimerMissileFromList(tmp, missile);
        }

        collObstaclesMissiles(&tmp->next, obstacle);
    }

}