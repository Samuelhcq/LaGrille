#include "algo2.h"
#include "score.h"
#include "autre.h"
#include "common.h"

vector<tuple<int,int>> max_vecteur(instance g,int d) //Retourne les coordonnées des d plus grandes valeur d'une instance
{
    vector<tuple<int,int>> rep;
    int compteur=0;
    while(compteur < d)
    {
        int valmax=g.matrice[0][0],imax=0,jmax=0;
        for (int i=0;i<g.taille;++i)
        {
            for (int j=0;j<g.taille;++j)
            {
                if (g.matrice[i][j]>valmax)
                {
                    valmax=g.matrice[i][j];
                    imax=i;
                    jmax=j;
                }
            }
        }
        rep.push_back(make_tuple(imax,jmax));
        ++compteur;
        g.matrice[imax][jmax]=-1;
    }
    return rep;
}

void afficher_vector(vector<tuple<int,int>> v) {
    for (unsigned int i=0;i<v.size();++i) 
    {
        cout << "(" << get<0>(v[i]) << ", " << get<1>(v[i]) << ") ";
    }
    cout << endl;
}

tuple<int,int> coordmin(instance g)
{
    int valmin=g.matrice[0][0],taille=g.taille,xmin=0,ymin=0;

    for (int i=0;i<taille;++i)
    {
        for (int j=0;j<taille;++j)
        {
            if (g.matrice[i][j]<valmin)
            {
                valmin=g.matrice[i][j];
                xmin=i;
                ymin=j;
            }
        }
    }
    return make_tuple(xmin,ymin);
}

tuple<int,int> valMax_adjacents(instance g,int x,int y)
{
    int valMax,xMax,yMax;
    for (int i = x-1; i <= x+1; i++)
    {
        for (int j = y-1; j <= y+1; j++)
        {
            if (i >= 0 && j >= 0 && i < g.taille && j < g.taille)
            {
                int val = g.matrice[i][j];
                if (val > valMax)
                {
                    valMax = val;
                    xMax = i;
                    yMax = j;
                }
            }
        }
    }
    return make_tuple(xMax, yMax);
}
vector<vector<char>> diagonales(solution s, int co_x, int co_y) {
    vector<char> diag1;
    vector<char> diag2; 
    int n=s.taille;
    for(int y = 0; y < n; y++) 
    {
        int x = co_y - (co_y - y);
        if (x >= 0 && x < n) diag1.push_back(s.matrice[y][x]);
        x = co_x + (co_y - y);
        if (x >= 0 && x < n) diag2.push_back(s.matrice[y][x]); 
    }
    return {diag1, diag2};
}


void affiche_diagonale(vector<char> matrice)
{
    int n=matrice.size();
    for (int i=0;i<n;++i)cout<<matrice[i]<<' ';
}

bool ligne_orangeSolution(solution s,int l)
{
    for (int i=0;i<s.taille;++i)
    {
        if (s.matrice[l][i]=='O')return true;
    }
    return false;
}

bool colonne_orangeSolution(solution s,int c)
{
    for (int i=0;i<s.taille;++i)
    {
        if (s.matrice[i][c]=='O')return true;
    }
    return false;
}
bool diagonale_orangeSolution(vector<char> diag)
{
    for (unsigned int i=0;i<diag.size();++i)
    {
        if (diag[i]=='O')return true;
    }
    return false;
}

solution genere_voisin(solution s, instance g) 
{
    solution nouvelle_solution;
    nouvelle_solution.taille = s.taille;
    nouvelle_solution.score = s.score;
    nouvelle_solution.matrice = s.matrice;

    do
    {
        int x1 = rand() % s.taille;
        int y1 = rand() % s.taille;
        int x2 = rand() % s.taille;
        int y2 = rand() % s.taille;

        char temp = nouvelle_solution.matrice[x1][y1];
        nouvelle_solution.matrice[x1][y1] = nouvelle_solution.matrice[x2][y2];
        nouvelle_solution.matrice[x2][y2] = temp;

        calculeScore(nouvelle_solution, g);
    }while (nouvelle_solution.score<=s.score);
    return nouvelle_solution;
}

solution GenereSolution1(instance g)
{
    solution s;
    do
    {
        int taille=g.taille;
        

        //Initialisation de s 
        s.taille=taille;
        s.score=0;
        vector<vector<char>> matrice;
        for (int i = 0; i < taille; i++) 
        {
            vector<char> ligne;
            for (int j = 0; j < taille; j++) 
            {
                ligne.push_back(' ');
            }
            matrice.push_back(ligne);
        }
        s.matrice=matrice;

        //Placement pions noirs
        vector<tuple<int,int>> pos_n=max_vecteur(g,taille);
        for (unsigned int i=0;i<pos_n.size();++i)
        {
            int xN=get<0>(pos_n[i]);
            int yN=get<1>(pos_n[i]);
            if (s.matrice[xN][yN]==' ') s.matrice[xN][yN]='N';
        }

        //Placement pion rouge
        tuple<int,int>coord =coordmin(g);
        int xR=get<0>(coord),yR=get<1>(coord);
        if (s.matrice[xR][yR]==' ') s.matrice[xR][yR]='R';

        //Placement pion vert & jaune
        for (int i=0;i<taille;++i)
        {
            for (int j=0;j<taille;++j)
            {
                //Placement vert
                int somme=g.matrice[i][j];
                if (i>0)somme+=g.matrice[i-1][j]; //case gauche
                if (i<taille-1)somme+=g.matrice[i+1][j]; //case droite
                if (j>0)somme+=g.matrice[i][j-1]; //case au dessus
                if (j<taille-1)somme+=g.matrice[i][j+1]; // case du dessous
                if(somme>0 && !pionDiagonale(s,'V',i,j) && !pionOrthogonal(s,'V',i,j) && s.matrice[i][j]==' ')s.matrice[i][j]='V';

                //Placement jaune
                if (g.matrice[i][j]>0)
                {
                    int max_val = 0;
                    int x_max = -1;
                    int y_max = -1;
                    for (int x = i-1; x <= i+1; ++x) //2 for = parcours des cases adjacentes pour rechercher le maximum
                    {
                        for (int y = j-1; y <= j+1; ++y) 
                        {
                            if (x >= 0 && x < taille && x!=i && y >= 0 && y < taille && y!=j) 
                            {
                                if (g.matrice[x][y] > max_val && s.matrice[x][y] == ' ') 
                                {
                                    max_val = g.matrice[x][y];
                                    x_max = x;
                                    y_max = y;
                                }
                            }
                        }
                    }
                    if (x_max != -1 && y_max != -1) 
                    {
                        s.matrice[i][j] = 'J';
                        s.matrice[x_max][y_max] = 'J';
                    }
                }
            }
        }
        for (int i = 0; i < taille; i++) 
        {
            for (int j = 0; j < taille; j++) 
            {
                vector<char> diag1, diag2;
                for (int k = 0; k < taille; k++) 
                {
                    int x1 = i - j + k;
                    int x2 = i + j - k;
                    if (x1 >= 0 && x1 < taille) 
                    {
                        diag1.push_back(s.matrice[x1][k]);
                    }
                    if (x2 >= 0 && x2 < taille) 
                    {
                        diag2.push_back(s.matrice[k][x2]);
                    }
                }
                if (!diagonale_orangeSolution(diag1) && !diagonale_orangeSolution(diag2) && !ligne_orangeSolution(s,i) && !colonne_orangeSolution(s,j) && s.matrice[i][j]==' ')s.matrice[i][j]='O';
                else if (s.matrice[i][j]==' ')s.matrice[i][j]='B';
            }
        }
        calculeScore(s,g);
    } while(!valide(s));
    return s;
}