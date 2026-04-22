#include "Monstre.h"

Monstre::Monstre (int pv) : pv(pv) {}

char Monstre::afficher() const {
    return 'M' ;
}

TypeCase Monstre::getTypeCase() const {
    return TypeCase::MONSTRE ;
}