#include "Piege.h"
#include <iostream>

using namespace std;

Piege::Piege (int degats) : degats(degats) {} 

char Piege::afficher() const {
    return 'T' ;
}

TypeCase Piege::getTypeCase() const {
    return TypeCase::PIEGE ;
}

ostream& operator<<(ostream& os, const Piege& e){
    os << e.afficher();
    return os;
}