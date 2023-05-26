#include "algo.h"
#include "common.h"
#include "quicksort.h"
#include "scorematrice.h"

#include <ctime>

int valeurVert (int i, int j, instance g) // Renvoie le nombre de points généré par un pion vert placés aux coordonnées (i, j)
{
    int somme = g.matrice[i][j];

    if (i > 0) somme += g.matrice[i-1][j];
    if (i < g.taille-1) somme += g.matrice[i+1][j];
    if (j > 0) somme += g.matrice[i][j-1];
    if (j < g.taille-1) somme += g.matrice[i][j+1];
     
    return somme;
}

vector<vector <int>> maximum (vector <vector <float>> G) // Renvoie les coordonnées du maximum du tableau G
{
    int t = G[0].size();

    float m = -1;
    vector <vector <int>> r;

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (G[i][j] > m)
            {
                m = G[i][j];
            }
        }
    }

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (G[i][j] == m)
            {
                r.push_back({i, j});
            }
        }
    }
    
    return r;
}

void penaliteVert (vector <vector <int>> & G, int i, int j, int p) // Applique la pénalité p aux éléments adjacents & diagonaux de la case (i,j) dans la matrice G
{
    int t = G.size();

    if (i > 0) G[i-1][j] -= p;
    if (i < t-1) G[i+1][j] -= p;
    if (j > 0) G[i][j-1] -= p;
    if (j < t-1) G[i][j+1] -= p;

    if (i > 0 && j > 0) G[i-1][j-1] -= p;
    if (i > 0 && j < t-1) G[i-1][j+1] -= p;
    if (i < t-1 && j > 0) G[i+1][j-1] -= p;
    if (i < t-1 && j < t-1) G[i+1][j+1] -= p;
}

int moyenne (vector <vector <int>> N, vector <vector <char>> G) // Renvoie la moyenne des cases positives de N 
{
    int t = N.size();

    int somme = 0;

    int n = 0;
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (N[i][j] > 0 and G[i][j] == 'X')
            {
                somme += N[i][j];
                n++;
            }
        }
    }

    return somme/n;
}

vector<vector <int>> minimum (vector <vector <int>> g) // Renvoie les coordonnées du minimum du tableau G
{
    int t = g[0].size();

    float m = g[0][0];
    vector <vector <int>> r;

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (g[i][j] < m)
            {
                m = g[i][j];
            }
        }
    }

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (g[i][j] == m)
            {
                r.push_back({i, j});
            }
        }
    }
    
    return r;
}

vector <vector <char>> NVR (instance g) // Effectue le placement des pions noirs, verts puis jaunes
{
    int t = g.taille;

    vector <vector <char>> G;

    vector <char> tempchar;

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            tempchar.push_back('X');
        }
        G.push_back(tempchar);
        tempchar.clear();
    }

    vector <vector <int>> N;
    vector <vector <int>> V;
    vector <vector <float>> M;

    vector <int> tempint;

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (g.matrice[i][j]-1 > 0)
            {
                tempint.push_back((g.matrice[i][j]-1)*2);
            }
            else
            {
                tempint.push_back(-1);
            }
        }
        N.push_back(tempint);
        tempint.clear();
    }
    
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (valeurVert(i, j, g) >= 0)
            {
                tempint.push_back(valeurVert(i, j, g));
            }
            else
            {
                tempint.push_back(-1);
            }
        }
        V.push_back(tempint);
        tempint.clear();
    }

    vector <float> tempfloat;
    int nv = 0;

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (N[i][j] != -1 or V[i][j] != -1)
            {
                tempfloat.push_back(((float)N[i][j] + (float)V[i][j])/2);
                nv++;
            }
            else
            {
                tempfloat.push_back(-1);
            }
        }
        M.push_back(tempfloat);
        tempfloat.clear();
    }

    int n = 0;
    int p = g.penalite;
    do
    {
        vector <vector <int>> maxNV = maximum(M);
        for (unsigned int k = 0; k < maxNV.size(); ++k)
        {
            int i = maxNV[k][0], j = maxNV[k][1];

            int valN = N[i][j], valV = V[i][j];

            if (valN > valV  and valN > 0 and valN >= moyenne(N, G) and t > n)
            {
                G[i][j] = 'N';
                n++;
            }
            else if (valV > 0)
            {
                G[i][j] = 'V';
                penaliteVert(V, i, j, p);
            }
            else if (valV == 0 and g.matrice[i][j] < 0)
            {
                G[i][j] = 'V';
                penaliteVert(V, i, j, p);
            }
            nv--;
            M[i][j] = -1;
        }
    }
    while (nv > 0);
    vector <vector <int>> R;
    
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if ((G[i][j] == 'V' and g.matrice[i][j] < 0) or g.matrice[i][j] < 0)
            {
                tempint.push_back(g.matrice[i][j]);
            }
            else
            {
                tempint.push_back(1);
            }
        }
        R.push_back(tempint);
        tempint.clear();
    }

    vector <vector <int>> minR = minimum(R);
    int i = minR[0][0], j = minR[0][1];
    if (minR.size()-1 > 1)
    {
        int minV = V[i][j];
        for(unsigned int k = 1; k < minR.size(); ++k)
        {
            if (minV < V[minR[k][0]][minR[k][1]])
            {
                i = minR[k][0];
                j = minR[k][1];
            }
        }
    }
    G[minR[minR.size()-1][0]][minR[minR.size()-1][1]] = 'R';

    return G;
}

bool ligne_orange(vector <vector <char>> s,int l) // Renvoie un booléen vérifiant s'il y-a un pion orange dans la ligne l de s
{
    for (unsigned int i=0;i<s.size();++i)
    {
        if (s[l][i]=='O')return true;
    }
    return false;
}

bool colonne_orange(vector <vector <char>> s,int c) // Renvoie un booléen vérifiant s'il y-a un pion orange dans la colonne c de s
{
    for (unsigned int i=0;i<s.size();++i)
    {
        if (s[i][c]=='O')return true;
    }
    return false;
}

bool diagonale_orange(vector<char> diag) // Renvoie un booléen vérifiant s'il y-a un pion orange dans le vecteur diag
{
    for (unsigned int i=0;i<diag.size();++i)
    {
        if (diag[i]=='O')return true;
    }
    return false;
}

void echange (vector<int> &x, vector<int> &y)
{
    vector<int> z = x; x = y; y = z;
}

void tri_selection (vector<vector<int>> &v,int n) //Effectue le tri par séléction de la matrice v
{
    for (int i = n-1; i > 0; --i)
    {
        int p = 0;
        for (int j = 1; j <= i; ++j)
            if (v[j][0] > v[p][0])
                p = j;
        echange(v[p],v[i]);
    }
}

vector <vector <char>> O(instance g) // Effectue le placement des pions oranges
{
    vector <vector <char>> s = NVR(g);

    int t=g.taille;
    vector<vector<int>> negatif;
    int nb=0;
    for (int i=0;i<t;++i)
    {
        for (int j=0;j<t;++j)
        {
            if (g.matrice[i][j]<0)
            {
                negatif.push_back({g.matrice[i][j],i,j});
                nb++;
            }
           
        }
    }

    tri_selection(negatif,nb);

    for (int i=0;i<nb;++i)
    {
        int x=negatif[i][1];
        int y=negatif[i][2];
        vector<char> diag1, diag2;
        for (int k = 0; k < t; k++) 
        {
            int x1 = x - y + k;
            int x2 = x + y - k;
            if (x1 >= 0 && x1 < t) 
            {
                diag1.push_back(s[x1][k]);
            }
            if (x2 >= 0 && x2 < t) 
            {
                diag2.push_back(s[k][x2]);
            }
        }
        if (!diagonale_orange(diag1) && !diagonale_orange(diag2) && !ligne_orange(s,x) && !colonne_orange(s,y) && s[x][y]=='X') s[x][y]='O';
    }
    return s;
}

int difference (vector <vector <int>> toutx, instance g) //Renvoie la différence entre le nombre de positif et de négatif
{
    int d = 0;

    int n = 0;
    for (unsigned int i = 0; i < toutx.size(); ++i)
    {
        n = g.matrice[toutx[i][0]][toutx[i][1]];
        if (n > 0)
        {
            d++;
        }
        if (n < 0)
        {
            d--;
        }
    }

    return d;
}

vector <vector <int>> vide (vector <vector <char>> s, instance g) //Renvoie un vecteur contenant les coordonées des cases vides de s
{
    int t = s.size();

    vector <vector <int>> x;

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (s[i][j] == 'X' and g.matrice[i][j] != 0)
            {
                x.push_back({i, j});
            }
        }
    }

    return x;
}

vector <vector <int>> minimumx (vector <vector <int>> x, instance g) // Renvoie un vecteur contenant le minimum et ses coordonées du vecteur x
{

    int t = x.size();

    vector < vector <int>> m;

    vector <int> temp;
    for (int i = 0; i < t; ++i)
    {
        if (g.matrice[x[i][0]][x[i][1]] < 0)
        {
            m.push_back({g.matrice[x[i][0]][x[i][1]], x[i][0], x[i][1]});
        }
    }
    quicksort(m, 0, m.size()-1);
    return m;
}

vector <vector <int>> maximumx (vector <vector <int>> x, instance g) // Renvoie un vecteur contenant le maxium et ses coordonées du vecteur x
{

    int t = x.size();

    vector < vector <int>> m;

    vector <int> temp;
    for (int i = 0; i < t; ++i)
    {
        if (g.matrice[x[i][0]][x[i][1]] >= 0)
        {
            m.push_back({g.matrice[x[i][0]][x[i][1]], x[i][0], x[i][1]});
        }
    }
    quicksort(m, 0, m.size()-1);
    return m;
}

bool adjacentOrtho (int i, int j, int x, int y, int t) // Renvoie un booléen qui indique si les cases (i,j) et (x,y) sont adjacente orthogonalement
{
	bool coordx = false;
	bool coordy = false;
	if (x == i) coordx = true;
	if (x+1 == i && x < t-1) coordx = true;
	if (x-1 == i && x > 0) coordx = true;

	if (y == j) coordy = true;
	if (y+1 == j && y < t-1) coordy = true;
	if (y-1 == j && y > 0) coordy = true;

    return (coordx and coordy);
}

bool adjacentDiago (int i, int j, int x, int y, int t) // Renvoie un booléen qui indique si les cases (i,j) et (x,y) sont adjacente diagonalement
{
	if (x+1 == i && y+1 == j && y < t-1 && x < t-1) return true;
	if (x+1 == i && y-1 == j && y > 0 && x < t-1) return true;
	if (x-1 == i && y-1 == j && y > 0 && x > 0) return true;
	if (x-1 == i && y+1 == j && y < t-1 && x > 0) return true;

    return false;
}

bool adjacent (int i, int j, vector <vector <int>> jaune, int t) // Renvoie un booléen qui indique si la case (i,j) est adjacente (orthogonalement ou diagonalement) aux coordonnées contenu dans le vecteur jaune
{
    bool r = false;
    int x = jaune[0][0], y = jaune[0][1];
    for (unsigned int k = 0; k < jaune.size(); ++k)
    {
        x = jaune[k][0];
        y = jaune[k][1];
        if (adjacentDiago(i, j, x, y, t) or adjacentOrtho(i, j, x, y, t))
        {
            r = true;
        }
    }

    return r;
}

void suppx (vector <vector <int>> & x, int i, int j) // Supprime toutes les occurences des coordonnées (i,j) dans le vecteur x
{
    for (unsigned int k = 0; k < x.size(); ++k)
    {
        if (x[k] == vector <int> {i, j})
        {
            x.erase(x.begin() + k);
        }
    }
}

int max (vector <vector <int>> jaune) // Renvoie l'indice du maximum contenu dans jaune
{
    int indice = 0, m = jaune[indice][2];

    for (unsigned int i = 0; i < jaune.size(); ++i)
    {
        if (jaune[i][2] > m)
        {
            m = jaune[i][2];
            indice = i;
        }
    }
    return indice;
}

void retour (vector <vector <int>> & jaune) // Revient sur le meilleur pivot de la grille
{
    int pivot = jaune.size()-1;

    do
    {
        pivot = max(jaune);
    } while ((jaune[pivot][5] != 0 and jaune[pivot][4] > 0) and (pivot == 0 and jaune[pivot][4] < 0));

    jaune.resize(pivot);
}

vector <vector <char>> B (vector <vector <char>> s) // Effectue le placement des pions bleu
{
    int t = s.size();

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (s[i][j] == 'X')
            {
                s[i][j] = 'B';
            }
        }
    }

    return s;
}

vector <vector <char>> J(vector <vector <char>> s, instance g, int n) // Effectue le placement des pions jaune
{
    vector <vector <char>> r = s;
    vector <vector <int>> toutx;
    vector <vector <int>> minx;
    vector <vector <int>> maxx;
    vector <vector <int>> jaune;
    int d;
    
    toutx = vide(r, g);
    d = difference(toutx, g);

    minx =  minimumx(toutx, g);
    maxx =  maximumx(toutx, g);
    int x, y;
    if (minx.size() > 0)
    {
        x = minx[0+n][1];
        y = minx[0+n][2];
        jaune = {{x, y, g.matrice[x][y] - g.penalite, -g.penalite, g.matrice[x][y], d}};
    }
    else
    {
        x = maxx[0][1];
        y = maxx[0][2];
        jaune = {{x, y, g.matrice[x][y] - g.penalite, 0, g.matrice[x][y] - g.penalite, d}};
    }
    suppx(toutx, x, y);

    int i = 0;
    while (toutx.size() > 0)
    {
        minx =  minimumx(toutx, g);
        maxx =  maximumx(toutx, g);

        d = difference(toutx, g);

        if (d < 0)
        {
            vector <vector <int>> temp;
            int meilleur = -1;;
            do
            {
                meilleur++;
                temp.push_back({minx[meilleur][1], minx[meilleur][2], jaune[i][2] + minx[meilleur][0] + (i == 0 ? g.penalite : 0), jaune[i][3] + - g.penalite, jaune[i][2] + minx[meilleur][0] - jaune[i][3] + g.penalite, d});      
            } while (!adjacent(temp[meilleur][0], temp[meilleur][1], jaune, g.taille) and (unsigned int)meilleur+1 < minx.size());

            jaune.push_back(temp[meilleur]);
            suppx(toutx, minx[meilleur][1], minx[meilleur][2]);
        }
        else
        {
            vector <vector <int>> temp;
            int meilleur = -1;
            do
            {
                meilleur++;
                temp.push_back({maxx[meilleur][1], maxx[meilleur][2], jaune[i][2] + maxx[meilleur][0] + (i == 0 ? g.penalite : 0), jaune[i][3], jaune[i][2] + maxx[meilleur][0] - jaune[i][3], d}); 
            } while (!adjacent(temp[meilleur][0], temp[meilleur][1], jaune, g.taille) and (unsigned int)meilleur+1 < maxx.size());
            
            jaune.push_back(temp[meilleur]);
            suppx(toutx, maxx[meilleur][1], maxx[meilleur][2]);
        }
        i++;
    }

    retour(jaune);

    for (unsigned int i = 0; i < jaune.size(); ++i)
    {
        r[jaune[i][0]][jaune[i][1]] = 'J';
    }

    return r;
}

int lastd (vector <vector <char>> s, instance g) //Compte la différence entre le nombre de case positive et négative, là où les pions bleu sont placés
{
    int d = 0, n = 0;

    int t = s.size();
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            n = g.matrice[i][j];
            if (s[i][j] == 'B')
            {
                if (n < 0)
                {
                    d--;
                }
                if (n > 0)
                {
                    d++;
                }
            }
        }
    }
    
    return d;
}

float temps (clock_t depart, clock_t breakpoint)
{
    return (0.0 + (breakpoint-depart)/ CLOCKS_PER_SEC);
}

vector <vector <char>> BJ (instance g)
{
    clock_t depart = clock();
    clock_t dernierbreackpoint = 0;
    clock_t breackpoint = 0;
    clock_t chrono = depart;
    clock_t chronomax = 55; //55 secondes
    vector <vector <char>> s = O(g);

    vector <vector <tuple <int, vector <vector <char>>>>> solutions;
    
    bool stop = false;
    unsigned int i = 0;
    do
    {
        dernierbreackpoint = breackpoint / CLOCKS_PER_SEC;
        solutions.push_back({make_tuple(calculeScoreMatrice(s, g), s)});

        bool premier = true;
        do
        {
            breackpoint = clock();
            chrono = temps(depart, breackpoint);

            vector <vector <char>> tempsolution = J(get<1>(solutions[i][solutions[i].size()-1]), g, (premier ? (int)i : 0));
            int tempscore = calculeScoreMatrice(B(tempsolution), g);

            premier = false;
            solutions[i].push_back(make_tuple(tempscore, tempsolution));
        } while (get<1>(solutions[i][solutions[i].size()-1]) != get<1>(solutions[i][solutions[i].size()-2]));


        solutions[i].erase(solutions[i].begin());
        solutions[i].erase(solutions[i].end());

        for (unsigned int j = 0; j < solutions[i].size(); ++j)
        {
            get<1>(solutions[i][j]) = B(get<1>(solutions[i][j]));
        }
        quicksort2(solutions[i], 0, solutions[i].size()-1);
        i++;
        
        if (chrono + dernierbreackpoint > chronomax)
        {
            stop = true;
        }
        
        if (stop)
        {
            i = minimumx(vide(s, g), g).size();
        }
    } while (i < minimumx(vide(s, g), g).size());
    
    int indice = 0, max = get<0>(solutions[indice][0]);
    for (unsigned int i = 0; i < solutions.size(); ++i)
    {
        if (get<0>(solutions[i][0]) > max)
        {
            max = get<0>(solutions[i][0]);
            indice = i;
        }
    }
    
    return get<1>(solutions[indice][0]);
}

vector <vector <char>> Boptimal (instance g)
{
    int t = g.taille;

    vector <vector <char>> s = BJ(g);
    vector <vector <int>> v = g.matrice;

    vector <vector <int>> toutnv;

    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            if (s[i][j] == 'N' and g.matrice[i][j] > 0)
            {
                toutnv.push_back({(g.matrice[i][j]-1)*2, i, j});
            }
            else if (s[i][j] == 'V' and g.matrice[i][j] > 0)
            {
                toutnv.push_back({valeurVert(i, j, g), i, j});
                penaliteVert(v, i, j, g.penalite);
            }
        }
    }

    quicksort3(toutnv, 0, toutnv.size()-1);

    int i = 0;
    while (i < -lastd(s, g) and toutnv.size() > 0)
    {
        if (toutnv[i][0] < g.penalite)
        {
            s[toutnv[i][1]][toutnv[i][2]] = 'B';
        }
        ++i;
    }

    return s;
}