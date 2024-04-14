#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "GameNonogram.hpp"

#include <iostream>
#include <vector>

class TextureManager;

class Game
{
public:

    int SCREEN_WIDTH = 1536;
    int SCREEN_HEIGHT = 768;
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
	void ButtonNonogram();

	bool running() { return isRunning; }
	//bool Nonogram() {return isNonogram;}
    static SDL_Renderer* renderer;

    SDL_Window* window;

    bool isRunning = true;
    bool isNonogram = true;

private:

    int srcRect_w,srcRect_h;
    int mouse_x, mouse_y;


    SDL_Event event;

};
