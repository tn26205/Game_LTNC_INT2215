#include "Play.hpp"

//GameObject* nonogram = new GameObject("Game Graphics/nonogram-01.png",0,0,525,525);

void Play::checkClick(){
    /*while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouse_x, &mouse_y);

                if(event.button.button == SDL_BUTTON_LEFT){
                    if(mouse_x >= nonogram.->getX() && mouse_x <= nonogram->getX() + nonogram->getWidth() && mouse_y >= nonogram->getY() && mouse_y <= nonogram->getY() + nonogram->getHeight()){

                    pos_x = (mouse_x - START_X_GRID) / PUZZLE_SIZE - 1;
                    pos_y = (mouse_y - START_Y_GRID) / PUZZLE_SIZE - 1;
                    if(mapNgram.mapn[pos_x][pos_y] == 1) current[pos_x][pos_y]=1;
                    else current[pos_x][pos_y]=2;
                }
                if(event.button.button == SDL_BUTTON_RIGHT){
                    pos_x = (mouse_x - START_X_GRID) / PUZZLE_SIZE - 1;
                    pos_y = (mouse_y - START_Y_GRID) / PUZZLE_SIZE - 1;
                    if(mapNgram.mapn[pos_x][pos_y] == 0) current[pos_x][pos_y]=0;
                    else current[pos_x][pos_y]=-1;
                }
                break;
            default:
                break;
            }
        }
    }*/
}


#include "GameNonogram.hpp"

GameNonogram::GameNonogram(){}

GameNonogram::~GameNonogram(){}

void GameNonogram::drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Đặt màu trắng
    for (int x = 0; x < _SCREEN_WIDTH; x += GRID_SIZE) {
        SDL_RenderDrawLine(renderer, x, 0, x, _SCREEN_HEIGHT); // Vẽ đường dọc
    }
    for (int y = 0; y < _SCREEN_HEIGHT; y += GRID_SIZE) {
        SDL_RenderDrawLine(renderer, 0, y, _SCREEN_WIDTH, y); // Vẽ đường ngang
    }
}

void GameNonogram::Play(){
    /*bool quit = false;
    SDL_Event e;
    while (!quit) {
        // Xử lý sự kiện
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }*/
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Đặt màu trang
        SDL_RenderClear(renderer);

        // Vẽ lưới

        drawGrid(renderer);

        // Cập nhật renderer
        SDL_RenderPresent(renderer);
    //}
}

/*void playNonogram()
{
    bool quit = false;
    // khoi tao cua so game.....

    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                handleMouseClick(mouseX, mouseY);
            }
        }

        render(renderer); // Vẽ lại trạng thái của trò chơi trên renderer

        // Giới hạn tốc độ khung hình của game
        SDL_Delay(16); // Tạo một khoảng thời gian ngắn trước khi vòng lặp tiếp tục
    }

    cleanUp();
}

void handleMouseClick(int x, int y){
    int grid_x = x / (800 / width);
    int grid_y = y / (600/ height);
    int pos = grid_y * width + grid_x;

    if(puzzle[pos] == SOLID){
        puzzle[pos] = UNKNOWN;
    }else{
        puzzle[pos] = SOLID;
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 215, 215, 215, 255);
    SDL_RenderClear(renderer);

    // Vẽ các ô trong bảng puzzle
    SDL_Rect cellRect;
    cellRect.w = 800 / width;
    cellRect.h = 600 / height;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int pos = i * width + j;
            if (puzzle[pos] == SOLID) {
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Màu solid
            } else if (puzzle[pos] == DOT) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu dot (lỗi)
            } else {
                SDL_SetRenderDrawColor(renderer, 215, 215, 215, 255); // Màu mặc định
            }
            cellRect.x = j * (800 / width);
            cellRect.y = i * (600 / height);
            SDL_RenderFillRect(renderer, &cellRect);
        }
    }

    SDL_RenderPresent(renderer);
}*/
