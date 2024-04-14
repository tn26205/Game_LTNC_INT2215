#include "Game.hpp"

GameObject* background;
GameObject* startgame;
GameObject* ground;
GameObject* turtle;
GameObject* turtlerun;
GameObject* ogre;
GameObject* box;
GameObject* nonogram;

Map* _map;
Map* _mapNgram;

GameNgram* Ngram;

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}

Game::~Game()
{}

void Game::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Game::initSDL(const char* WINDOW_TITLE, int x_pos, int y_pos, int SCREEN_WIDTH, int SCREEN_HEIGHT,bool fullScreen)
{
    int flags = 0;
    if(fullScreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) logErrorAndExit("SDL_Init", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) logErrorAndExit( "SDL_image error:", IMG_GetError());

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }
    else logErrorAndExit("CreateRenderer", SDL_GetError());

    background = new GameObject("Game Graphics/newbackground1.png",0,0,1536,768);
    startgame = new GameObject("Game Graphics/playgame.png",620,380,200,90);

    ground = new GameObject("Game Graphics/ground.png",0,0,1536,768);
    //grass = new GameObject("Game Graphics/grass/Asset 1.png",-1,-1,32,30);
    turtle = new GameObject("Game Graphics/Character/turtle.png",0,100,65,52);
    turtlerun = new GameObject("Game Graphics/Character/run.png",260,500,50,52);
    ogre = new GameObject("Game Graphics/Character/ogre.png",-10,650,55,58);
    box = new GameObject("Game Graphics/Box.png",100,100,61,68);
    nonogram = new GameObject("Game Graphics/nonogram.png",600,200,525,525);
    _map = new Map();
    _mapNgram = new Map();

}

void Game::Start()
{
    background->Update();
    startgame->Update();

    background->Render();
    startgame->Render();

	SDL_RenderPresent(renderer);
	while(SDL_PollEvent(&event)){
        switch (event.type)
        {
            case SDL_QUIT :
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouse_x, &mouse_y);

                if(event.button.button == SDL_BUTTON_LEFT){
                    if(mouse_x >= startgame->getX() && mouse_x <= startgame->getX() + startgame->getWidth() &&
                   mouse_y >= startgame->getY() && mouse_y <= startgame->getY() + startgame->getHeight()){
                       isRunning = true;
                    }
                }
                break;
            default:
                break;
        }
	}
}

void Game::update()
{
    ground->Update();
    turtle->Update();
    turtlerun->Update();
    ogre->Update();
    turtlerun->x_pos+=2;
    turtlerun->y_pos--;
    ogre->x_pos+=2;
    ogre->y_pos--;
    box->Update();

    nonogram->Update();

    turtle->HandleMove();
}
void Game::render()
{
	SDL_RenderClear(renderer);
    ground->Render();

    _map->DrawMap();
    //_map->DrawNgram(0,0,0);
    turtle->Render();
    turtlerun->Render();
    ogre->Render();
    box->Render();
    //nonogram->Render();
    //nonogram->Render();
	SDL_RenderPresent(renderer);
}
void Game::handleEvents()
{
    //while (SDL_PollEvent(&event)) {
    SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT :
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        turtle->y_pos -= 32;
                        break;
                    case SDLK_DOWN:
                        turtle->y_pos += 32;
                        break;
                    case SDLK_RIGHT:
                        turtle->x_pos += 32;
                        break;
                    case SDLK_LEFT:
                        turtle->x_pos -= 32;
                        break;
                    default:
                        break;
                    }
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouse_x, &mouse_y);

                if(event.button.button == SDL_BUTTON_LEFT){
                   if(mouse_x >= box->getX() && mouse_x <= box->getX() + box->getWidth() && mouse_y >= box->getY() && mouse_y <= box->getY() + box->getHeight())
                    {
                        while(isNonogram){
                            nonogram->Render();
                            SDL_RenderPresent(renderer);
                            Ngram->Ngram();
                        }
                        std::cout << "nonogram";
                        std::cout << "run" << std::endl;
                        isRunning = false;
                   }
                }
                break;

            default:
                break;
        }
    //}
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

