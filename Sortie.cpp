#include "Sortie.h"
#include "CaseFactory.h"

char Sortie::afficher() const {
    return 'S' ;
}

TypeCase Sortie::getTypeCase() const {
    return TypeCase::SORTIE ;
}