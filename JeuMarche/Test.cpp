#include <stdio.h>
#include <iostream>
#include "Test.h"
#include "Grille.h"
#include <unistd.h>


using namespace std;



//void resoudre( int * & gr, Grille g);


int main(void)
{
  unsigned int x,y;
  Grille g(40,30); //initialisation taille
  std::cout << "Commencer" << '\n';
  std::cout << "Ouvrir case :" << '\n';
  std::cin >> x;
  std::cin >> y;
  g.Commencer(x,y); //comencer à x, y
  g.Afficher();
   bool part = true;
   while (part) {
     char c;
     std::cout << "Poser un drapeau ou ouvrir case ? (F/O) suivit x et y" << '\n';
     std::cin >> c;
     if (c == 'F' || c=='f')
     {
       std::cin >> x;
       std::cin >> y;
       if( !(x < 40 && x>=0) || !((y < 30 && y>=0)))
       {
         std::cout << "Vous avez choisi une mauvaise case..." << '\n';
       }else{
         g.Flag(x,y);
       }
     }else if (c == 'O' || c=='o')
     {
       std::cin >> x;
       std::cin >> y;
       if( !(x < 40 && x>=0) || !((y < 30 && y>=0)))
       {
         std::cout << "Vous avez choisi une mauvaise case..." << '\n';
       }else{
         if(g.Click(x,y)) part = false;
       }
     }
   }

	return 0;
}
