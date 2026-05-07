#include "Aventurier.h"
#include "CaseFactory.h"
#include "TypeCase.h"

#include <iostream>
#include <vector>

#define RESET   "\033[0m"
#define ROUGE   "\033[31m"
#define VERT    "\033[32m"
#define JAUNE   "\033[33m"
#define BLEU    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"


// CONSTRUCTEUR
Aventurier::Aventurier (int xInit, int yInit) : x(xInit), y(yInit), ptsVie(100), nbTresors(0) {}


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



// GESTION PV + TRÉSOR

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


void Aventurier::deplacer(int nx, int ny) {
    x = nx ;
    y = ny ;
}


bool Aventurier::estVivant () const {
    return ptsVie > 0 ;
}


void Aventurier::afficherStatut() const {
    std::cout << "Position : (" << x << ", " << y << ")\n";
    std::cout << "Points de vie : " << ptsVie << "/100\n";
    std::cout << "Inventaire : " << nbTresors << " tresor(s) coffrés\n\n";
}


// fonction qui gère les intéractions avec les cases
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

            if (choix == 'c') { // si le joueur choisit le combat, il joue au PFC avec le monstre

                /*std::cout << "Combat =>  perte de 10 PV.\n";
                pertePV(10) ;
                d.remplacerCase(x, y, CaseFactory::creerCase(TypeCase::PASSAGE)) ;
                return true ;*/
                
                int resultat = combatPFC() ;
                cout << resultat << endl;
                if (resultat == 1) {
                    std::cout << "Vous avez vaincu le monstre !\n" ;
                    d.remplacerCase(x, y, CaseFactory::creerCase(TypeCase::PASSAGE)) ;
                    return true ;
                } 
                else if (resultat == 0) {
                    std::cout << "Égalité ! Le monstre repart rôder...\n" ;
                    d.deplacerMonstreAleatoirement(x, y) ;
                    return false ;
                }
                else {
                    std::cout << "Le monstre vous a eu... -10 PV.\n" ;
                    pertePV(10) ;
                    d.remplacerCase(x, y, CaseFactory::creerCase(TypeCase::PASSAGE)) ;
                    return true ;
                }

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
            int degats = 5 + rand() % 16 ; // le joueur perdra entre 5 et 20 PV
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

// fonction qui gère toute la boucle de jeu
void Aventurier::boucledeJeu(Donjon& d){
    char clavier;
    d.marquerVisitee(x, y);

    vector<pair<int,int>> cheminActuel = {};

    while (estVivant() && d.getCase(x, y)->getTypeCase() != TypeCase::SORTIE){
        
        if (cheminActuel.empty())
            d.afficher(x, y);
        else
            d.afficherChemin(cheminActuel, x, y);

        cout << "ZQSD pour bouger | P pour afficher le chemin optimal | I = sauvegarder | M = charger\n\n";
        
        afficherStatut();

        cout << "Nombre de cases visitées : " << d.getNbCasesVisitees() << endl << endl;

        auto chemin = d.trouverChemin(d.getGrille(), {x, y}, {d.getSortieX(), d.getSortieY()});
        cout << "Distance à la sortie: " << chemin.size() - 1 << " cases\n\n";

        cin >> clavier;

        int nx = x;
        int ny = y;

        switch (clavier){
            case 'z': nx--; break;
            case 'q': ny--; break;
            case 's': nx++; break;
            case 'd': ny++; break;

            case 'p':
                cheminActuel = d.trouverChemin(
                    d.getGrille(),
                    {x, y},
                    {d.getSortieX(), d.getSortieY()}
                );
                break;

            case 'i':
                d.sauvegarder("donjon.txt");
                cout << "Donjon sauvegardé.\n";
                break;

            case 'm':
                d.charger("donjon.txt");
                cout << "Donjon chargé.\n";
                break;
            
            default:
                break;
        }

        // reset du chemin si le joueur se déplace
        if (clavier == 'z' || clavier == 'q' || clavier == 's' || clavier == 'd')
            cheminActuel = {};

        Case* cible = d.getCase(nx, ny);
        if(cible == nullptr || cible->getTypeCase() == TypeCase::MUR){
            cout << "Le déplacement est impossible." << endl;
            continue;
        }

        bool peutAvancer = resoudreCase(d, nx, ny);
        if (peutAvancer) {
            deplacer(nx, ny);
            d.marquerVisitee(nx, ny);
        }
    }

    if (!estVivant())
        cout << ROUGE << BOLD << "GAME OVER" << RESET << endl;
    else
        cout << VERT << BOLD << "BRAVO VOUS ETES SORTI !!" << RESET << endl;
}



// fonction qui gère le combat PFC

bool Aventurier::combatPFC() {
    int victoires = 0, defaites = 0 ;
    const vector<std::string> options = {"pierre", "feuille", "ciseaux"} ;

    for (int manche = 1 ; manche <= 3 ; ++manche) {
        cout << "\n----- MAAANCHE " << manche << " ----\n" ;
        cout << "Choisissez : p = pierre | f = feuille | c = ciseaux : " ;
        char coup ;
        cin >> coup ;

        int indexMonstre = std::rand() % 3 ;
        cout << "Le monstre joue : " << options[indexMonstre] << "\n" ;

        int indexJoueur = -1 ;
        if      (coup == 'p') indexJoueur = 0 ;
        else if (coup == 'f') indexJoueur = 1 ;
        else if (coup == 'c') indexJoueur = 2 ;
        else {
            cout << "Choix invalide, manche perdue !\n" ;
            ++defaites ;
            continue ;
        }

        if (indexJoueur == indexMonstre) {
            cout << "Égalité !\n" ;
        }
        else if ((indexJoueur == 0 && indexMonstre == 2) ||
                 (indexJoueur == 1 && indexMonstre == 0) ||
                 (indexJoueur == 2 && indexMonstre == 1)) {
            cout << VERT << "GG !\n" << RESET;
            ++victoires ;
        }
        else {
            cout << ROUGE << "LOSER VA !\n" << RESET;
            ++defaites ;
        }
    }

    cout << "\n Résultat : " << victoires << " victoire(s) / "
              << defaites << " défaite(s) \n" ;

    if (victoires > defaites) return 1 ;
    if (victoires == defaites) return 0 ;
    return -1 ;
}
