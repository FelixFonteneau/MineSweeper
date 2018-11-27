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
    // Mode d'emploi :
    //
    // Contrat :
    //

	void Commencer(const unsigned int x,const unsigned int y );
	// Mode d'emploi :
	//
	// Contrat :
	//

  bool Click(const unsigned int x,const unsigned int y);
  bool Flag(const unsigned int x,const unsigned int y);


  void AfficherFin(void);

  void ResGrille(int * gr);


//------------------------------------------------- Surcharge d'opérateurs
 //   Grille & operator = ( const Grille & unGrille );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Grille (const unsigned int x,const unsigned int y);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //



    virtual ~Grille ( );
    // Mode d'emploi :
    // Détruit le tableau représentant l'Grille avant de détruire l'objet lui-même
    // Contrat :
    //

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
