#include "algo.h"
#include "common.h"

int valeurVert (int i, int j, instance g)
{
    int somme = g.matrice[i][j];

    if (i > 0) somme += g.matrice[i-1][j];
    if (i < g.taille-1) somme += g.matrice[i+1][j];
    if (j > 0) somme += g.matrice[i][j-1];
    if (j < g.taille-1) somme += g.matrice[i][j+1];
     
    return somme;
}

vector<vector <int>> maximum (vector <vector <float>> G)
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

void penaliteVert (vector <vector <int>> & G, int i, int j, int p)
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

int moyenne (vector <vector <int>> N, vector <vector <char>> G)
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

vector<vector <int>> minimum (vector <vector <int>> g)
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

vector <vector <char>> NVR (instance g)
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

    // cout << "N : " << endl;
    // for (int i = 0; i < t; ++i)
    // {
    //     for (int j = 0; j < t; ++j)
    //     {
    //         cout << N[i][j] << "\t";
    //     }
    //     cout << endl;
    // }

    // cout << "M : " << endl;
    // for (int i = 0; i < t; ++i)
    // {
    //     for (int j = 0; j < t; ++j)
    //     {
    //         cout << M[i][j] << "\t";
    //     }
    //     cout << endl;
    // }

    // cout << endl << endl << endl;

    int n = 0;
    int p = g.penalite;
    do
    {
        // cout << "N : " << endl;
        // for (int i = 0; i < t; ++i)
        // {
        //     for (int j = 0; j < t; ++j)
        //     {
        //         cout << N[i][j] << "\t";
        //     }
        //     cout << endl;
        // }
        
        // cout << "V : " << endl;
        // for (int i = 0; i < t; ++i)
        // {
        //     for (int j = 0; j < t; ++j)
        //     {
        //         cout << V[i][j] << "\t";
        //     }
        //     cout << endl;
        // }

        vector <vector <int>> maxNV = maximum(M);
        for (unsigned int k = 0; k < maxNV.size(); ++k)
        {
            int i = maxNV[k][0], j = maxNV[k][1];

            int valN = N[i][j], valV = V[i][j];

            if (valN > valV  and valN > 0 and valN >= moyenne(N, G) and t > n)
            {
                G[i][j] = 'N';
                // cout << 'N' << ' ' << valN << '>' << valV << endl;
                n++;
            }
            else if (valV > 0)
            {
                G[i][j] = 'V';
                // cout << 'V'  << ' ' << valV << '>' << valN << endl;
                penaliteVert(V, i, j, p);
            }
            else if (valV == 0 and g.matrice[i][j] < 0)
            {
                G[i][j] = 'V';
                // cout << 'V'  << ' ' << valV << '>' << valN << endl;
                penaliteVert(V, i, j, p);
            }
            // else cout << 'X' << i << ' ' << j << endl;
            nv--;
            M[i][j] = -1;
        }
    }
    while (nv > 0);
    
    // for (int i = 0; i < t; ++i)
    // {
    //     for (int j = 0; j < t; ++j)
    //     {
    //         cout << G[i][j] << "\t";
    //     }
    //     cout << endl;
    // }

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

    // for (int i = 0; i < t; ++i)
    // {
    //     for (int j = 0; j < t; ++j)
    //     {
    //         cout << R[i][j] << "\t";
    //     }
    //     cout << endl;
    // }

    vector <vector <int>> minR = minimum(R);
    
    int i = minR[0][0], j = minR[0][1];
    if (minR.size() > 1)
    {
        int minV = V[i][j];
        for(unsigned int k = 1; k < minR.size(); ++k)
        {
            if (minV < V[minR[k][0]][minR[k][1]])
            {
                i = k;
                j = k;
            }
        }
    }
    G[i][j] = 'R';

    // for (int i = 0; i < t; ++i)
    // {
    //     for (int j = 0; j < t; ++j)
    //     {
    //         cout << G[i][j] << "\t";
    //     }
    //     cout << endl;
    // }

    return G;
}

bool ligne_orange(vector <vector <char>> s,int l)
{
    for (unsigned int i=0;i<s.size();++i)
    {
        if (s[l][i]=='O')return true;
    }
    return false;
}

bool colonne_orange(vector <vector <char>> s,int c)
{
    for (unsigned int i=0;i<s.size();++i)
    {
        if (s[i][c]=='O')return true;
    }
    return false;
}

bool diagonale_orange(vector<char> diag)
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

void tri_selection (vector<vector<int>> &v,int n)
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

vector <vector <char>> placement_orange(instance g)
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