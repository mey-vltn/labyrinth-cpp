#include "Mur.h"
#include <iostream>

using namespace std;

char Mur::afficher () const {
    return '#' ;
}

TypeCase Mur::getTypeCase() const {
    return TypeCase::MUR ;
}

ostream& operator<<(ostream& os, const Mur& e){
    os << e.afficher();
    return os;
}