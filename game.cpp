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
GameObject *grid;
GameObject *lose;
GameObject *back_;
GameObject *box_locked;
GameObject *continue_;
GameObject *GameOver;
GameObject *Win;

int current[15][15]={0};
int mapn[15][15];
int clicked[15][15];
vector<int> title;

Map *_map;

GameNgram *Ngram = new GameNgram();
GameNgram *sgNgram = new GameNgram();
GameNgram *Ngame = new GameNgram();

SDL_Renderer *Game::renderer = nullptr;

const char* image_title;
const char* map_title;

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
    if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096)==-1)
    {
        std::cout << "Error Music" << std::endl;
    }
    sound1 =Mix_LoadWAV("music_game.wav");
    sound2 =Mix_LoadWAV("click_incorrect.wav");

   if(sound1==NULL||sound2==NULL)
        std::cout << "Error Load Music" << std::endl;


    background = new GameObject("Game Graphics/newbackground1.png",0,0,1536,768);
    startgame = new GameObject("Game Graphics/playgame.png",620,380,200,90);

    ground = new GameObject("Game Graphics/ground.png",0,0,1536,768);

    turtle = new GameObject("Game Graphics/Character/turtle.png",0,100,64,52);
    turtlerun = new GameObject("Game Graphics/Character/run.png",260,500,50,52);
    ogre = new GameObject("Game Graphics/Character/ogre.png",-10,650,55,58);
    box = new GameObject("Game Graphics/Box/Box.png",100,100,148,100);
    bgrn = new GameObject("Game Graphics/Asset 3.png",-3,-10,1572,794);
    heart = new GameObject("Game Graphics/heart.png",heartPosX , heartPosY, heartWidth,heartHeight);
    grid = new GameObject("Game Graphics/grid.png",300,225,525,525);
    lose = new GameObject("Game Graphics/lose.png",80,150,160,114);
    back_ = new GameObject("Game Graphics/back.png",70,90,145,50);
    continue_ = new GameObject("Game Graphics/continue.png",70,150,144,43);
    GameOver = new GameObject("Game Graphics/GameOver.png",900,100,510,568);
    Win = new GameObject("Game Graphics/Win.png",900,100,547,501);
    _map = new Map();
    LoadNgram("Nonogram.txt");
    ContinuePlay();
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
    box->Update();
    GameOver->Update();
    Win->Update();
}
void Game::render()
{

	SDL_RenderClear(renderer);
    ground->Render();
    _map->DrawMap();
    turtle->Render();
    box->Render();

    Nonogram();

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

                if(Collision->checkCollision(turtle, box)){
                    isNonogram = true;
                    isPlayNgram =true;
                    turtle->x_pos += 32;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouse_x, &mouse_y);

                if(event.button.button == SDL_BUTTON_LEFT){
                    if (mouse_x >= nonogram->getX() && mouse_x <= nonogram->getX() + nonogram->getWidth() && mouse_y >= nonogram->getY() && mouse_y <= nonogram->getY() + nonogram->getHeight() && isNonogram)
                    {
                        Ngram->handleEventNgramClickLeft(mouse_x, mouse_y,sound1,sound2);
                        std::cout << _heart << std::endl;
                    }
                    if(mouse_x >= back_->getX() && mouse_x <= back_->getX() + back_->getWidth() && mouse_y >= back_->getY() && mouse_y <= back_->getY() + back_->getHeight() && isNonogram){
                        isNonogram = false;
                        isPlayNgram = false;
                        if(_heart == 0) box = new GameObject("Game Graphics/Box/Box_locked.png",100,100,78,90);
                        box->Update();
                        box->Render();
                        SDL_RenderPresent(renderer);
                    }
                    if(mouse_x >= continue_->getX() && mouse_x <= continue_->getX() + continue_->getWidth() && mouse_y >= continue_->getY() && mouse_y <= continue_->getY() + continue_->getHeight() && isNonogram && isPlayNgram && sumClick == 225 ){
                        isPlayContinue = true;
                    }
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    if (mouse_x >= nonogram->getX() && mouse_x <= nonogram->getX() + nonogram->getWidth() && mouse_y >= nonogram->getY() && mouse_y <= nonogram->getY() + nonogram->getHeight() && isNonogram)
                    {
                        Ngram->handleEventNgramClickRight(mouse_x, mouse_y, sound1, sound2);
                    }
                }
                break;

            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mouse_x, &mouse_y);
                if(event.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)){
                    if (mouse_x >= nonogram->getX() && mouse_x <= nonogram->getX() + nonogram->getWidth() && mouse_y >= nonogram->getY() && mouse_y <= nonogram->getY() + nonogram->getHeight() && isNonogram)
                    {
                        Ngram->handleEventNgramClickLeft(mouse_x, mouse_y, sound1, sound2);
                        std::cout << _heart << std::endl;
                    }
                }
                if(event.motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)){
                    if (mouse_x >= nonogram->getX() && mouse_x <= nonogram->getX() + nonogram->getWidth() && mouse_y >= nonogram->getY() && mouse_y <= nonogram->getY() + nonogram->getHeight() && isNonogram)
                    {
                        Ngram->handleEventNgramClickRight(mouse_x, mouse_y,sound1, sound2);
                    }
                }
                break;

            default:
                break;
        }
    }
}

void Game::LoadMapNgram(const char* filepath)
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

void Game::LoadNgram(const char* filepath)
{
    std::ifstream file(filepath);
    if(!file.is_open()) return;
    int temp;
    while(file >> temp){
        title.push_back(temp);
    }
    for(int i=0;i<title.size();i++){
        std::cout << title[i] << "," << std::endl;
    }
    file.close();
}

void Game::Nonogram()
{
    if(isNonogram){
        bgrn->Update();
        grid->Update();
        lose->Update();
        back_->Update();
        continue_->Update();

        bgrn->Render();
        back_->Render();

        Ngame->renderArrRow(renderer, sgNgram->sg_row);
        Ngame->renderArrCol(renderer, sgNgram->sg_col);

        if(_heart == 0 ){

            lose->Render();
            nonogram->Render();
            GameOver->Render();
            isPlayNgram = false;
        }
    }
    if (isPlayNgram)
    {
        for (int i = 0; i < _heart; i++) {
            heart->x_pos = heartPosX + i * (heartWidth + 5);
            heart->Update();
            heart->Render();
        }
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                if (current[i][j] == 1 && clicked[i][j] != 3)
                {
                    color[i][j] = new GameObject(image_title, j * PUZZLE_SIZE + START_X_GRID, i * PUZZLE_SIZE + START_Y_GRID, PUZZLE_SIZE, PUZZLE_SIZE + 1);

                    color[i][j]->srcRect.x = j * PUZZLE_SIZE;
                    color[i][j]->srcRect.y = i * PUZZLE_SIZE;

                    clicked[i][j] = 3;
                    sumClick ++;

                }
                else if (current[i][j] == -2 && clicked[i][j] != 3)

                {
                    color[i][j] = new GameObject("Game Graphics/puzzle/x_red.png", j * PUZZLE_SIZE + START_X_GRID, i * PUZZLE_SIZE + START_Y_GRID, PUZZLE_SIZE, PUZZLE_SIZE);
                    clicked[i][j] = 3;
                    sumClick++;
                    _heart--;
                }
                 else if (current[i][j] == 2 && clicked[i][j] != 3)
                {
                    color[i][j] = new GameObject("Game Graphics/puzzle/x_black.png", j * PUZZLE_SIZE + START_X_GRID, i * PUZZLE_SIZE + START_Y_GRID, PUZZLE_SIZE, PUZZLE_SIZE);
                    clicked[i][j] = 3;
                    sumClick++;
                }
                else if (current[i][j] == -1 && clicked[i][j] != 3)

                {
                    color[i][j] = new GameObject("Game Graphics/puzzle/red.png", j * PUZZLE_SIZE + START_X_GRID, i * PUZZLE_SIZE + START_Y_GRID, PUZZLE_SIZE, PUZZLE_SIZE);
                    clicked[i][j] = 3;
                    sumClick++;
                    _heart--;
                }
                color[i][j]->Update();
                color[i][j]->Render();
            }
        }
        grid->Render();

        if(sumClick == 225 ) {
            if(!isPlayContinue){
                nonogram->Render();
                continue_->Render();
                if(title.size() == 0) Win->Render();
                //Ngame->updateScore(score);
                //std::cout << "score:" << score << std::endl;
                //Ngame->renderScore(renderer, Ngame->gFont, score,100,100);
                SDL_RenderPresent(renderer);
            }
            else ContinuePlay();

            int scoreToAdd = 5;
            score += scoreToAdd;
            Ngame->updateScore(score);
            std::cout << "score:" << score << std::endl;
            Ngame->renderScore(renderer, Ngame->gFont, score,100,100);
        }
    }

    std::cout << "Click:" << sumClick << std:: endl;
}

void Game::ContinuePlay()
{
    _heart = 3;
    score = 0;
    sumClick = 0;
    srand(time(0));
    index = rand() % 3;
    int t = title[index];
    _image_title = "Game Graphics/Nonogram/" + to_string(t) + ".png";
    _map_title = "Map/" + to_string(t) + ".txt";
    image_title = _image_title.c_str();
    map_title = _map_title.c_str();
    nonogram = new GameObject(image_title,300,225,525,525);
    nonogram->Update();
    LoadMapNgram(map_title);
    sgNgram->Suggest(mapn);
    title.erase(title.begin() + index);

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            color[i][j] = new GameObject("Game Graphics/puzzle/puzzle.png", j * PUZZLE_SIZE + START_X_GRID, i * PUZZLE_SIZE + START_Y_GRID, PUZZLE_SIZE, PUZZLE_SIZE);

            current[i][j]=0;
            clicked[i][j]=0;
        }
    }
    isPlayContinue = false;
    std::cout << "image" << image_title << "map" << map_title ;
}

void Game::del()
{
    background->~GameObject();
    startgame->~GameObject();
    ground->~GameObject();
    turtle->~GameObject();
    turtlerun->~GameObject();
    ogre->~GameObject();
    box->~GameObject();
    nonogram->~GameObject();
    bgrn->~GameObject();
    heart->~GameObject();
    bgrn->~GameObject();
    grid->~GameObject();
    lose->~GameObject();
    back_->~GameObject();
    continue_->~GameObject();

    for (int i     = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            color[i][j]->~GameObject();
        }
    }
    delete _map;
    delete mapn;
    Ngame->closeTTF();
}

void Game::clean()
{
    //del();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
