#include <stdio.h>
#include <iostream>
#include "Test.h"
#include "Grille.h"
#include <unistd.h>


using namespace std;

#define TAILLE_X 40
#define TAILLE_Y 30




void resoudre( int * & gr, Grille & g);
int nbCaseFlag(const unsigned int x, const unsigned int y,const int *  gr);
int nbCaseNonOuverte(const unsigned int x, const unsigned int y, int *  gr);
void poseFlag(unsigned int i, unsigned int j, int * & gr, Grille & g);
void ouvreCase(const unsigned int i,const  unsigned int j, int * & gr, Grille & g);


int main(void)
{
  unsigned int x,y;
  int * gr = new int[TAILLE_X*TAILLE_Y]; //gr de résolution algo
  Grille g(TAILLE_X,TAILLE_Y); //initialisation taille
  std::cout << "Commencer" << '\n';
  std::cout << "Ouvrir case :" << '\n';
  std::cin >> x;
  std::cin >> y;

  g.Commencer(x,y); //comencer à x, y
  g.Afficher();
  while (!g.EstTermine())
  {
    g.ResGrille(gr);
    resoudre(gr, g);
  }

  delete [] gr;
	return 0;
}

//algo permetant de résoudre le démineur
void resoudre( int * & gr, Grille & g)
{
  for (unsigned int i(0); i < TAILLE_X; i++ )
  {
    for (unsigned int j(0); j < TAILLE_Y; j++)
    {

      if ( gr[j*TAILLE_X + i] != -1 && gr[j*TAILLE_X + i] != -2 && nbCaseNonOuverte(i,j, gr) != 0 ) {

    /*    for(unsigned int x(0); x < TAILLE_X; x++){
            for(unsigned int y(0); y < TAILLE_Y; y++){
              std::cout << gr[y*TAILLE_X + x];
            }
          std::cout << '\n';
        }
        std::cout <<i << " " << j << " " <<  nbCaseNonOuverte(i,j,gr) << '\n'; */

        //Traitement des cases ayant le nombre de bombes exact
        if ( (nbCaseNonOuverte(i,j, gr) == gr[j*TAILLE_X + i] && nbCaseFlag(i,j,gr) == 0) || (nbCaseNonOuverte(i,j, gr) == gr[j*TAILLE_X + i] - nbCaseFlag(i,j,gr)) )
        {
          poseFlag(i,j,gr,g);
        }

        //cas où on connait l'emplacement des bombes, on ouvre le reste
        if (nbCaseFlag(i,j,gr) == gr[j*TAILLE_X + i])
        {
          ouvreCase(i,j,gr,g);
        }

        //Autres cas plus complexes
  /*      if(nbCaseNonOuverte(i,j,gr) > gr[j*TAILLE_X + i] - nbCaseFlag(i,j,gr))
        {

          if(nbCaseNonOuverte == 2 && gr[j*TAILLE_X + i] - nbCaseFlag(i,j,gr) == 1)
          {

          }

        } */

      }
    }
  }
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
