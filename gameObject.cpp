#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "game.hpp"

GameObject::GameObject(const char* texturesheet,/* SDL_Renderer* ren,*/ int x, int y, int w, int h)
{
    //renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet/*, ren*/);
    x_pos = x;
    y_pos = y;

    srcRect.w = w;
    srcRect.h = h;
}

void GameObject::HandleMove()
{
    destRect.x += x_pos;
    if(destRect.x < 0 || destRect.x + srcRect.w >= SCREEN_WIDTH)
    {
        destRect.x -= x_pos;
    }
    destRect.y += y_pos;
    if(destRect.y < 0 || destRect.y + srcRect.h >= SCREEN_HEIGHT)
    {
        destRect.x -= x_pos;
    }
}

void GameObject::Update()
{

    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = x_pos;
    destRect.y = y_pos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;

}
void GameObject::free(SDL_Texture *texture)
{
    SDL_DestroyTexture(texture);
    texture=nullptr;
}
void GameObject::Render()
{
    SDL_RenderCopy(/*renderer*/Game::renderer, objTexture, &srcRect, &destRect);
}
