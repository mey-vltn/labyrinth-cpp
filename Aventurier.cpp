#include "Aventurier.h"
#include "CaseFactory.h"
#include "TypeCase.h"

#include <iostream>



// CONSTRUCTEUR
Aventurier::Aventurier (int xInit, int yInit) 
    : x(xInit), y(yInit), ptsVie(100), nbTresors(0) {}



// GETTERS 

int Aventurier::getX() const {
    return x ;
}

int Aventurier::getY() const {
    return y ;
}

int Aventurier::getPV() const {
    return ptsVie ;
}

int Aventurier::getNbTresors() const {
    return nbTresors ;
}




void Aventurier::deplacer(int nx, int ny) {
    x = nx ;
    y = ny ;
}

void Aventurier::pertePV(int degats) {
    ptsVie -= degats ;
    if (ptsVie < 0) ptsVie = 0 ;
}

void Aventurier::ajouterTresor() {
    nbTresors++ ;
} 

bool Aventurier::estVivant () const {
    return ptsVie > 0 ;
}

void Aventurier::afficherStatut() const {
    std::cout << "Position : (" << x << ", " << y << ")\n";
    std::cout << "Sante : " << ptsVie << "\n";
    std::cout << "Inventaire : " << nbTresors << " tresor(s)\n";
}


void Aventurier::resoudreCase (Donjon& d, int x, int y)  {

    Case* c = d.getCase(x,y) ;

    switch (c->getTypeCase()) {

        case TypeCase::MUR:
            break ;

        case TypeCase::PASSAGE :
            break ;

        case TypeCase::TRESOR :
            std::cout << "VOUS AVEZ TROUVÉ UN TRÉSOR" << endl ;
            ajouterTresor() ;
            d.remplacerCase(x, y, CaseFactory::creerCase(TypeCase::PASSAGE)) ;
            break ;

        case TypeCase::MONSTRE :
            char choix ;
            std::cout << "Il Y a un monstre : saisir c = combattre ou f = fuir :" << endl ;
            std::cin >> choix ;

            if (choix == 'c') {
                std::cout << "Combat =>  perte de x PV.\n";
                pertePV(10) ;
                d.remplacerCase(x, y, CaseFactory::creerCase(TypeCase::PASSAGE)) ;
            } 
            else if (choix == 'f') {
                std::cout << "Fuite prise.\n";
            } 
            else {
                std::cout << "Choix invalide => perte de x PV.\n" ;
                pertePV(15) ;
                d.remplacerCase(x, y, CaseFactory::creerCase(TypeCase::PASSAGE)) ;
            }
            break ;

        case TypeCase::PIEGE :
            std::cout << "Un piege se declenche, perds x PV.\n";
            pertePV(10);
            d.remplacerCase(x, y, CaseFactory::creerCase(TypeCase::PASSAGE)) ;
            break;


            
        

        
    }
}
