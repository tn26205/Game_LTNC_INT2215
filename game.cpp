#include "Game.hpp"

GameObject *background;
GameObject *startgame;
GameObject *ground;
GameObject *turtle;
GameObject *turtlerun;
GameObject *ogre;
GameObject *box;
GameObject *nonogram;
GameObject *color[ROW][COL];
GameObject *Collision;
GameObject *heart;
GameObject *bgrn;

int current[15][15]={0};
int mapn[15][15];
int clicked[15][15];

Map *_map;

GameNgram *Ngram = new GameNgram();
GameNgram *sgNgram = new GameNgram();
GameNgram *Ngame = new GameNgram();

SDL_Renderer *Game::renderer = nullptr;

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

    if (!Ngame->initTTF(renderer)) {
        std::cout << "Error" << std::endl;
    }

    background = new GameObject("Game Graphics/newbackground1.png",0,0,1536,768);
    startgame = new GameObject("Game Graphics/playgame.png",620,380,200,90);

    ground = new GameObject("Game Graphics/ground.png",0,0,1536,768);

    turtle = new GameObject("Game Graphics/Character/turtle.png",0,100,65,52);
    turtlerun = new GameObject("Game Graphics/Character/run.png",260,500,50,52);
    ogre = new GameObject("Game Graphics/Character/ogre.png",-10,650,55,58);
    box = new GameObject("Game Graphics/Box.png",100,100,61,68);
    nonogram = new GameObject("Game Graphics/Nonogram/1.png",300,225,525,525);
    bgrn = new GameObject("Game Graphics/Asset 3.png",-3,-10,1572,794);

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            color[i][j] = new GameObject("Game Graphics/puzzle/puzzle.png", j * PUZZLE_SIZE + START_X_GRID, i * PUZZLE_SIZE + START_Y_GRID, PUZZLE_SIZE, PUZZLE_SIZE);
        }
    }
    _map = new Map();

    LoadNgram("mapNgram.txt");
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            std::cout << mapn[i][j] << " ";
        }
        std::cout << std::endl;
    }
    sgNgram->Suggest(mapn);
}

void Game::Start()
{
    SDL_RenderClear(renderer);
    background->Update();
    startgame->Update();

    background->Render();
    startgame->Render();

	SDL_RenderPresent(renderer);

	while(SDL_PollEvent(&event)){
        switch (event.type)
        {
            case SDL_QUIT :
                clean();
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
    //ogre->x_pos+=2;
    //ogre->y_pos--;
    box->Update();
    bgrn->Update();

    if (isNonogram)
    {
        nonogram->Update();

        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                if (current[i][j] == 1 && clicked[i][j] != 3)
                {
                    color[i][j] = new GameObject("Game Graphics/puzzle/black.png", j * PUZZLE_SIZE + START_X_GRID, i * PUZZLE_SIZE + START_Y_GRID, PUZZLE_SIZE, PUZZLE_SIZE + 1);
                    /*delete color[i][j];
                    color[i][j] = nullptr;
                    clicked[i][j] = 3;*/
                }
                else if (current[i][j] == 2 && clicked[i][j] != 3)

                {
                    color[i][j] = new GameObject("Game Graphics/puzzle/x_red.png", j * PUZZLE_SIZE + START_X_GRID, i * PUZZLE_SIZE + START_Y_GRID, PUZZLE_SIZE, PUZZLE_SIZE);
                    clicked[i][j] = 3;
                    _heart--;
                }
                 else if (current[i][j] == -1 && clicked[i][j] != 3)
                {
                    color[i][j] = new GameObject("Game Graphics/puzzle/x_black.png", j * PUZZLE_SIZE + START_X_GRID, i * PUZZLE_SIZE + START_Y_GRID, PUZZLE_SIZE, PUZZLE_SIZE);
                    clicked[i][j] = 3;
                }
                else if (current[i][j] == -2 && clicked[i][j] != 3)

                {
                    color[i][j] = new GameObject("Game Graphics/puzzle/red.png", j * PUZZLE_SIZE + START_X_GRID, i * PUZZLE_SIZE + START_Y_GRID, PUZZLE_SIZE, PUZZLE_SIZE);
                    clicked[i][j] = 3;
                    _heart--;
                }
                color[i][j]->Update();
            }
        }
    }
}
void Game::render()
{
	SDL_RenderClear(renderer);
    ground->Render();

    _map->DrawMap();

    turtle->Render();
    //turtlerun->Render();
    //ogre->Render();
    box->Render();

    if (isNonogram)
    {
        bgrn->Render();
        Nonogram->Render();
        for (int i = 0; i < _heart; i++) {
            heart = new GameObject("Game Graphics/heart.png",heartPosX + i * (heartWidth + 5), heartPosY, heartWidth,heartHeight);
            heart->Update();
            heart->Render();
        }

        Ngame->renderArrRow(renderer, sgNgram->sg_row);
        Ngame->renderArrCol(renderer, sgNgram->sg_col);

        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                color[i][j]->Render();
            }
        }
    }
	SDL_RenderPresent(renderer);
}
void Game::handleEvents()
{
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_QUIT :
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        if(turtle->y_pos > 32){
                            turtle->y_pos -= 32;
                        }
                        break;
                    case SDLK_DOWN:
                        if(turtle->y_pos + turtle->srcRect.h < SCREEN_HEIGHT) turtle->y_pos += 32;
                        std::cout << turtle->y_pos + turtle->srcRect.h << " ";
                        break;
                    case SDLK_RIGHT:
                        if(turtle->x_pos + turtle->srcRect.w < SCREEN_WIDTH) turtle->x_pos += 32;
                        break;
                    case SDLK_LEFT:
                        if(turtle->x_pos > 16) turtle->x_pos -= 32;
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
                        isNonogram = true;
                        std::cout << "Nonogram" << std::endl;

                    }
                    else if (mouse_x >= nonogram->getX() && mouse_x <= nonogram->getX() + nonogram->getWidth() && mouse_y >= nonogram->getY() && mouse_y <= nonogram->getY() + nonogram->getHeight() && isNonogram)
                    {
                        Ngram->handleEventNgramClickLeft(mouse_x, mouse_y);
                        std::cout << _heart << std::endl;
                        if(_heart == 0) isNonogram = false;
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    if (mouse_x >= nonogram->getX() && mouse_x <= nonogram->getX() + nonogram->getWidth() && mouse_y >= nonogram->getY() && mouse_y <= nonogram->getY() + nonogram->getHeight() && isNonogram)
                    {
                        Ngram->handleEventNgramClickRight(mouse_x, mouse_y);
                        if(_heart == 0) isNonogram = false;
                    }
                }
                break;

            default:
                break;
        }
    }
}

void Game::LoadNgram(const char* filepath)
{
    std::ifstream file(filepath);
    if(!file.is_open()) return;

    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            file >> mapn[i][j];
        }
    }
    file.close();
}

void Game::clean()
{
    Ngame->closeTTF();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

