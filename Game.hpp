#pragma once
#include <fstream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "GameNonogram.hpp"

#include <iostream>
#include <vector>

const int SCREEN_WIDTH = 1535;
const int SCREEN_HEIGHT = 750;
const int ROW = 15;
const int COL = 15;

class Game
{
public:
    int x_pos, y_pos;

    Game();
    ~Game();

    void logErrorAndExit(const char* msg, const char* error);
    void initSDL(const char* WINDOW_TITLE, int x_pos, int y_pos, int SCREEN_WIDTH, int SCREEN_HEIGHT,bool fullScreen);
    void handleMouse();
    void handleKeyDownEvent(SDL_Keycode keycode);
    void handleMousClickEvent(SDL_MouseButtonEvent& buttonEvent);
    void handleNonogram(int mouse_x, int mouse_y);
    void handleEvents();
	void update();
	void render();
	void clean();
	void Start();
	void Nonogram();
	void LoadNgram(const char* filepath);

	bool running() { return isRunning; }
    static SDL_Renderer* renderer;

    SDL_Window* window;

    bool isRunning = true;
    bool isNonogram = false;

    int srcRect_w,srcRect_h;

private:

    int mouse_x, mouse_y;

    SDL_Event event;

    int x_value = 32;

    int _heart = 3;
    int heartPosX = 60;
    int heartPosY = 180;
    int heartWidth = 42;
    int heartHeight = 35;

};
