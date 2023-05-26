#include "scorematrice.h"
#include "common.h"

bool pionOrthogonal (vector <vector <char>> s, char l, unsigned int i, unsigned int j) //Vérifie les pions adjacents orthogonalements
{
    if (j > 0 && s[i][j-1] == l) return true; //A gauche
    if ((unsigned int)j < s.size()-1 && s[i][j+1] == l) return true; //A droite
    if (i > 0 && s[i-1][j] == l) return true; //En dessous
    if ((unsigned int)i < s.size()-1 && s[i+1][j] == l) return true; //Au dessus
    return false;
}

bool pionDiagonale (vector <vector <char>> s, char l, unsigned int i, unsigned int j) //Vérifie les pions adjacents en diagonale
{
    if (i > 0 && j > 0 && s[i-1][j-1] == l) return true; //En bas à gauche
    if (i > 0 && j < s.size()-1 && s[i-1][j+1] == l) return true; //En bas à droite
    if (i < s.size()-1 && j > 0 && s[i+1][j-1] == l) return true; //En haut à gauche
    if (i < s.size()-1 && j < s.size()-1 && s[i+1][j+1] == l) return true; //En haut à droite
    
    return false;
}

int compteurPions (vector <vector <char>> s, char l) //Compte le nombre d'une certaine couleur de pion
{
    int compteur = 0;
    for (unsigned int i = 0; i < s.size(); ++i)
    {
        for (unsigned int j = 0; j < s.size(); ++j)
        {
            if (s[i][j%s.size()] == l) compteur++;
        }
    }
    return compteur;
}

int absmatrice (int x) //Calcule la valeur absmatriceolue (utilsé dans la fonction pionsBleus)
{
    if(x >= 0) return x;
    return -x;
}

int pionsBleus (vector <vector <char>> s, instance g) //Calcule le score des pions bleus
{
    int d = 0, val;
    unsigned int t = s.size();
    for (unsigned int i = 0; i < t; ++i)
    {
        for (unsigned int j = 0; j < t; ++j)
        {
            val = g.matrice[i][j];
            if (s[i][j] == 'B')
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

int pionRouge (vector <vector <char>> s, instance g) //Calcule le score du pion rouge
{
    int i = 0, j = 0;
    unsigned int t = s.size();
    bool pionRouge = false;
    while (!pionRouge and (unsigned int)i < t)
    {
        do
        {
            if (s[i][j++] == 'R') pionRouge = true;
        }
        while (!pionRouge and (unsigned int)j < t);

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

int pionsNoirs (vector <vector <char>> s, instance g) //Calcule le score des pions noirs
{
    int nbPionNoir = 0, score = 0;
    unsigned int t = s.size();
    for (unsigned int i = 0; i < t; ++i)
    {
        for (unsigned int j = 0; j < t; ++j)
        {
            if (s[i][j] == 'N')
            {
                score += g.matrice[i][j];
                nbPionNoir++;
            }
        }
    }
    if ((unsigned int)nbPionNoir <= t) return 2*(score-nbPionNoir);
    return score-nbPionNoir;
}


tuple<int, int> pionsJaunes (vector <vector <char>> s, instance g) //Calcule le score des pions jaunes
{
    int score = 0, nbPionsIsole = 0;
    unsigned int t = s.size();
    for (unsigned int i = 0; i < t; ++i)
    {
        for (unsigned int j = 0; j < t; ++j)
        {
            if (s[i][j] == 'J')
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


tuple<int, int> pionsVerts (vector <vector <char>> s, instance g) //Calcule le score des pions verts
{
    int score = 0, nbPaire = 0;
    unsigned int t = s.size();
    for (unsigned int i = 0; i < t; ++i)
    {
        for (unsigned int j = 0; j < t; ++j)
        {
            if (s[i][j] == 'V')
            {
                score += g.matrice[i][j];
                //Ajout de la valeur des cases adjecentes orthogonalement
                if (j > 0) score += g.matrice[i][j-1]; //En dessous
                if (j < s.size()-1) score += g.matrice[i][j+1]; //Au dessus
                if (i > 0) score += g.matrice[i-1][j]; //A gauche
                if (i < s.size()-1) score += g.matrice[i+1][j]; //A droite

                //Calcule du nombre de paire
                //Ajout du nombre de paire orthogonalement
                if (j > 0 && s[i][j-1] == 'V') nbPaire++; //En dessous
                if (i < s.size()-1 && s[i+1][j] == 'V') nbPaire++; //A droite
                //Ajout du nombre de paire en diagonale
                if (i > 0 && j > 0 && s[i-1][j-1] == 'V') nbPaire++; //En bas à gauche
                if (i > 0 && j < s.size()-1 && s[i-1][j+1] == 'V') nbPaire++; //En bas à droite
            }
        }
    }
    return make_tuple(score, nbPaire);
}

long long int factorielmatrice (int x) //Calcule la factorielmatrice de x (utile pour binomialDe2matrice())
{
    long long int result = 1;

    for (int i = 2; i <= x; ++i)
    {
        result *= i;
    }

    return result;
}

float binomialDe2matrice (int n) //Calcule le coefficient binomiale (n parmis 2)
{
    return factorielmatrice(n)/(factorielmatrice(n-2)*factorielmatrice(2));
}

bool pionOrthogonalOrange (vector <vector <unsigned int>> paire, vector <vector <char>> s) //Vérifie les pions orthogonalement
{
    if (paire[0][1] == paire[1][1]) return true;  //En dessous
    if (paire[0][0] == paire[1][0]) return true; //A droite
    
    return false;
}

bool pionDiagonalOrange (vector <vector <unsigned int>> paire, vector <vector <char>> s) //Vérifie les pions en diagonale
{
    int difference = paire[1][1] - paire[0][1];
    
    if (paire[0][0] == paire[1][0]-difference && paire[0][1] == paire[1][1]-difference) return true; //En bas à droite
    if (paire[0][0] == paire[1][0]+difference && paire[0][1] == paire[1][1]-difference) return true; //En bas à gauche
    
    return false;
}

int pionsOranges (vector <vector <char>> s, instance g) //Calcule score pions oranges
{
    int nbPionOrange = 0;
    unsigned int t = s.size();
    vector <vector <unsigned int>> position;
    vector <unsigned int> temp;
    for (unsigned int i = 0; i < t; ++i)
    {
        for (unsigned int j = 0; j < t; ++j)
        {
            temp.clear();
            if (s[i][j] == 'O')
            {
                temp = {i, j};
                position.push_back(temp);
                nbPionOrange++;
            }
        }
    }
    if (nbPionOrange >= 2)
    {
        float nbPairePossible = binomialDe2matrice(nbPionOrange);
        int nbPaire = 0;
        vector <vector <vector <unsigned int>>> paireOrange;
        vector <vector <unsigned int>> temp;
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
        return nbPaire;
    }
    return 0;
}

int calculeScoreMatrice (vector <vector <char>> s, instance g) //Calcule du score final
{
    int score = 0, nbPenalite = 0;
    int tempScore = 0, tempNbPenalite = 0;
    nbPenalite += pionsBleus (s, g);
    score += pionRouge (s, g);
    score += pionsNoirs (s, g);
    tie(tempScore, tempNbPenalite) = pionsJaunes(s, g);
    score += tempScore; nbPenalite += tempNbPenalite;
    tie(tempScore, tempNbPenalite) = pionsVerts(s, g);
    score += tempScore; nbPenalite += tempNbPenalite;
    nbPenalite += pionsOranges(s, g);
    return (score - (nbPenalite * g.penalite));
}