#pragma once
#include <SDL2/SDL.h>
#include "TextureManager.hpp"
//#include "Game.hpp"

class GameObject{
public:

int SCREEN_WIDTH = 1536;
int SCREEN_HEIGHT = 768;
    int x_pos;
   int y_pos;

    GameObject(const char* texturesheet, /*SDL_Renderer* ren,*/ int x, int y,int w, int h);
    ~GameObject();
    void free(SDL_Texture *texture);
    //void HandleInputAction(SDL_Event events);
    void HandleMove();
   void Update();
   void Render();
   int getX() const { return x_pos;}
   int getY() const { return y_pos;}
   int getWidth() const { return destRect.w;}
   int getHeight() const { return destRect.h;}

private:

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
    //SDL_Renderer* renderer;
};
