#include "score.h"
#include "common.h"

bool pionOrthogonal (solution s, char l, int i, int j) //Vérifie les pions adjacents orthogonalements
{
    if (j > 0 && s.matrice[i][j-1] == l) return true; //A gauche
    if (j < s.taille-1 && s.matrice[i][j+1] == l) return true; //A droite
    if (i > 0 && s.matrice[i-1][j] == l) return true; //En dessous
    if (i < s.taille-1 && s.matrice[i+1][j] == l) return true; //Au dessus
    return false;
}

bool pionDiagonale (solution s, char l, int i, int j)  //Vérifie les pions adjacents en diagonale
{
    if (i > 0 && j > 0 && s.matrice[i-1][j-1] == l) return true; //En bas à gauche
    if (i > 0 && j < s.taille-1 && s.matrice[i-1][j+1] == l) return true; //En bas à droite
    if (i < s.taille-1 && j > 0 && s.matrice[i+1][j-1] == l) return true; //En haut à gauche
    if (i < s.taille-1 && j < s.taille-1 && s.matrice[i+1][j+1] == l) return true; //En haut à droite
    return false;
}

int compteurPions (solution s, char l) //Compte le nombre d'une certaine couleur de pion
{
    int compteur = 0;
    for (int i = 0; i < s.taille; ++i)
    {
        for (int j = 0; j < s.taille; ++j)
        {
            if (s.matrice[i][j%s.taille] == l) compteur++;
        }
    }

    return compteur;
}

int abs (int x) //Calcule la valeur absolue (utilsé dans la fonction pionsBleus)
{
    if(x >= 0) return x;
    return -x;
}

int pionsBleus (solution s, instance g) //Calcule le score des pions bleus
{
    int d = 0, val, t = s.taille;
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            val = g.matrice[i][j];

            if (s.matrice[i][j] == 'B')
            {
                if (val > 0)
                {
                    d--;
                }
                if (val < 0) 
                {   
                    d++;
                }
            }
        }
    }
    
    if (d > 0) return d;
    return 0;
}

int pionRouge (solution s, instance g) //Calcule le score du pion rouge
{
    int i = 0, j = 0, t = s.taille;
    bool pionRouge = false;

    while (!pionRouge and i < t)
    {
        do
        {
            if (s.matrice[i][j++] == 'R')pionRouge = true;
        }
        while (!pionRouge and j < t);
        if (!pionRouge)
        {
            j = 0;
            ++i;
        }
    }

    j--;


    int valPion = g.matrice[i][j];
    return -valPion;
}

int pionsNoirs (solution s, instance g) //Calcule le score des pions noirs
{
    int nbPionNoir = 0, score = 0, t = s.taille;

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (s.matrice[i][j] == 'N')
            {
                score += g.matrice[i][j];
                nbPionNoir++;
            }
        }
    }
    if (nbPionNoir <= t) return 2*(score-nbPionNoir);
    return score-nbPionNoir;

}

tuple<int, int> pionsJaunes (solution s, instance g) //Utilise les tuples (avec le module 'tuple')
{
    int score = 0, nbPionsIsole = 0, t = s.taille;

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (s.matrice[i][j] == 'J')
            {
                score += g.matrice[i][j];
                if (!(pionOrthogonal(s, 'J', i, j) or pionDiagonale(s, 'J', i, j)))
                {
                    nbPionsIsole++;
                    j++;
                }
            }
        }
    }
    return make_tuple(score, nbPionsIsole);
}


tuple<int, int> pionsVerts (solution s, instance g) //Calcule le score des pions verts
{
    int score = 0, nbPaire = 0, t = s.taille;
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (s.matrice[i][j] == 'V')
            {
                score += g.matrice[i][j];
                //Ajout de la valeur des cases adjacentes orthogonalement
                if (j > 0) score += g.matrice[i][j-1]; //En dessous
                if (j < s.taille-1) score += g.matrice[i][j+1]; //Au dessus
                if (i > 0) score += g.matrice[i-1][j]; //A gauche
                if (i < s.taille-1) score += g.matrice[i+1][j]; //A droite

                //Ajout du nombre de paire orthogonalement
                if (j > 0 && s.matrice[i][j-1] == 'V') nbPaire++; //En dessous
                if (i < s.taille-1 && s.matrice[i+1][j] == 'V') nbPaire++; //A droite

                //Ajout du nombre de paire en diagonale
                if (i > 0 && j > 0 && s.matrice[i-1][j-1] == 'V') nbPaire++; //En bas à gauche
                if (i > 0 && j < s.taille-1 && s.matrice[i-1][j+1] == 'V') nbPaire++; //En bas à droite
            }
        }
    }
    return make_tuple(score, nbPaire);
}

long long int factoriel (int x) //Calcule la factoriel de x (utile pour binomialDe2())
{
    long long int result = 1;

    for (int i = 2; i <= x; ++i)
    {
        result *= i;
    }

    return result;
}

float binomialDe2 (int n) //Calcule le coefficient binomiale (n parmis 2)
{
    return factoriel(n)/(factoriel(n-2)*factoriel(2));
}

bool pionOrthogonalOrange (vector <vector <int>> paire, solution s) //Vérifie les pions orthogonalement
{
    if (paire[0][1] == paire[1][1]) return true;  //En dessous
    if (paire[0][0] == paire[1][0]) return true; //A droite
    
    return false;
}

bool pionDiagonalOrange (vector <vector <int>> paire, solution s) //Vérifie les pions en diagonale
{
    int difference = paire[1][1] - paire[0][1];
    
    if (paire[0][0] == paire[1][0]-difference && paire[0][1] == paire[1][1]-difference) return true; //En bas à droite
    if (paire[0][0] == paire[1][0]+difference && paire[0][1] == paire[1][1]-difference) return true; //En bas à gauche
    
    return false;
}

int pionsOranges (solution s, instance g) //Calcule score pions oranges
{
    int t = s.taille, nbPionOrange = 0;
    vector <vector <int>> position;
    vector <int> temp;
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            temp.clear();
            if (s.matrice[i][j] == 'O')
            {
                temp = {i, j};
                position.push_back(temp);
                nbPionOrange++;
            }
        }
    }
    if (nbPionOrange >= 2)
    {
        float nbPairePossible = binomialDe2(nbPionOrange);
        int nbPaire = 0;
        vector <vector <vector <int>>> paireOrange;
        vector <vector <int>> temp;
        for (int j = 0; j < nbPionOrange-1; ++j)
        {
            temp.clear();
            for (int h = j+1; h < nbPionOrange; ++h)
            {
                temp = {{position[j][0], position[j][1]}, {position[h][0], position[h][1]}};
                paireOrange.push_back(temp);
            }
        }
        for (int i = 0; i < nbPairePossible; ++i)
        {
            if (pionDiagonalOrange(paireOrange[i], s) or pionOrthogonalOrange(paireOrange[i], s)) nbPaire++; 
        }

        // Debug cout << "Score pions oranges : " << nbPaire * g.penalite << "\tParamètres : " << "nombre de paire possible(C(" << nbPionOrange << ", 2))=" << nbPairePossible << "\t, nombre de paire(nombre de pénalité)=" << nbPaire << endl;    
        return nbPaire;
    }
    
    //Débuggage
    // cout << "Score pions oranges : " << 0 << "\tParamètres : " << "nombre de paire possible(C(1, 2))= {}" << endl;
    
    return 0;
}

void calculeScore (solution & s, instance g) //Calcule du score final
{
    int score = 0, nbPenalite = 0;
    int tempScore = 0, tempNbPenalite = 0;

    //Calcule du score
    nbPenalite += pionsBleus (s, g);
    score += pionRouge (s, g);
    score += pionsNoirs (s, g);
    tie(tempScore, tempNbPenalite) = pionsJaunes(s, g);
    score += tempScore; nbPenalite += tempNbPenalite;
    tie(tempScore, tempNbPenalite) = pionsVerts(s, g);
    score += tempScore; nbPenalite += tempNbPenalite;
    nbPenalite += pionsOranges(s, g);
    s.score = score - (nbPenalite * g.penalite);
}