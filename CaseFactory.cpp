#include "CaseFactory.h"

#include "Case.h"
#include "Mur.h"
#include "Passage.h"
#include "Tresor.h"
#include "Monstre.h"
#include "Piege.h"
#include "Entree.h"
#include "Sortie.h"

#include <stdexcept>

Case* CaseFactory::creerCase(TypeCase type) {
    
    switch(type) {
        
        case TypeCase::MUR :
            return new Mur();
        
        case TypeCase::PASSAGE :
            return new Passage();
        
        case TypeCase::TRESOR :
            return new Tresor(10);
        
        case TypeCase::MONSTRE :
            return new Monstre(10);
        
        case TypeCase::PIEGE :
            return new Piege(10);  
        
        case TypeCase::ENTREE:
            return new Entree();

        case TypeCase::SORTIE:
            return new Sortie();
        
        default :
            throw std::invalid_argument("TypeCase invalide");;
    }
};
