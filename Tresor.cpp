#include "Tresor.h"

Tresor::Tresor (int valeur) : valeur(valeur) {}

char Tresor::afficher () const {
    char c = 'T' ;
    return c ;
}

TypeCase Tresor::getTypeCase() const {
    return TypeCase::TRESOR ;
}