#include "NonogramButton.hpp"

PushButton::PushButton(int* b, bool* f) : button(b), first(f) {
    rect = { 0, 0, SIZE, SIZE }; // Thiết lập kích thước và vị trí ban đầu của nút
    processed = false;
}

void PushButton::handleEvent(SDL_Event& e, SDL_Renderer* renderer) {
    /*if (e.type == SDL_MOUSEBUTTONDOWN) {
        SDL_MouseButtonEvent* mouseEvent = reinterpret_cast<SDL_MouseButtonEvent*>(&e);
        if (mouseEvent->button != SDL_BUTTON_LEFT && mouseEvent->button != SDL_BUTTON_RIGHT) {
            return;
        }
        *button = mouseEvent->button;
        *first = true;
        processed = true;
        if (mouseEvent->button == SDL_BUTTON_LEFT) {
            std::cout << "Left button pressed!" << std::endl;
        }
        else {
            std::cout << "Right button pressed!" << std::endl;
        }

        // Tạo và gửi sự kiện kéo thả (drag and drop)
        SDL_Event dragEvent;
        dragEvent.type = SDL_USEREVENT;
        dragEvent.user.code = 1;
        SDL_PushEvent(&dragEvent);
    }*/

    if (e.type == SDL_MOUSEBUTTONUP) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        SDL_Point point = { mouseX, mouseY };

        if (SDL_PointInRect(&point, &rect)) {
            SDL_MouseButtonEvent* mouseEvent = reinterpret_cast<SDL_MouseButtonEvent*>(&e);

            if (mouseEvent->button == SDL_BUTTON_LEFT || mouseEvent->button == SDL_BUTTON_RIGHT) {
                *button = mouseEvent->button;
                *first = true;
                processed = true;

                if (mouseEvent->button == SDL_BUTTON_LEFT) {
                    std::cout << "Left button pressed!" << std::endl;
                } else {
                    std::cout << "Right button pressed!" << std::endl;
                }

                // Tạo và gửi sự kiện kéo thả (drag and drop)
                SDL_Event dragEvent;
                dragEvent.type = SDL_USEREVENT;
                dragEvent.user.code = 1;
                SDL_PushEvent(&dragEvent);
            }
        }
    }
}

void PushButton::render(SDL_Renderer* renderer) {
    // Xóa màn hình
    /*SDL_SetRenderDrawColor(renderer, 215, 215, 215, 255);
    SDL_RenderClear(renderer);*/

    // Vẽ nút
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Đặt màu đen
    SDL_RenderFillRect(renderer, &rect); // Vẽ hình chữ nhật (nút)

    // Hiển thị lên màn hình
    SDL_RenderPresent(renderer);
}
