#include <stdio.h>
#include <iostream>
#include <ctime>
#include "Test.h"
#include "Grille.h"
#include <unistd.h>
#include <vector>



using namespace std;

#define TAILLE_X 40
#define TAILLE_Y 30




void resoudre( int * & gr, Grille & g);
// mode d'emploi :
int nbCaseFlag(const unsigned int x, const unsigned int y,const int *  gr);
int nbCaseNonOuverte(const unsigned int x, const unsigned int y, int *  gr);
void poseFlag(unsigned int i, unsigned int j, int * & gr, Grille & g);
void ouvreCase(const unsigned int i,const  unsigned int j, int * & gr, Grille & g);
void resoudComplex(const unsigned int i,const  unsigned int j, int * & gr, Grille & g);
vector<vector<unsigned int > > coordoneeCasesVides(const unsigned int i,const  unsigned int j, int * & gr);
void cas32(const unsigned int i,const  unsigned int j, int * & gr, Grille & g);
void cas21(const unsigned int i,const  unsigned int j, int * & gr, Grille & g);



int main(void)
{
  unsigned int x,y;
  int * gr = new int[TAILLE_X*TAILLE_Y]; //gr de résolution algo
  Grille g(TAILLE_X,TAILLE_Y); //initialisation taille
  cout << "Commencer" << '\n';
  cout << "Ouvrir case :" << '\n';
  cin >> x;
  cin >> y;

  g.Commencer(x,y); //comencer à x, y
  g.Afficher();
  g.ResGrille(gr);
  resoudre(gr, g);

  delete [] gr;
	return 0;
}

//algo permetant de résoudre le démineur
void resoudre( int * & gr, Grille & g)
{
  bool plusDeCasTriviaux = true;
  bool faireComplex = false;

  while (!g.EstTermine())
  {
    plusDeCasTriviaux = true;
    for (unsigned int i(0); i < TAILLE_X; i++ )
    {
      for (unsigned int j(0); j < TAILLE_Y; j++)
      {

        if ( gr[j*TAILLE_X + i] != -1 && gr[j*TAILLE_X + i] != -2 && nbCaseNonOuverte(i,j, gr) != 0 ) {
          //Traitement des cases ayant le nombre de bombes exact
          if ( (nbCaseNonOuverte(i,j, gr) == gr[j*TAILLE_X + i] && nbCaseFlag(i,j,gr) == 0) || (nbCaseNonOuverte(i,j, gr) == gr[j*TAILLE_X + i] - nbCaseFlag(i,j,gr)) )
          {
            plusDeCasTriviaux = false;
            poseFlag(i,j,gr,g);
          }

          //cas où on connait l'emplacement des bombes, on ouvre le reste
          if (nbCaseFlag(i,j,gr) == gr[j*TAILLE_X + i])
          {
            plusDeCasTriviaux = false;
            ouvreCase(i,j,gr,g);
          }

          //Autres cas plus complexes
         if(faireComplex && nbCaseNonOuverte(i,j,gr) > gr[j*TAILLE_X + i] - nbCaseFlag(i,j,gr))
          {
            resoudComplex(i,j,gr,g);
          }

        }
      }
    }
    if (faireComplex) faireComplex = false;
    if(plusDeCasTriviaux) faireComplex = true;
  }
}

void resoudComplex(const unsigned int i,const  unsigned int j, int * & gr, Grille & g)
{
  if(nbCaseNonOuverte(i,j,gr) == 3 && gr[j*TAILLE_X + i] - nbCaseFlag(i,j,gr) == 2)
  {
    cas32(i,j,gr,g);
  }

  if(nbCaseNonOuverte(i,j,gr) == 2 && gr[j*TAILLE_X + i] - nbCaseFlag(i,j,gr) == 1)
  {
    cas21(i,j,gr,g);
  }
}

void cas32(const unsigned int i,const  unsigned int j, int * & gr, Grille & g)
{
  vector<vector<unsigned int > > casesLibres = coordoneeCasesVides(i,j,gr);
  for(unsigned int k( i>0 ? i - 1 : i); k <= ( i == TAILLE_X -1 ? i : i+1); k++)
  {
    for(unsigned int l( j>0 ? j - 1 : j); l <= ( j == TAILLE_Y-1 ? j : j+1); l++)
    {
      if(nbCaseNonOuverte(k,l,gr) >= 2 && gr[l*TAILLE_X + k] - nbCaseFlag(k,l,gr) == 1)
      {
        //std::cout << "passe !" << '\n';
        vector<vector<unsigned int > > casesLibresTmp = coordoneeCasesVides(k,l,gr);
        unsigned int cmpt = 0;
        vector<unsigned int > coordBomb;
        for (vector<unsigned int > c1 : casesLibres) // access by reference to avoid copying
        {
          bool egal = false;
          for (vector<unsigned int > c2 : casesLibresTmp) // access by reference to avoid copying
          {
            if(c1 == c2)
            {
              ++cmpt;
              egal = true;
             }
          }
          if (!egal)
          {
            coordBomb = c1;
          }
        }

        if (cmpt == 2)
        {
          g.Flag(coordBomb[0],coordBomb[1]);
          g.ResGrille(gr);
          for (vector<unsigned int > c2 : casesLibresTmp) // access by reference to avoid copying
          {
            bool egal = false;
            for (vector<unsigned int > c1 : casesLibres) // access by reference to avoid copying
            {
              if(c1 == c2)
              {
                egal = true;
               }
            }
            if (!egal)
            {
              g.Click(c2[0],c2[1]);
              g.ResGrille(gr);

            }
          }
        }
      }
    }
  }
  casesLibres.clear();
}

void cas21(const unsigned int i,const  unsigned int j, int * & gr, Grille & g)
{

  vector<vector<unsigned int > > casesLibres = coordoneeCasesVides(i,j,gr);
  for(unsigned int k( i>0 ? i - 1 : i); k <= ( i == TAILLE_X -1 ? i : i+1); k++)
  {
    for(unsigned int l( j>0 ? j - 1 : j); l <= ( j == TAILLE_Y-1 ? j : j+1); l++)
    {
      if(nbCaseNonOuverte(k,l,gr) >= 3 && gr[l*TAILLE_X + k] - nbCaseFlag(k,l,gr) == 1)
      {
        //std::cout << "passe !" << '\n';
        vector<vector<unsigned int > > casesLibresTmp = coordoneeCasesVides(k,l,gr);
        unsigned int cmpt = 0;
        vector<unsigned int > coordBomb;
        for (vector<unsigned int > c1 : casesLibres) // access by reference to avoid copying
        {
          for (vector<unsigned int > c2 : casesLibresTmp) // access by reference to avoid copying
          {
            if(c1 == c2)
            {
              ++cmpt;
             }
          }
        }

        if (cmpt == 2)
        {
          for (vector<unsigned int > c2 : casesLibresTmp) // access by reference to avoid copying
          {
            bool egal = false;
            for (vector<unsigned int > c1 : casesLibres) // access by reference to avoid copying
            {
              if(c1 == c2)
              {
                egal = true;
               }
            }
            if (!egal)
            {
              g.Click(c2[0],c2[1]);
              g.ResGrille(gr);

            }
          }
        }
      }
    }
  }

}


vector<vector<unsigned int > > coordoneeCasesVides(const unsigned int i,const  unsigned int j, int * & gr)
{
  vector<vector<unsigned int > > casesLibres;

  for(unsigned int k( i>0 ? i - 1 : i); k <= ( i == TAILLE_X -1 ? i : i+1); k++)
  {
    for(unsigned int l( j>0 ? j - 1 : j); l <= ( j == TAILLE_Y-1 ? j : j+1); l++)
    {
      if( (l != j || k != i) && gr[(l)*TAILLE_X + k] == -1)
      {
        vector<unsigned int > coordoneeCasesVides;
        coordoneeCasesVides.push_back(k);
        coordoneeCasesVides.push_back(l);
        casesLibres.push_back(coordoneeCasesVides);
        coordoneeCasesVides.clear();
      }
    }
  }
  return casesLibres;
}


void ouvreCase(const unsigned int i,const  unsigned int j, int * & gr, Grille & g)
{

  for(unsigned int k( i>0 ? i - 1 : i); k <= ( i == TAILLE_X -1 ? i : i+1); k++)
  {
    for(unsigned int l( j>0 ? j - 1 : j); l <= ( j == TAILLE_Y-1 ? j : j+1); l++)
    {
      if( (l != j || k != i) && gr[(l)*TAILLE_X + k] == -1 )
      {
        g.Click(k,l);
        g.ResGrille(gr);
      }
    }
  }
}

void poseFlag(const unsigned int i,const  unsigned int j, int * & gr, Grille & g)
{

  for(unsigned int k( i>0 ? i - 1 : i); k <= ( i == TAILLE_X-1 ? i : i+1); k++)
  {
    for(unsigned int l( j>0 ? j - 1 : j); l <= ( j == TAILLE_Y-1 ? j : j+1); l++)
    {
      if( (l != j || k != i) &&  gr[(l)*TAILLE_X + k] == -1 )
      {
        g.Flag(k,l);
        g.ResGrille(gr);
      }
    }
  }
}

int nbCaseFlag(const unsigned int i, const unsigned int j, const int *  gr)
{
  int nb = 0;
  for(unsigned int k( i>0 ? i - 1 : i); k <= ( i == TAILLE_X-1 ? i : i+1); k++)
  {
    for(unsigned int l( j>0 ? j - 1 : j); l <= ( j == TAILLE_Y-1 ? j : j+1); l++)
    {
      if( (l != j || k != i) &&  gr[(l)*TAILLE_X + k] == -2 )
      {
        ++nb;
      }
    }
  }
  return nb;
}

int nbCaseNonOuverte(unsigned int i, unsigned int j, int *  gr)
{
  int nb = 0;
  for(unsigned int k( i>0 ? i - 1 : i); k <= ( i == TAILLE_X-1 ? i : i+1); k++)
  {
    for(unsigned int l( j>0 ? j - 1 : j); l <= ( j == TAILLE_Y-1 ? j : j+1); l++)
    {
      if( (l != j || k != i) && gr[(l)*TAILLE_X + k] == -1 )
      {
        ++nb;
      }
    }
  }
  return nb;
}
