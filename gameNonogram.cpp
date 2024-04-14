#include "GameNonogram.hpp"

extern GameObject* nonogram;
extern GameObject* startgame;
GameObject* ngram = new GameObject("Game Graphics/puzzle/black.png",550,150,35,35);

extern Map* _mapNgram;

Game* quit;

GameNgram::GameNgram()
{
}

GameNgram::~GameNgram()
{}

void GameNgram::Ngram()
{
    handleEventNgram();
    std::cout << "true" << std::endl;
    //quit->isNonogram = false;
    //quit->isRunning = false;
    std::cout << "false" << std::endl;
}

void GameNgram::handleEventNgram()
{
    while (cnt != 5) {
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT :
                isQNgram = false;
                quit->isNonogram = false;
                quit->isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x_mouse, &y_mouse);

                if(x_mouse >= nonogram->getX() && x_mouse <= nonogram->getX() + nonogram->getWidth() && y_mouse >= nonogram->getY() && y_mouse <= nonogram->getY() + nonogram->getHeight())
                {
                    if(event.button.button == SDL_BUTTON_LEFT){

                        pos_x = (y_mouse - START_Y_GRID) / PUZZLE_SIZE;
                        pos_y = (x_mouse - START_X_GRID) / PUZZLE_SIZE;
                        std::cout << x_mouse << " " << pos_x << std::endl;
                        std::cout << y_mouse << " " << pos_y << std::endl;
                        for(int i=0;i<15;i++){
                            for(int j=0;j<15;j++){
                                std::cout << _mapNgram->mapn[i][j] << " ";
                            }
                            std::cout << std::endl;
                        }
                        if(_mapNgram->mapn[pos_x][pos_y] == 1) current[pos_x][pos_y]=1;
                        else{
                                current[pos_x][pos_y]=2;
                        }
                        std::cout << _mapNgram->mapn[pos_x][pos_y] << " " << current[pos_x][pos_y] << std::endl;
                        _mapNgram->DrawNgram(current[pos_x][pos_y],pos_x,pos_y);
                        //SDL_Delay(2000);

                    }
                    if(event.button.button == SDL_BUTTON_RIGHT){
                        pos_x = (x_mouse - START_X_GRID) / PUZZLE_SIZE;
                        pos_y = (y_mouse - START_Y_GRID) / PUZZLE_SIZE;
                        if(_mapNgram->mapn[pos_x][pos_y] == 0) current[pos_x][pos_y]=0;
                        else current[pos_x][pos_y]=3;
                        _mapNgram->DrawNgram(current[pos_x][pos_y],pos_x,pos_y);

                    }
                    cnt ++;
                }
                break;

            default:
                break;
        }
    //}
    /*if(cnt == 5){
        quit->isNonogram = false;
        quit->isRunning = false;*/
    }
    quit->isNonogram = false;
}
