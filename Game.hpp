#pragma once
#include <fstream>
using namespace std;

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "GameNonogram.hpp"

#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

const int SCREEN_WIDTH = 1535;
const int SCREEN_HEIGHT = 750;
const int ROW = 15;
const int COL = 15;
const int map_image_ngram = 3;

class Game
{
public:
    int x_pos, y_pos;

    Game();
    ~Game();

    void logErrorAndExit(const char* msg, const char* error);
    void initSDL(const char* WINDOW_TITLE, int x_pos, int y_pos, int SCREEN_WIDTH, int SCREEN_HEIGHT,bool fullScreen);
    void handleEvents();
	void update();
	void render();
	void clean();
	void Start();
	void Nonogram();
	void LoadMapNgram(const char* filepath);
    void LoadNgram(const char* filepath);
	void ContinuePlay();
	void del();

	bool running() { return isRunning; }
    static SDL_Renderer* renderer;
    Mix_Chunk *sound1;
    Mix_Chunk *sound2;

    SDL_Window* window;

    bool isRunning = true;
    bool isNonogram = false;
    bool isPlayNgram = false;
    bool isPlayContinue = false;

    int srcRect_w,srcRect_h;

private:

    int mouse_x, mouse_y;

    SDL_Event event;

    int x_value = 32;

    int _heart = 3;
    int _heart1 = 2;
    int _heart2 = 3;
    int heartPosX = 60;
    int heartPosY = 180;
    int heartWidth = 42;
    int heartHeight = 35;
    int x,y;
    int sumClick = 0;
    string _image_title;
    string _map_title;
    int index;
    int score = 0;
};
