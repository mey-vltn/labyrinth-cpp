#include "Aventurier.h"
#include "CaseFactory.h"
#include "TypeCase.h"

#include <iostream>


// CONSTRUCTEUR
Aventurier::Aventurier (int xInit, int yInit) 
    : x(xInit), y(yInit), ptsVie(100), nbTresors(0) {}



// GETTERS 

int Aventurier::getX() const {
    return x ;
}

int Aventurier::getY() const {
    return y ;
}

int Aventurier::getPV() const {
    return ptsVie ;
}

int Aventurier::getNbTresors() const {
    return nbTresors ;
}





void Aventurier::deplacer(int nx, int ny) {
    x = nx ;
    y = ny ;
}

void Aventurier::pertePV(int degats) {
    ptsVie -= degats ;
    if (ptsVie < 0) ptsVie = 0 ;
}

void Aventurier::gagnerPV(int soin) {
    ptsVie += soin ;
}

void Aventurier::ajouterTresor() {
    nbTresors++ ;
} 

bool Aventurier::estVivant () const {
    return ptsVie > 0 ;
}

void Aventurier::afficherStatut() const {
    std::cout << "Position : (" << x << ", " << y << ")\n";
    std::cout << "Points de vie : " << ptsVie << "/100\n";
    std::cout << "Inventaire : " << nbTresors << " tresor(s) coffrés\n\n";
}


bool Aventurier::resoudreCase (Donjon& d, int x, int y)  {

    Case* c = d.getCase(x,y) ;

    switch (c->getTypeCase()) {

        case TypeCase::MUR:
            return false ;

        case TypeCase::PASSAGE :
            return true ;

        case TypeCase::TRESOR : {
            std::cout << "VOUS AVEZ TROUVÉ UN TRÉSOR" << endl ;
            ajouterTresor() ;

            int soin = 5 + rand() % 6 ; // entre 5 et 10
            gagnerPV(soin) ;

            std::cout << "Le tresor vous soigne de " << soin << " PV.\n" ;

            d.remplacerCase(x, y, CaseFactory::creerCase(TypeCase::PASSAGE)) ;
            return true ;
        }

        case TypeCase::MONSTRE :
            char choix ;
            std::cout << "Il Y a un monstre : saisir c = combattre ou f = fuir :" << endl ;
            std::cin >> choix ;

            // randomiser le nombre de ptsVie perdus?
            // que faire en cas de fuite?

            if (choix == 'c') {
                std::cout << "Combat =>  perte de 10 PV.\n";
                pertePV(10) ;
                d.remplacerCase(x, y, CaseFactory::creerCase(TypeCase::PASSAGE)) ;
                return true ;
            } 
            else if (choix == 'f') {
                std::cout << "Fuite prise : le monstre rôde ailleurs dans le donjon...\n";
                d.deplacerMonstreAleatoirement(x, y);
                return false;
            }
            else {
                std::cout << "Choix invalide => perte de 15 PV.\n" ;
                pertePV(15) ;
                d.remplacerCase(x, y, CaseFactory::creerCase(TypeCase::PASSAGE)) ;
                return false ;
            }


        case TypeCase::PIEGE :{
            int degats = 5 + rand() % 16 ; // entre 5 et 20
            std::cout << "Un piege se declenche, perte de " << degats << " PV.\n";
            pertePV(degats);
            d.remplacerCase(x, y, CaseFactory::creerCase(TypeCase::PASSAGE)) ;
            return true ;
        }
        
        case TypeCase::SORTIE:
            return true ;

        case TypeCase::ENTREE:
            return true ;
    }
    return false ;
}

void Aventurier::boucledeJeu(Donjon& d){
    char clavier;
    d.marquerVisitee(x, y);

    while (estVivant() && d.getCase(x, y)->getTypeCase() != TypeCase::SORTIE){
        
        d.afficher(x,y);

        cout << "ZQSD pour bouger | I = sauvegarder | M = charger\n\n";
        
        afficherStatut();

        cout << "Nombre de cases visitées : " << d.getNbCasesVisitees() << endl << endl;

        auto chemin = d.trouverChemin(d.getGrille(), {x, y}, {d.getSortieX(), d.getSortieY()});
        cout << "Distance à la sortie: " << chemin.size() - 1 << " cases\n\n";

        cin >> clavier;

        int nx = x;
        int ny = y;

        switch (clavier){
            case 'z':
                nx--;
                break;

            case 'q':
                ny--;
                break;

            case 's':
                nx++;
                break;

            case 'd':
                ny++;
                break;

            case 'p': {
                auto chemin = d.trouverChemin(
                    d.getGrille(),
                    {x, y},
                    {d.getSortieX(), d.getSortieY()}
                );
            
                d.afficherChemin(chemin, x, y);
            
                break ;
            }
            case 'i':  // sauvegarde
                d.sauvegarder("donjon.txt");
                cout << "Donjon sauvegardé.\n";
                break;

            case 'm':  // chargement
                d.charger("donjon.txt");
                cout << "Donjon chargé.\n";
                break;
            
            default:
                break;
        }

        // vérification si la case cible est un mur
        Case* cible = d.getCase(nx, ny);
        if(cible == nullptr || cible->getTypeCase() == TypeCase::MUR){
            cout << "Le déplacement est impossible." << endl;
            continue;
        }

        bool peutAvancer = resoudreCase(d, nx, ny) ;
        if (peutAvancer) {
            deplacer(nx, ny);
            d.marquerVisitee(nx, ny);
        }

    }

    if (!estVivant()){
        cout<<"GAME OVER"<<endl;
    }
    else{
        cout << "BRAVO VOUS ETES SORTI !!"<<endl;
    }
}


