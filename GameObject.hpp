#pragma once
#include <SDL2/SDL.h>
#include "TextureManager.hpp"

class GameObject{
public:

int SCREEN_WIDTH = 1536;
int SCREEN_HEIGHT = 768;
    int x_pos;
    int y_pos;

    GameObject(const char* texturesheet,int x, int y,int w, int h);
    ~GameObject();

    void Update();
    void Render();
    int getX() const { return x_pos;}
    int getY() const { return y_pos;}
    int getWidth() const { return destRect.w;}
    int getHeight() const { return destRect.h;}

    bool checkCollision(const GameObject* obj_1, const GameObject* obj_2);

    SDL_Rect srcRect, destRect;

private:

    SDL_Texture* objTexture;
};
