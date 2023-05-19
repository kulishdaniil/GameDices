#pragma once
#include "Shered.h"

void Game(SDL_Renderer*& renderer, Mix_Chunk* ButtonTapSound, Mix_Chunk* DiceRollingSound, Mix_Music* GameMusic, int GameVolume, int& GameCount, int& WinsCountInRow, int& SmallBackCount, int& BigBackCount);