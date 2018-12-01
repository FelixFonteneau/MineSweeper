/*************************************************************************
Grille  -  description
-------------------
début                : $DATE$
copyright            : (C) $YEAR$ par $AUTHOR$
e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Grille> (fichier Grille.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
#include <unistd.h>

#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

using namespace std;

//------------------------------------------------------ Include personnel
#include "Grille.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//retourne une grille de l'état en entiers -1 si aucune information
void Grille::ResGrille(int * gr)
{
  for (unsigned int i(0); i < taille_x; i++ )
  {
    for (unsigned int j(0); j < taille_y; j++)
    {
      if(grille[j*taille_x + i].estOuvert)
      {
        gr[j*taille_x + i] = getNbBombs(i,j);

      }else if ((grille[j*taille_x + i].flag)) {
        gr[j*taille_x + i] = -2;
      } else {
        gr[j*taille_x + i] = - 1;
      }
    }
  }
}


void Grille::Afficher(void)
{
  if( estCommence && !estTermine)
  {
    for (unsigned int i(0); i < taille_x; i++ )
    {
      for (unsigned int j(0); j < taille_y; j++)
      {
        if ( grille[j*taille_x + i].estOuvert && getNbBombs(i,j) < 1)
        {
            ouvre(i, j);
        }

      }
    }
  }
  
  //Afficher la grille non initialisée
  usleep(10000);
  system("clear");
  cout << "    ";
  //première ligne
  for (unsigned int i = 0; i < taille_x; i++)
  {
    cout << setw(3) << i;
  }
  cout << endl << "  ";
  for (unsigned int i = 0; i < 2+taille_x*3; i++)
    cout << "_";
  cout << endl;

  for (unsigned int i = 0; i < taille_y; i++) {
    cout << setw(3) << i << "|";
    for (unsigned int j = 0; j < taille_x; j++)
      cout << setw(3) << getChar(j,i);
    cout << endl;
  }
}

void Grille::Commencer(const unsigned int x, const unsigned int y )
{
  estCommence = true;
  for (unsigned int i(0); i < taille_x; i++ )
  {
    for (unsigned int j(0); j < taille_y; j++)
    {
      if ( abs( (int) x - (int) i) <= 1 && abs( (int) y - (int) j) <= 1)
      {
        grille[j*taille_x + i].estBombe = false;
        grille[j*taille_x + i].estOuvert = true;
        grille[j*taille_x + i].flag = false;

      }
      else
      {
        grille[j*taille_x + i].estBombe =  ( (rand() % 5) == 0);
        grille[j*taille_x + i].estOuvert = false;
        grille[j*taille_x + i].flag = false;
      }
    }
  }
}


bool Grille::Click(const unsigned int x, const unsigned int y )
{
  if(!grille[y*taille_x + x].estOuvert && !grille[y*taille_x + x].flag)
  {
    if (grille[y*taille_x + x].estBombe)
    {
      estTermine = true;
      Afficher();
      return true;
    }
    grille[y*taille_x + x].estOuvert = true;
    if(getNbBombs(x,y) == 0){
      ouvre(x,y);
    }
  }
  Afficher();
  return false;
}

bool Grille::Flag(const unsigned int x,const unsigned int y)
{
  if(! grille[y*taille_x + x].estOuvert)
  {
    grille[y*taille_x + x].flag = !(grille[y*taille_x + x].flag);
  }
  Afficher();
  return grille[y*taille_x + x].flag;
}


bool Grille::EstTermine(void){
  return estTermine;
}


Grille::Grille(const unsigned int x, const unsigned int y)
{
	#ifdef MAP
		cout << "Appel au constructeur de <Grille>" << endl;
	#endif
  estCommence = false;
  estTermine = false;
  taille_x = x;
  taille_y = y;
  grille = new Case[x*y];
  Afficher();
}

Grille::~Grille()
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <Grille>" << endl;
#endif

  delete [] grille;
} //----- Fin de ~Grille


  //------------------------------------------------------------------ PRIVE

  //----------------------------------------------------- Méthodes protégées
string Grille::getChar(const unsigned int x,const unsigned int y) const
{
  //Pré Partie
  if(!estCommence)
  {
    return "\033[0m   \033[0m";
  }
  // Partie en cours
  else if (!estTermine)
  {
    if( !grille[y*taille_x + x].estOuvert)
    {
      if (grille[y*taille_x + x].flag)
        return "\033[41m ! \033[0m";
      return "\033[0m   \033[0m";
    }
    else
    {
      unsigned int nbBomb = getNbBombs(x,y);
      if ( nbBomb == 0)
      {
        return "\033[47m   \033[0m";
      }
      else
      {
        string couleur;

        //couleur des bombes
        switch (nbBomb) {
          case 1:
            couleur = "\033[44m ";
            break;

          case 2:
            couleur = "\033[42m ";
            break;

          case 3:
            couleur = "\033[43m ";
            break;

          case 4:
            couleur = "\033[40m ";
            break;

          case 5:
            couleur = "\033[45m ";
            break;

          case 6:
            couleur = "\033[46m ";
            break;

          default:
            couleur = "\033[0m ";
        }
        string s = couleur;
        s += to_string(nbBomb);
        s += " \033[0m";
        return s;
      }
    }
  }
  //partie Terminée
  else
  {
    if(grille[y*taille_x + x].estBombe)
    {
      return "\033[41m X \033[0m";
    }
    else
    {
      unsigned int nbBomb = getNbBombs(x,y);
      if ( nbBomb == 0)
      {
        return "\033[40m   \033[0m";
      }
      else
      {
        string s = "\033[40m ";
        s += to_string(nbBomb);
        s += " \033[0m";
        return s;
      }
    }
  }
}

unsigned int Grille::getNbBombs(const unsigned int x,const unsigned int y) const
{
  unsigned int nbBomb = 0;
  for(unsigned int k( x> 0 ?x- 1 :x); k <= (x== taille_x -1 ? x : x+ 1); k++)
  {
    for(unsigned int l( y>0 ? y - 1 : y); l <= ( y == taille_y-1 ? y : y+1); l++)
    {
      if( (l != y || k !=x) && grille[l*taille_x + k].estBombe  )
      {
        ++nbBomb;
      }
    }
  }
  return nbBomb;
}

void Grille::ouvre(const unsigned int x,const unsigned int y)
{
  for(unsigned int k( x> 0 ?x- 1 :x); k <= (x== taille_x -1 ? x : x+ 1); k++)
  {
    for(unsigned int l( y>0 ? y - 1 : y); l <= ( y == taille_y-1 ? y : y+1); l++)
    {
      if( (l != y || k !=x) && !(grille[l*taille_x + k].estOuvert) )
      {
        grille[l*taille_x + k].estOuvert = true;
        if (getNbBombs(k, l) == 0 )
            ouvre(k, l);
      }
    }
  }
}

//Grille & Grille::operator = ( const Grille & unGrille )
