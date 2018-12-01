/*************************************************************************
                           Grille  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Grille> (fichier Grille.h) ----------------
#if ! defined ( Grille_H )
#define Grille_H

//--------------------------------------------------- Interfaces utilisées
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


//------------------------------------------------------------------------
// Rôle de la classe <Grille>
// Gestion d'une collection d'entier, avec réajustement automatique ou à
// la demande. Cette collection d'entier peut s'apparenter à un Grille
// mathématique.
//
//------------------------------------------------------------------------

class Grille
{

  // structure privée de la classe Grille
  struct Case {
    bool estBombe;
    bool estOuvert;
    bool flag;
  };
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

  bool EstTermine(void);
	void Afficher ( void );
    // Mode d'emploi : affiche l'état actuel de la grille dans le terminal
    //
    // Contrat :
    //

	void Commencer(const unsigned int x,const unsigned int y );
	// Mode d'emploi : demande à l'utilisateur d'entrer la première case à ouvrir
	// la grille sera générée en fonction de cette case de départs
	// Contrat :
	// 0 <= x <= taille_x-1 (taille de donnée au constructeur)
  // 0 <= y <= taille_y-1 (taille de donnée au constructeur)

  bool Click(const unsigned int x,const unsigned int y);
  // Mode d'emploi :ouvre la case (x,y) puis affiche l'état actuel de la grille
  // si (x,y) est une bombe, la partie se termine
  // sinon elle continue
  // Contrat :
  // 0 <= x <= taille_x-1 (taille de donnée au constructeur)
  // 0 <= y <= taille_y-1 (taille de donnée au constructeur)


  bool Flag(const unsigned int x,const unsigned int y);
  // Mode d'emploi :pose ou enlève un drapeau à la case (x,y) puis affiche
  // l'état actuel de la grille
  // Contrat :
  // 0 <= x <= taille_x-1 (taille de donnée au constructeur)
  // 0 <= y <= taille_y-1 (taille de donnée au constructeur)



  void ResGrille(int * gr);
  // Mode d'emploi : prend en entrée un tableau gr et met à jour l'état actuel
  // du jeu dans ce tableau. gr est un tableau applatit.
  // Contrat :
  // gr [taille_x * taille_y]



//-------------------------------------------- Constructeurs - destructeur
    Grille (const unsigned int x,const unsigned int y);
    // Mode d'emploi (constructeur de copie) :
    // Construit la grille de taille x * y
    // Contrat :
    // x>1, y>1



    virtual ~Grille ( );
    // Mode d'emploi :
    // Détruit le tableau représentant l'Grille avant de détruire l'objet lui-même


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

  std::string getChar(const unsigned int x,const  unsigned int y) const;
  unsigned int getNbBombs(const unsigned int x,const unsigned int y) const;
  void ouvre(const unsigned int x,const unsigned int y);
//----------------------------------------------------- Attributs protégés
bool estTermine;
bool estCommence;
unsigned int taille_x;
unsigned int taille_y;
Case * grille;

};

//-------------------------------- Autres définitions dépendantes de <Grille>

#endif // Grille_H
