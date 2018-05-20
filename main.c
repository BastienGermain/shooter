#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "header.h"

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void drawShip(float x, float y) {
    glBegin(GL_QUADS);
        glColor3ub(150, 100, 250);
        glVertex2f(x, y);
        glVertex2f(x + TAILLE_VAISSEAU, y);
        glVertex2f(x + TAILLE_VAISSEAU, y + TAILLE_VAISSEAU);
        glVertex2f(x, y + TAILLE_VAISSEAU);        
    glEnd();
}


int main(int argc, char** argv) {
    
    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0., 10., 0., 10.);  // Ici on précise que nos coordonées vont de 0 à 10 pour chaque axe
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("Jeu", NULL);

    /* Varriables des écrans */
    int mode = 0; /* 0 = menu/accueil; 1 = jeu */

    /* Variables background */
    FILE *bg = fopen("bg1.ppm", "r");
    ObstacleList obstacles = readPPM(bg);
    fclose(bg);

    /* Variables vaisseau */
    int vies = 3;
    float shipPosY = 4.5;

    /* Créé la bounding box du vaisseau */

    BoundingBox shipBox;

    shipBox.pMinX = 2;
    shipBox.pMaxX = 2 + TAILLE_VAISSEAU;

    shipBox.pMinY = shipPosY;
    shipBox.pMaxY = shipPosY + TAILLE_VAISSEAU;

    // Variables enemy

    EnemyList enemies = NULL;
    int genere = 1; // à 0 on stop la génération d'enemy
    
    /* Boucle d'affichage */
    int loop = 1;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();

        glClear(GL_COLOR_BUFFER_BIT); // Nettoie la fenêtre
        glClearColor(1, 1, 1, 1); // fond couleur blanc

        /* Dessine le background */
        moveObstacles(obstacles);
        drawObstacles(obstacles); 

        /* Vaisseau */

        drawShip(2, shipPosY);
        if (vies == 0) {
            printf("Perdu !\n");
        }

        /* Enemies */

        if (genere == 1) {
            genereEnemy(&enemies); // créé de nouveaux enemy aléatoirement
        }
        
        drawEnemies(enemies);
        moveEnemy(enemies);
        int collEnemy = collEnemies(&enemies, shipBox);   

        if (collEnemy == 1) {
            vies -= 1;
            printf("nb vies : %d\n", vies);
        }

        /* Obstacles */

        int collObst = collObstacles(&obstacles, shipBox);   

        if (collObst == 1) {
            vies -= 1;
            printf("nb vies : %d\n", vies);
        } else if (collObst == 2) {
            printf("Fin de partie !!!\n");
        }

        ObstacleList tmp = obstacles;

        // Test la présence de la ligne d'arrivée à l'écran pour arrêter la génération d'enemies
        if (genere != 0) {
            while (tmp != NULL) {
                if (tmp->levelEnd == 1) {
                    if (tmp->box.pMinX < 10) {
                        genere = 0;
                        break;
                    }
                }

                tmp = tmp->next;
            }
        }
        

        /* Test les collisions vaisseau/bg et enemy/bg */
            
            /*int collShip = checkCollision(shipBox, bgBox[k]);

            collEnemies(&enemies, bgBox[k]);

            if (collShip == 1) {
                bgBox[k].pMaxX = 0;
                bgBox[k].pMaxY = 0;
                vies -= 1;
                printf("nb vies : %d\n", vies);              
            }*/

                 

             

        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();

        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            switch(e.type) {

                case SDL_KEYDOWN:
                    // appuie sur la touche "q" pour fermer la fenêtre 
                    if (e.key.keysym.sym == 113) {
                        loop = 0;
                    }

                    break;

                default:
                    break;
            }

        }

        /* Gère les mouvements du vaisseau */
        
        const Uint8 *state = SDL_GetKeyState(NULL);
        
        if (state[SDLK_UP]) {
            shipPosY += 0.05;
            shipBox.pMinY = shipPosY;
            shipBox.pMaxY = shipPosY + TAILLE_VAISSEAU;
        }

        if (state[SDLK_DOWN]) {
            shipPosY -= 0.05;
            shipBox.pMinY = shipPosY;
            shipBox.pMaxY = shipPosY + TAILLE_VAISSEAU;
        }        

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
