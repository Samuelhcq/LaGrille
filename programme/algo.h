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
vector <vector <char>> O(instance g);

int difference (vector <vector <int>> toutx, instance g);
bool adjacent (int i, int j, vector <vector <int>> jaune, int t);
bool adjacentDiago (int i, int j, int x, int y, int t);
bool adjacentOrtho (int i, int j, int x, int y, int t);
vector <vector <int>> maximumx (vector <vector <int>> x, instance g);
vector <vector <int>> minimumx (vector <vector <int>> x, instance g);
vector <vector <int>> vide (vector <vector <char>> s, instance g);
void suppx (vector <vector <int>> & x, int i, int j);
int max (vector <vector <int>> jaune);
void retour (vector <vector <int>> & jaune);
vector <vector <char>> B (vector <vector <char>> s);
vector <vector <char>> J(vector <vector <char>> stemp, instance g, int n);
int lastd (vector <vector <char>> s, instance g);
vector <vector <char>> BJ (instance g);
vector <vector <char>> Boptimal (instance g);