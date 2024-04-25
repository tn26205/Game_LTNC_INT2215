#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "Map.hpp"
#include "Game.hpp"
#include "GameObject.hpp"

class Play{
public:
    void checkClick();

    std::vector<std::vector<int>> current;
    //int pos_x, pos_y;
private:
    int mouse_x,mouse_y;
    SDL_Event event;
    //Map mapNgram;
};

#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
//#include "Game.hpp"

const int _SCREEN_WIDTH = 640;
const int _SCREEN_HEIGHT = 480;
const int GRID_SIZE = 20;

class GameNonogram
{
public:
    GameNonogram();
    ~GameNonogram();

    //void playNonogram();

    void drawGrid(SDL_Renderer* renderer);
    void Play();

    //static SDL_Renderer* ren;
private:
    int width, height;
    std::vector<int> puzzle;
    SDL_Renderer* renderer;
    SDL_Event event;
};
