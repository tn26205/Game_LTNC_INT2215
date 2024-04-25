#include "GameNonogram.hpp"

extern GameObject* nonogram;
extern GameObject* startgame;
extern int current[15][15];
extern int mapn[15][15];

Map *mapNgram;

Game *quit;

GameNgram::GameNgram()
{
}

GameNgram::~GameNgram()
{}
void GameNgram::handleEventNgramClickLeft(int &mouse_x, int &mouse_y,Mix_Chunk* sound1, Mix_Chunk *sound2)
{
    std::cout << "Click left: " << mouse_x << " " << mouse_y << std::endl;
    int pos_x = (int)((mouse_y - START_Y_GRID) / PUZZLE_SIZE);
    int pos_y = (int)((mouse_x - START_X_GRID) / PUZZLE_SIZE);
    std::cout << pos_x << " " << pos_y << std::endl;

    if (mapn[pos_x][pos_y] == 1){
        current[pos_x][pos_y] = 1;
         Mix_PlayChannel(-1,sound1,0);
    }
    else{
        current[pos_x][pos_y] = -2;
        Mix_PlayChannel(-1,sound2,0);
    }

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            std::cout << current[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void GameNgram::handleEventNgramClickRight(int &mouse_x, int &mouse_y,Mix_Chunk *sound1, Mix_Chunk *sound2)
{
    std::cout << "Click right: " << mouse_x << " " << mouse_y << std::endl;
    int pos_x = (int)((mouse_y - START_Y_GRID) / PUZZLE_SIZE);
    int pos_y = (int)((mouse_x - START_X_GRID) / PUZZLE_SIZE);
    std::cout << pos_x << " " << pos_y << std::endl;

    if (mapn[pos_x][pos_y] == 0){
         current[pos_x][pos_y] = 2;
         Mix_PlayChannel(-1,sound1,0);
    }
    else{
         current[pos_x][pos_y] = -1;
         Mix_PlayChannel(-1,sound2,0);
    }

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            std::cout << current[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void GameNgram::Suggest(int a[15][15]){
    sg_row.clear();
    sg_col.clear();

    for (int i = 0; i < 15; i++) {
        row_segments.clear();
        int check = 0;

        for (int j = 0; j < 15; j++){
            cnt = 0;
            if (a[i][j] == 0) {
                if (check > 0) {
                    row_segments.push_back(check);
                    cnt++;
                    check = 0;
                }
            } else if (a[i][j] == 1) {
                check++;
            }
        }

        if (check > 0) {
            row_segments.push_back(check);
            cnt++;
        }
        if(cnt>max_row) max_row = cnt;
        sg_row.push_back(row_segments);
    }

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < sg_row[i].size(); j++) {
            cout << sg_row[i][j] << " ";
        }
        cout << endl;
    }


    for (int j = 0; j < 15; j++) {
        row_segments.clear();
        int check = 0;
        cnt = 0;

        for (int i = 0; i < 15; i++) {
            if (a[i][j] == 0) {
                if (check > 0) {
                    row_segments.push_back(check);
                    check = 0;
                    cnt++;
                }
            } else if (a[i][j] == 1) {
                check++;
            }
        }

        if (check > 0) {
            row_segments.push_back(check);
            cnt++ ;
        }
        if(cnt>max_col) max_col = cnt;
        sg_col.push_back(row_segments);
    }

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < sg_col[i].size(); j++) {
            cout << sg_col[i][j] << " ";
        }
        cout << endl;
    }
}
bool GameNgram::initTTF(SDL_Renderer* renderer)
{
    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    gFont = TTF_OpenFont("lazy.ttf", 18);
    if (gFont == nullptr) {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void GameNgram::closeTTF()
{
    if (gFont != nullptr) {
        TTF_CloseFont(gFont);
        gFont = nullptr;
    }
    TTF_Quit();
}


void GameNgram::renderArrRow(SDL_Renderer* renderer, const vector<vector<int>>& arr)
{
    SDL_Color textColor = { 225, 225, 225 };
    int text_x;
    int text_y = SG_X_ROW;
    int lineHeight = 35;
    int space = 40;
    for (int t = 0; t < 15; t++) {
        for (int f = 0; f < arr[t].size(); f++) {
            text_x = SG_X_COL + (max_row - arr[t].size() + f + 1) * space;
            string text = to_string(arr[t][f]);
            SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
            if (textSurface != nullptr) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture != nullptr) {
                    SDL_Rect textRect = { text_x, text_y, textSurface->w, textSurface->h };
                    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
                    SDL_DestroyTexture(textTexture);
                }
                SDL_FreeSurface(textSurface);
            }
        }
        text_y += lineHeight;
    }
}

void GameNgram::renderArrCol(SDL_Renderer* renderer, const vector<vector<int>>& arr)
{
    SDL_Color textColor = { 225, 225, 225 };
    int text_x = SG_Y_ROW;
    int text_y;
    int lineHeight = 30;
    int space = 35;
    for (int t = 0; t < 15; t++) {
        for (int f = 0; f < arr[t].size(); f++) {
            text_y = SG_Y_COL + (max_col - arr[t].size() + f + 1) * lineHeight;
            string text = to_string(arr[t][f]);
            SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
            if (textSurface != nullptr) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture != nullptr) {
                    SDL_Rect textRect = { text_x, text_y, textSurface->w, textSurface->h };
                    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
                    SDL_DestroyTexture(textTexture);
                }
                SDL_FreeSurface(textSurface);
            }
        }
        text_x += space;
    }
}

/*void GameNgram::printTTF(SDL_Surface* textSurface, string text, SDL_Color textColor, SDL_Renderer* renderer,SDL_Rect textRect){
    //SDL_Color textColor = {225, 225, 225};
    textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    if (textSurface != nullptr) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture != nullptr) {
            //SDL_Rect textRect = { text_x, text_y, textSurface->w, textSurface->h };
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

            SDL_DestroyTexture(textTexture);
        }

        SDL_FreeSurface(textSurface);
    }
}*/
void GameNgram::renderScore(SDL_Renderer* renderer, TTF_Font* font, int score, int x, int y) {

    std::string scoreText = "Score: " + std::to_string(score);

    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);

    if (!textSurface) {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        SDL_Log("Unable to create text texture! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    SDL_Rect dstRect = {x, y, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
void GameNgram::updateScore(int& score) {
    // Biến thời điểm trước đó
    std::chrono::steady_clock::time_point lastScoreUpdateTime = std::chrono::steady_clock::now();
    // Lấy thời điểm hiện tại
    auto currentTime = std::chrono::steady_clock::now();

    // Tính khoảng thời gian từ lần cập nhật điểm số trước đó đến thời điểm hiện tại
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastScoreUpdateTime).count();

    // Tốc độ tăng điểm (số điểm tăng mỗi giây)
    double scorePerSecond = 5.0; // Ví dụ: Tốc độ tăng là 5 điểm mỗi giây

    // Tính số điểm tăng dựa trên thời gian đã trôi qua
    int scoreToAdd = static_cast<int>(scorePerSecond * (elapsedTime / 1000.0)); // Đổi milliseconds sang seconds

    // Cập nhật điểm số
    score += scoreToAdd;

    // Cập nhật thời điểm cuối cùng
    lastScoreUpdateTime = currentTime;
}
