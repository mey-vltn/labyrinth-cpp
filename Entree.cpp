#include "Entree.h"
#include "CaseFactory.h"

char Entree::afficher() const {
    return 'E' ;
}

TypeCase Entree::getTypeCase() const {
    return TypeCase::ENTREE ;
}