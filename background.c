#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "header.h"

/* Dessine le background et renvoie un tableau contenant la bounding box de chaque case obstacle */
BoundingBox* drawPPM(FILE *file, float startX) {

    int ch;
    int lines = 0;
    int width, height;

    /* Process header (se débarrasse des lignes inutiles dans l'en-tête du fichier PPM) */
    while (lines < 4) { 

        if (lines == 2) {
            fscanf(file, "%d %d\n", &width, &height);
        } else {
            ch = fgetc(file); 
        }

        if (ch == '\n') { 
            lines++; 
        } 
    }

    /* Parcours du fichier PPM */

    int red, green, blue;
    float x = startX;
    int y = height - 1;

    BoundingBox *box = malloc(sizeof(BoundingBox)*width*height);
    if (!box) {
        printf("Erreur allocation\n");
        return NULL;
    }

    int k = 0;

    while (!feof(file)) {
        /* Récupère les données rvb pour chaque pixel */
        fscanf(file, "%d\n%d\n%d\n", &red, &green, &blue);

        /* Dessine chaque pixels */
        glBegin(GL_QUADS);
            glColor3ub(red, green, blue);
            glVertex2f(x, y);
            glVertex2f(x + 1, y);
            glVertex2f(x + 1, y + 1); 
            glVertex2f(x, y + 1);            
        glEnd();

        /* On recupère la position de chaque case non-blanche (les obstacles) pour créer les bounding box */
        if (red != 255 || green != 255 || blue != 255){
            box[k].pMinX = x;
            box[k].pMinY = y;
            box[k].pMaxX = x + 1;
            box[k].pMaxY = y + 1;
            box[k].end = 0;
            k++;
        }

        // Permet de tester la fin du tableau dans le main
        box[k].end = 1;

        /* Passe d'une colonne à une autre jusqu'à la fin de la ligne puis change de ligne une fois au bout */
        if (x == (width - 1) + startX) {
            y -= 1;
            x = startX;
        } else {
            x += 1;
        }
    }

    return box;

}