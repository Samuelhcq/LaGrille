#pragma once
#include "structure.h"

bool pionOrthogonal (vector <vector <char>> s, char l, unsigned int i, unsigned int j);
bool pionDiagonale (vector <vector <char>> s, char l, unsigned int i, unsigned int j);
int compteurPions (vector <vector <char>> s, char l);
int absmatrice (int x);
int pionsBleus (vector <vector <char>> s, instance g);
int pionRouge (vector <vector <char>> s, instance g);
int pionsNoirs (vector <vector <char>> s, instance g);
tuple<int, int> pionsJaunes (vector <vector <char>> s, instance g);
tuple<int, int> pionsVerts (vector <vector <char>> s, instance g);
long long int factorielmatrice (int x);
float binomialDe2matrice (int n);
bool pionOrthogonalOrange (vector <vector <unsigned int>>paire , vector <vector <char>> s);
bool pionDiagonalOrange (vector <vector <unsigned int>> paire, vector <vector <char>> s);
int pionsOranges (vector <vector <char>> s, instance g);
int calculeScoreMatrice (vector <vector <char>> s, instance g);