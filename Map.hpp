#pragma once
#include <fstream>

#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "GameNonogram.hpp"

class Map{
public:
    Map();
    ~Map();

    void LoadMap(const char* filepath);
    void DrawMap();
    void mapNgram();
    void LoadNgram(const char* filepath);
    void DrawNgram(int digit,int pos_x, int pos_y);

    int mapn[15][15];

private:
    SDL_Rect src, dest;
    SDL_Rect src_n, dest_n;

    SDL_Texture* grass;
    SDL_Texture* black;
    SDL_Texture* red;
    SDL_Texture* x_black;
    SDL_Texture* x_red;

    int map[24][48];
};

