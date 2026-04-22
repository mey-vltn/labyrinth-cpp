#include "Aventurier.h"


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

bool Aventurier::estVivant () const {
    return ptsVie > 0 ;
}

void Aventurier::afficherStatut() const {
    std::cout << "Position : (" << x << ", " << y << ")\n";
    std::cout << "Sante : " << ptsVie << "\n";
    std::cout << "Inventaire : " << nbTresors << " tresor(s)\n";
}


