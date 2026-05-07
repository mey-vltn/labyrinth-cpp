#include "Donjon.h"
#include "Aventurier.h"

#include <cstdlib>  
#include <ctime> 

int main() {
    std::srand(std::time(nullptr)) ; // ça initialise l'aléatoire

    Donjon donjon;
    Aventurier aventurier(0, 0) ;

    donjon.generer(21, 21) ;

    aventurier.boucledeJeu(donjon) ;

    return 0 ;
}