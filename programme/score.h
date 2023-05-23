#pragma once
#include "structure.h"

bool pionOrthogonal (solution s, char l, int i, int j);
bool pionDiagonale (solution s, char l, int i, int j);
int compteurPions (solution s, char l);
int abs (int x);
int pionsBleus (solution s, instance g);
int pionRouge (solution s, instance g);
int pionsNoirs (solution s, instance g);
tuple<int, int> pionsJaunes (solution s, instance g);
tuple<int, int> pionsVerts (solution s, instance g);
long long int factoriel (int x);
float binomialDe2 (int n);
bool pionOrthogonalOrange (vector <vector <int>> paire, solution s);
bool pionDiagonalOrange (vector <vector <int>> paire, solution s);
int pionsOranges (solution s, instance g);
void calculeScore (solution & s, instance g);