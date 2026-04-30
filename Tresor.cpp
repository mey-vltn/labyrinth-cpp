#include "Tresor.h"
#include <iostream>

using namespace std;

Tresor::Tresor (int valeur) : valeur(valeur) {}

char Tresor::afficher () const {
    char c = 'T' ;
    return c ;
}

TypeCase Tresor::getTypeCase() const {
    return TypeCase::TRESOR ;
}

ostream& operator<<(ostream& os, const Tresor& e){
    os << e.afficher();
    return os;
}