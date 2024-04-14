#include "Game.hpp"
SDL_Window* window;
const int SCREEN_WIDTH = 1536;
const int SCREEN_HEIGHT = 768;

const char*WINDOW_TITLE = "MY GAME";

Game* game = nullptr;

int main(int argc, char* argv[])
{
    game = new Game();

    game->initSDL(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    game->Start();
    const int FPS=50; //(Frame Per Second: so luong khung hinh muon chay trong mot giay)
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;
    while(game->running()){

        frameStart = SDL_GetTicks();

       game->update();
       game->render();

       game->handleEvents();

       frameTime = SDL_GetTicks() - frameStart;
       if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay-frameTime);
        }
    }

    game->clean();
    delete game;
    return 0;
}
