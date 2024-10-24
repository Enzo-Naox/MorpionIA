#include "IA.h"

int IA::evaluate(Board& board) {
    if (board.verifierVictoire('O')) return 10;  // IA gagne
    if (board.verifierVictoire('X')) return -10; // Joueur humain perd
    return 0; // Match nul ou jeu en cours
}


bool IA::isGameOver(Board& board) {
    return board.verifierVictoire('X') || board.verifierVictoire('O') || board.isFull();
}

int IA::minimax(Board& board, bool isMaximizing) {
    int score = evaluate(board);

    if (score != 0) return score; // Retourne le score si le jeu est terminé

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.mouvementValide(i, j) == Board::VALIDE) {
                    board.placerSymbole(i, j, 'O'); // IA joue
                    bestScore = std::max(bestScore, minimax(board, false));
                    board.Rollback(i, j); // Annule le coup
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = 1000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.mouvementValide(i, j) == Board::VALIDE) {
                    board.placerSymbole(i, j, 'X'); // Joueur humain joue
                    bestScore = std::min(bestScore, minimax(board, true));
                    board.Rollback(i, j); // Annule le coup
                }
            }
        }
        return bestScore;
    }
}

void IA::play(Board& board) {
    // Vérifie d'abord si l'IA peut gagner
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.mouvementValide(i, j) == Board::VALIDE) {
                board.placerSymbole(i, j, 'O'); // IA joue
                if (board.verifierVictoire('O')) {
                    cout << "IA a joue en (" << (i + 1) << ", " << (j + 1) << ")" << endl;
                    return; // Gagne et sort
                }
                board.Rollback(i, j); // Annule le coup
            }
        }
    }

    // Vérifie si l'adversaire peut gagner et bloque
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.mouvementValide(i, j) == Board::VALIDE) {
                board.placerSymbole(i, j, 'X'); // Adversaire joue
                if (board.verifierVictoire('X')) {
                    board.placerSymbole(i, j, 'O'); // Bloque l'adversaire
                    cout << "IA a bloque en (" << (i + 1) << ", " << (j + 1) << ")" << endl;
                    return; // Bloque et sort
                }
                board.Rollback(i, j); // Annule le coup
            }
        }
    }

    // Sinon, utilise Minimax pour déterminer le meilleur coup
    int bestValue = -1000;
    int bestMove[2] = { -1, -1 };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.mouvementValide(i, j) == Board::VALIDE) {
                board.placerSymbole(i, j, 'O'); // IA joue
                int moveValue = minimax(board, false);
                board.Rollback(i, j); // Annule le coup
                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }

    board.placerSymbole(bestMove[0], bestMove[1], 'O'); // Place le meilleur coup
    cout << "IA a joue en (" << (bestMove[0] + 1) << ", " << (bestMove[1] + 1) << ")" << endl;
}
