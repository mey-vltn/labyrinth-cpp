#include "Aventurier.h"

bool Aventurier::estVivant () const {
    return this->ptsVie > 0 ;
}


void Aventurier::afficherStatut() const {
    cout << "Position    : (" << this->position.first << "" 
}