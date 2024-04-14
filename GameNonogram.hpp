#pragma once

#include <SDL2/SDL.h>

#include "GameObject.hpp"
#include "Map.hpp"
#include "Game.hpp"

const int START_X_GRID = 600;
const int START_Y_GRID = 200;
const int PUZZLE_SIZE = 35;

class GameNgram
{
public:
    GameNgram();
    ~GameNgram();

    void Ngram();
    void handleEventNgram();

    int x_mouse,y_mouse;

    int current[15][15];
private:
    SDL_Renderer* renderer;
    SDL_Event event;

    int pos_x, pos_y;

    bool isQNgram = true;
    int cnt=0;
};
