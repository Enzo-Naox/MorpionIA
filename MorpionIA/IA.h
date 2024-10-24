#pragma once
#include <iostream>
#include <vector>
#include "Board.h"
#include <algorithm>

class IA {
    public:
        int minimax(Board& board, bool isMaximizing);
        int evaluate(Board& board);
        bool isGameOver(Board& board);
        void play(Board& board);

    private:    
};

