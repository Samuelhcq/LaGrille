#pragma once
#include "structure.h"

struct calquesNV
{
    vector <tuple <string, vector <vector <vector <float>>>>> matrice;
};

struct calques
{
    vector <tuple <char, vector <vector <vector <int>>>>> matrice;
};

bool valide (solution s);
void genereSolutionAlea (solution & s, instance g);
void saisieSolution (solution & s, instance g);
void lectureSolution (string ficA, solution & s, instance g);
void genereCalques (calques & c, instance g);
void genereCalquesNV (calquesNV & c, instance g);
int adjacentVert (int i, int j, instance g);
void afficheCalque (calques c, calquesNV cNV, instance g);