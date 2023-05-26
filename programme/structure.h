#pragma once
#include "common.h"

//Déclaration des structures de données d'entrée et de sortie
struct instance
{
    int taille, penalite;
    vector <vector <int>> matrice;
};

struct solution
{
    int taille, score;
    vector <vector <char>> matrice;
};

void initialisationInstance (string ficA, instance & g);
void affichageInstance (instance g);
void affichageSolution (solution s);
void ecriture (string ficA, solution s);
bool valide (solution s);