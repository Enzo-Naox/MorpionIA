#include "Game.h"

void Game::chooseGame() const
{
    int choose;
    
    cout << "----- Morpion -----";
    cout << "\n1- Joueur contre Joueur";
    cout << "\n2- Joueur contre Ia";
    cout << "\n3- Ia contre Ia";
    cout << "\nVeuillez choisir votre mode de jeu ! ";
    cin >> choose;

    switch (choose) {
    case 1:
        cout << "Vous avez choisi Joueur contre Joueur." << endl;
        system("cls");
        startGamePVP();
        break;
    case 2:
        cout << "Vous avez choisi Joueur contre IA." << endl;
        startGamePVE();
        system("cls");
        break;
    case 3:
        cout << "Vous avez choisi IA contre IA." << endl;
        system("cls");
        break;
    default:
        cout << "Choix invalide. Veuillez réessayer." << endl;
        chooseGame();
        break;
    }
}

void Game::startGamePVP() const
{
    Board board;
    char joueur = 'X';
    int ligne, col;

    for (int tour = 0; tour < 9; ++tour) {
        board.afficherGrille();
        cout << "Joueur " << joueur << ", entrez votre mouvement (ligne et colonne): ";
        cin >> ligne >> col;

        Board::Resultat resultat = board.mouvementValide(ligne - 1, col - 1);
        while (resultat != Board::VALIDE) {
            if (resultat == Board::OCCUPE) {
                cout << "Cette case est deja occupee ! Reessayer (ligne et colonne): ";
            }
            else if (resultat == Board::ERREUR) {
                cout << "Coordonner erronee ! Reessayer (ligne et colonne): ";
            }
            cin >> ligne >> col;
            resultat = board.mouvementValide(ligne - 1, col - 1);
        }

        board.placerSymbole(ligne - 1, col - 1, joueur);

        if (board.verifierVictoire(joueur)) {
            board.afficherGrille();
            cout << "Joueur " << joueur << " a gagnee !" << endl;
            return;
        }

        joueur = (joueur == 'X') ? 'O' : 'X';

    }

    board.afficherGrille();
    cout << "La partie est terminée ! Match nul." << endl;
}

void Game::startGamePVE() const
{
    Board board;
    IA ia;
    char joueur = 'X'; // 'X' est le joueur humain
    int ligne, col;

    for (int tour = 0; tour < 9; ++tour) {
        board.afficherGrille();

        if (joueur == 'X') { // Joueur humain
            cout << "Joueur " << joueur << ", entrez votre mouvement (ligne et colonne): ";
            cin >> ligne >> col;

            Board::Resultat resultat = board.mouvementValide(ligne - 1, col - 1);
            while (resultat != Board::VALIDE) {
                if (resultat == Board::OCCUPE) {
                    cout << "Cette case est deja occupee ! Reessayer (ligne et colonne): ";
                }
                else if (resultat == Board::ERREUR) {
                    cout << "Coordonner erronee ! Reessayer (ligne et colonne): ";
                }
                cin >> ligne >> col;
                resultat = board.mouvementValide(ligne - 1, col - 1);
            }
            board.placerSymbole(ligne - 1, col - 1, joueur);
        }
        else { // IA
            ia.play(board);
        }

        joueur = (joueur == 'X') ? 'O' : 'X'; // Changer de joueur
    }

    board.afficherGrille();
    cout << "La partie est terminée ! Match nul." << endl;
}



