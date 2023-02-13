#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect button1 = { 240, 100, 160, 60 };
    SDL_Rect button2 = { 240, 180, 160, 60 };
    SDL_Rect button3 = { 240, 260, 160, 60 };

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    SDL_Quit();
                    return 0;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int x = event.button.x;
                        int y = event.button.y;
                        if (SDL_PointInRect(&((SDL_Point){ x, y }), &button1)) {
                            printf("Button 1 clicked\n");
                        }
                        if (SDL_PointInRect(&((SDL_Point){ x, y }), &button2)) {
                            printf("Button 2 clicked\n");
                        }
                        if (SDL_PointInRect(&((SDL_Point){ x, y }), &button3)) {
                            printf("Button 3 clicked\n");
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &button1);
        SDL_RenderFillRect(renderer, &button2);
        SDL_RenderFillRect(renderer, &button3);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &button1);
        SDL_RenderDrawRect(renderer, &button2);
        SDL_RenderDrawRect(renderer, &button3);

        SDL_RenderPresent(renderer);
    }
}