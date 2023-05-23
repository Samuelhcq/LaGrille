#pragma once
#include "structure.h"

vector<tuple<int,int>> max_vecteur(instance g,int d); //Retourne les coordonnées des d plus grandes valeur d'une instance
void afficher_vector(vector<tuple<int,int>> v);
tuple<int,int> coordmin(instance g);
tuple<int,int> valMax_adjacents(instance g,int x,int y);
vector<vector<char>> diagonales(solution s, int co_x, int co_y);
void affiche_diagonale(vector<char> matrice);
bool ligne_orangeSolution(solution s,int l);
bool colonne_orangeSolution(solution s,int c);
bool diagonale_orangeSolution(vector<char> diag);
solution GenereSolution1(instance g);
solution genere_voisin(solution s, instance g);