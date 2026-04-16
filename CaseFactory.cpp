#include "CaseFactory.h"

#include "Case.h"
#include "Mur.h"
#include "Passage.h"
#include "Tresor.h"
#include "Monstre.h"
#include "Piege.h"

Case* CaseFactory::creerCase(TypeCase type) {
    switch(type) {
        
        case MUR :
            return new Mur();
        
        case PASSAGE :
            return new Passage();
        
        case TRESOR :
            return new Tresor(10);
        
        case MONSTRE :
            return new Monstre(10);
        
        case PIEGE :
            return new Piege(10);  
        
        default :
            return nullptr;
    }
};
