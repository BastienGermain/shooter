#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h>

#define VITESSE_DEFILEMENT 0.02
#define TAILLE_VAISSEAU 0.5
#define TAILLE_ENEMY 0.5
#define LONGUEUR_MISSILE 0.5
#define HAUTEUR_MISSILE 0.2
#define MAX_MISSILES 10

typedef struct BoundingBox {
	float pMinX, pMinY, pMaxX, pMaxY;	
} BoundingBox;

typedef struct Obstacle {
	float posX, posY;
	int r, g, b;
	BoundingBox box;
	int levelEnd; // bool : la case est une case de la ligne d'arrivée (pour le bg)
	struct Obstacle *next;
} Obstacle, *ObstacleList;

typedef struct Enemy {
	float posX, posY;
	int sens; // sens du déplacement (1 vers le haut; -1 vers le bas)
	BoundingBox box;
	struct Enemy *next;
} Enemy, *EnemyList;

typedef struct Missile {
	float posX, posY;
	BoundingBox box;
	struct Missile *next;
} Missile, *MissileList;

//ship
void drawShip(float x, float y);
void drawLives(int lives);
void drawAmmu(int numbMissiles);

// background
ObstacleList readPPM(FILE *file);
void drawObstacles(ObstacleList list);
void moveObstacles(Obstacle *obstacle);
int collObstacles(ObstacleList *obstacle, BoundingBox box);
void supprimerObstacleFromList(Obstacle *toSuppr, ObstacleList *list);

// collision
int checkCollision(BoundingBox box1, BoundingBox box2);
void collEnemiesObstacles(ObstacleList *obstacle, EnemyList *enemy);
void collEnemiesMissiles(MissileList *missile, EnemyList *enemy);
void collObstaclesMissiles(MissileList *missile, ObstacleList *obstacle);

// enemy
void drawEnemy(float x, float y);
void drawEnemies(EnemyList enemy);
int createEnemy(EnemyList *list);
void genereEnemy(EnemyList *list);
void moveEnemy(Enemy *enemy);
void supprimerEnemyFromList(Enemy *toSuppr, EnemyList *list);
int collEnemies(EnemyList *enemy, BoundingBox box);

// missile
int createMissile(MissileList *list, float y);
void drawMissiles(MissileList list);
void moveMissiles(Missile *missile);
void supprimerMissileFromList(Missile *toSuppr, MissileList *list);

#endif