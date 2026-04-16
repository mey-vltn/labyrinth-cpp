#include "Case.h"
#include "Mur.h"
#include "Passage.h"
#include "Tresor.h"
#include "Monstre.h"
#include "Piege.h"

enum TypeCase {
    MUR,
    PASSAGE,
    TRESOR,
    MONSTRE,
    PIEGE
};

class CaseFactory {

    public:
        static Case* creerCase (TypeCase type) {
            switch(type) {
                
                case MUR :
                    return new Mur() ;
                
                case PASSAGE :
                    return new Mur() ;
                
                case TRESOR :
                    return new Mur() ;
                
                case MONSTRE :
                    return new Mur() ;
                
                case PIEGE :
                    return new Mur() ;  
                
                default :
                    return nullptr ;
            }
        }
};