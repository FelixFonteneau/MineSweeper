#include <stdio.h>
#include <iostream>
#include "Test.h"
#include "Grille.h"
#include <unistd.h>


using namespace std;



void resoudre( int * & gr, Grille & g);
int nbCaseFlag(const unsigned int x, const unsigned int y,const int *  gr);
int nbCaseNonOuverte(const unsigned int x, const unsigned int y, int *  gr);
void poseFlag(unsigned int i, unsigned int j, int * & gr, Grille & g);
void ouvreCase(const unsigned int i,const  unsigned int j, int * & gr, Grille & g);


int main(void)
{
  unsigned int x,y;
  int * gr = new int[40*30]; //gr de résolution algo
  Grille g(40,30); //initialisation taille
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
  for (unsigned int i(0); i < 40; i++ )
  {
    for (unsigned int j(0); j < 30; j++)
    {

      if ( gr[j*40 + i] != -1 && gr[j*40 + i] != -2 && nbCaseNonOuverte(i,j, gr) != 0 ) {

    /*    for(unsigned int x(0); x < 40; x++)
        {
          for(unsigned int y(0); y < 30; y++)
          {
            std::cout << gr[y*40 + x];
          }
          std::cout << '\n';
        }
        std::cout <<i << " " << j << " " <<  nbCaseNonOuverte(i,j,gr) << '\n'; */

        //Traitement des cases ayant le nombre de bombes exact
        if ( (nbCaseNonOuverte(i,j, gr) == gr[j*40 + i] && nbCaseFlag(i,j,gr) == 0) || (nbCaseNonOuverte(i,j, gr) == gr[j*40 + i] - nbCaseFlag(i,j,gr)) )
        {
          poseFlag(i,j,gr,g);
        }

        //cas où on connait l'emplacement des bombes, on ouvre le reste
        if (nbCaseFlag(i,j,gr) == gr[j*40 + i])
        {
          ouvreCase(i,j,gr,g);
        }

        //Autres cas plus complexes
  /*      if(nbCaseNonOuverte(i,j,gr) > gr[j*40 + i] - nbCaseFlag(i,j,gr))
        {

          if(nbCaseNonOuverte == 2 && gr[j*40 + i] - nbCaseFlag(i,j,gr) == 1)
          {

          }

        } */

      }
    }
  }
}

void ouvreCase(const unsigned int i,const  unsigned int j, int * & gr, Grille & g)
{
  if( i != 0 )
  {
    if( j != 0)
    {
      if(gr[(j-1)*40 + i-1] == -1 )
      {
        g.Click(i-1,j-1);
        g.ResGrille(gr);

      }
    }

    if(gr[(j)*40 + i-1] == -1 )
    {
      g.Click(i-1,j);
      g.ResGrille(gr);

    }

    if (j != 30-1 && gr[(j+1)*40 + i-1] == -1)
    {
      g.Click(i-1,j+1);
      g.ResGrille(gr);

    }
  }

  if( j != 0 &&  gr[(j-1)*40 + i] == -1)
  {
    g.Click(i,j-1);
    g.ResGrille(gr);

  }

  if (j != 30-1 && gr[(j+1)*40 + i] == -1)
  {
    g.Click(i,j+1);
    g.ResGrille(gr);

  }

  if (i != 40-1)
  {
    if( j != 0 && gr[(j-1)*40 + i+1] == -1)
    {
      g.Click(i+1,j-1);
      g.ResGrille(gr);

    }

    if( gr[(j)*40 + i+1] == -1 )
    {
      g.Click(i+1,j);
      g.ResGrille(gr);

    }


    if (j != 30-1 && gr[(j+1)*40 + i+1] == -1)
    {
      g.Click(i+1,j+1);
      g.ResGrille(gr);

    }
  }
}

void poseFlag(const unsigned int i,const  unsigned int j, int * & gr, Grille & g)
{
  if( i != 0 )
  {
    if( j != 0)
    {
      if(gr[(j-1)*40 + i-1] == -1 )
      {
        g.Flag(i-1,j-1);
        g.ResGrille(gr);

      }
    }

    if(gr[(j)*40 + i-1] == -1 )
    {
      g.Flag(i-1,j);
      g.ResGrille(gr);

    }

    if (j != 30-1 && gr[(j+1)*40 + i-1] == -1)
    {
      g.Flag(i-1,j+1);
      g.ResGrille(gr);

    }
  }

  if( j != 0 &&  gr[(j-1)*40 + i] == -1)
  {
    g.Flag(i,j-1);
    g.ResGrille(gr);

  }

  if (j != 30-1 && gr[(j+1)*40 + i] == -1)
  {
    g.Flag(i,j+1);
    g.ResGrille(gr);

  }

  if (i != 40-1)
  {
    if( j != 0 && gr[(j-1)*40 + i+1] == -1)
    {
      g.Flag(i+1,j-1);
      g.ResGrille(gr);

    }

    if( gr[(j)*40 + i+1] == -1 )
    {
      g.Flag(i+1,j);
      g.ResGrille(gr);

    }


    if (j != 30-1 && gr[(j+1)*40 + i+1] == -1)
    {
      g.Flag(i+1,j+1);
      g.ResGrille(gr);

    }
  }
}

int nbCaseFlag(const unsigned int x, const unsigned int y, const int *  gr)
{
  int nb = 0;
  if( x != 0 )
  {
    if( y != 0)
        nb += gr[(y-1)*40 + x-1] == -2 ? 1 : 0;

    nb += gr[(y)*40 + x-1] == -2 ? 1 : 0;

    if (y != 30-1)
        nb += gr[(y+1)*40 + x-1] == -2 ? 1 : 0;
  }

  if( y != 0)
      nb += gr[(y-1)*40 + x] == -2 ? 1 : 0;

  if (y != 30-1)
      nb += gr[(y+1)*40 + x] == -2 ? 1 : 0;

  if (x != 40-1)
  {
    if( y != 0)
        nb += gr[(y-1)*40 + x+1] == -2 ? 1 : 0;

    nb += gr[(y)*40 + x+1] == -2 ? 1 : 0;

    if (y != 30-1)
        nb += gr[(y+1)*40 + x+1] == -2 ? 1 : 0;
  }
  return nb;
}

int nbCaseNonOuverte(unsigned int x, unsigned int y, int *  gr)
{
  int nb = 0;
  if( x != 0 )
  {
    if( y != 0)
        nb += gr[(y-1)*40 + x-1] == -1 ? 1 : 0;

    nb += gr[(y)*40 + x-1] == -1 ? 1 : 0;

    if (y != 30-1)
        nb += gr[(y+1)*40 + x-1] == -1 ? 1 : 0;
  }

  if( y != 0)
      nb += gr[(y-1)*40 + x] == -1 ? 1 : 0;

  if (y != 30-1)
      nb += gr[(y+1)*40 + x] == -1 ? 1 : 0;

  if (x != 40-1)
  {
    if( y != 0)
        nb += gr[(y-1)*40 + x+1] == -1 ? 1 : 0;

    nb += gr[(y)*40 + x+1] == -1 ? 1 : 0;

    if (y != 30-1)
        nb += gr[(y+1)*40 + x+1] == -1 ? 1 : 0;
  }
  return nb;
}
