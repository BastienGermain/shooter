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

// Dessine une liste d'enemy
void drawEnemies(EnemyList enemy) {
	if (enemy != NULL) {
		drawEnemy(enemy->posX, enemy->posY);

		drawEnemies(enemy->next);
	}
}

// Ajoute un enemy en début de liste
int createEnemy(EnemyList *list) {

	Enemy *new = malloc(sizeof(Enemy));

	if (new == NULL){ /* Si malloc échoue */
		return 0;
	} else {
		new->posX = 9;
		float Y = rand() % 11; // random number de 0 à 10
		new->posY = Y;
		new->sens = 1;

		BoundingBox box;

		box.pMinX = 9;
		box.pMaxX = 9 + TAILLE_ENEMY;

		box.pMinY = Y;
		box.pMaxY = Y + TAILLE_ENEMY;

		new->box = box;

		new->next = *list;
		*list = new; 

		return 1;
	}

}

void genereEnemy(EnemyList *list) {
	// Fonction appelée à chaque tour de boucle
	int randomNum = rand() % 100;

	// Se déclenche une fois sur 100
	if (randomNum == 0) {
		createEnemy(list);
	}
}

// Déplace les enemies
void moveEnemy(Enemy *enemy) {

	// Le mouvement est en zigzag

	if (enemy != NULL) {
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

		BoundingBox box;

		box.pMinX = enemy->posX;
		box.pMaxX = enemy->posX + TAILLE_ENEMY;

		box.pMinY = enemy->posY;
		box.pMaxY = enemy->posY + TAILLE_ENEMY;

		enemy->box = box;

		moveEnemy(enemy->next);
	}
	
}

// Supprime un enemy de la liste
void supprimerEnemyFromList(Enemy *toSuppr, EnemyList *list) {

	/* Si l'enemey à supprimer est en début de liste */
	if (toSuppr == *list){			

		/* On fait pointer la liste sur l'enemy qui suit celui à supprimé */
		*list = toSuppr->next;

	/* Si l'enemy' à supprimer est en seconde position */
	} else if (toSuppr == (*list)->next) {

		/* On fait pointer le premier enemy de la liste sur celui qui suit l'enemy à supprime */
		(*list)->next = toSuppr->next;

	} else {
		/* On conserve la valeur d'entrée de la liste */
		EnemyList conserve = *list;

		/* On boucle jusqu'à arriver à l'enemy qui précède celui à supprimer */
		while (toSuppr != (*list)->next) {
			*list = (*list)->next; /* !!! ici l'entrée de la liste est modifiée !!! */
		}

		/* On fait pointer l'enemy qui précède sur celui qui suit l'enemy à supprimé */
		(*list)->next = toSuppr->next;

		/* On remet la bonne valeur d'entrée pour la liste */
		*list = conserve;
	}

	free(toSuppr);
}

// Gère les collisions avec la liste d'enemy
void collEnemies(EnemyList *enemy, BoundingBox box) {
	EnemyList tmp = *enemy;

	if (tmp != NULL) {
	
		int coll = checkCollision(box, tmp->box);

		if (coll == 1) {
			printf("collision avec enemy\n");
			supprimerEnemyFromList(tmp, enemy);
		}

		collEnemies(&tmp->next, box);
	}

}