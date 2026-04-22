#include "Mur.h"

char Mur::afficher () const {
    return '#' ;
}

TypeCase Mur::getTypeCase() const {
    return TypeCase::MUR ;
}