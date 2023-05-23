#pragma once
#include "structure.h"

int valeurVert (int i, int j, instance g);
vector<vector <int>> maximum (vector <vector <float>> G);
void penaliteVert (vector <vector <int>> & G, int i, int j, int p);
int moyenne (vector <vector <int>> N, vector <vector <char>> G);
vector<vector <int>> minimum (vector <vector <int>> g);
vector <vector <char>> NVR (instance g);
bool ligne_orange(vector <vector <char>> s,int l);
bool colonne_orange(vector <vector <char>> s,int c);
bool diagonale_orange(vector<char> diag);
void echange (vector<int> &x, vector<int> &y);
void tri_selection (vector<vector<int>> &v,int n);
vector <vector <char>> placement_orange(instance g);