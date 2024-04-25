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

    srcRect.x = 0;
    srcRect.y = 0;
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
    destRect.x = x_pos;
    destRect.y = y_pos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;

}
void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

bool GameObject::checkCollision(const GameObject* obj_1, const GameObject* obj_2)
{
    return (obj_1->destRect.x < obj_2->destRect.x + obj_2->destRect.w/2-20 &&
            obj_1->destRect.x + obj_1->destRect.w > obj_2->destRect.x &&
            obj_1->destRect.y < obj_2->destRect.y + obj_2->destRect.h &&
            obj_1->destRect.y + obj_1->destRect.h > obj_2->destRect.y);
}
/*bool GameObject::checkCollision(const GameObject* obj_1, const Gam* obj_2)
{
    return (obj_1->destRect.x < obj_2->dest.x + obj_2->dest.w/2-20 &&
            obj_1->destRect.x + obj_1->destRect.w > obj_2->dest.x &&
            obj_1->destRect.y < obj_2->dest.y + obj_2->dest.h &&
            obj_1->destRect.y + obj_1->destRect.h > obj_2->dest.y);
}*/


