#pragma once

#include <iostream>
#include <SDL2/SDL.h>


#define SIZE 20

class PushButton {
private:
    int* button;
    bool* first;
    bool processed;
    SDL_Rect rect; // Kích thước và vị trí của nút

public:
    PushButton(int* b, bool* f); // Constructor
    void handleEvent(SDL_Event& e, SDL_Renderer* renderer); // Xử lý sự kiện
    void render(SDL_Renderer* renderer); // Vẽ nút
};
