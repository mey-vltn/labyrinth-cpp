#include "Monstre.h"
#include <iostream>

using namespace std;

Monstre::Monstre (int pv) : pv(pv) {}

char Monstre::afficher() const {
    return 'M' ;
}

TypeCase Monstre::getTypeCase() const {
    return TypeCase::MONSTRE ;
}

ostream& operator<<(ostream& os, const Monstre& e) {
    os << e.afficher() ;
    return os ;
}