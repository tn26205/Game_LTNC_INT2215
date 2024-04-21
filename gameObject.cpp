#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "game.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y, int w, int h)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    x_pos = x;
    y_pos = y;

    srcRect.w = w;
    srcRect.h = h;
}

GameObject::~GameObject()
{
    if (objTexture != nullptr)
    {
        SDL_DestroyTexture(objTexture);
        objTexture = nullptr;
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
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

/*bool GameObject::checkCollision(*const SDL_Rect& obj_1, const SDL_Rect& obj_2*)
{
    int left_1 = obj_1.x;
    int right_1 = obj_1.x + obj_1.w;
    int top_1 = obj_1.y;
    int bottom_1 = obj_1.y + obj_1.h;

    int left_2 = obj_2.x;
    int right_2 = obj_2.x + obj_2.w;
    int top_2 = obj_2.y;
    int bottom_2 = obj_2.y + obj_2.h;

    if (left_1 > left_2 && left_1 < right_2)
    {
        if (top_1 > top_2 && top_1 < bottom_2)
        {
          return true;
        }

        if (bottom_1 > top_2 && bottom_1 < bottom_2)
        {
          return true;
        }
    }
    if(right_1 > left_2 && right_1 < right_2){
        if (top_1 > top_2 && top_1 < bottom_2)
        {
            return true;
        }
        if (bottom_1 > top_2 && bottom_1 < bottom_2)
        {
          return true;
        }
    }

    if (left_2 > left_1 && left_2 < right_1)
    {
        if (top_2 > top_1 && top_2 < bottom_1)
        {
          return true;
        }
        if (bottom_2 > top_1 && bottom_2 < bottom_1)
        {
          return true;
        }
    }

    if (right_2 > left_1 && right_2 < right_1)
    {
        if (top_2 > top_1 && top_2 < bottom_1)
        {
          return true;
        }
        if (bottom_2 > top_1 && bottom_2 < bottom_1)
        {
          return true;
        }
    }

    if (top_1 == top_2 && right_1 == right_2 && bottom_1 == bottom_2)
    {
        return true;
    }

    return false;

}*/
/*bool GameObject::checkCollision(const SDL_Rect& obj_1, const SDL_Rect& obj_2)
{
    return (obj_1.x < obj_2.x + obj_2.w &&
            obj_1.x + obj_1.w > obj_2.x &&
            obj_1.y < obj_2.y + obj_2.h &&
            obj_1.y + obj_1.h > obj_2.y);
}*/


