#include "Piege.h"

Piege::Piege (int degats) : degats(degats) {} 

char Piege::afficher() const {
    return 'T' ;
}

TypeCase Piege::getTypeCase() const {
    return TypeCase::PIEGE ;
}