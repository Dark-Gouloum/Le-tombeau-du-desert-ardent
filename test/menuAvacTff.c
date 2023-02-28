#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Fonction pour dessiner du texte sur une texture
SDL_Texture* drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color)
{
    // Dessiner le texte sur une surface
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface)
    {
        printf("Erreur : impossible de créer la surface de texte : %s\n", TTF_GetError());
        return NULL;
    }

    // Convertir la surface en texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        printf("Erreur : impossible de créer la texture de texte : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }

    // Libérer la surface devenue inutile
    SDL_FreeSurface(surface);

    return texture;
}

int main()
{
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Erreur : impossible d'initialiser SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Initialiser SDL_ttf
    if (TTF_Init() < 0)
    {
        printf("Erreur : impossible d'initialiser SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Créer la fenêtre et le rendu
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Window* window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Erreur : impossible de créer la fenêtre : %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Erreur : impossible de créer le rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Charger la police TTF
    const char* FONT_FILE = "./Annexe/font/Roboto/Roboto-Regular.ttf";
    TTF_Font* font = TTF_OpenFont(FONT_FILE, 24);
    if (!font)
    {
        printf("Erreur : impossible de charger la police TTF : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Préparer les couleurs des boutons
    SDL_Color colorStart = { 255, 255, 255, 255 };
    SDL_Color colorOptions = { 255, 255, 255, 255 };
    SDL_Color colorQuit = { 255, 255, 255, 255 };

    // Préparer les textures des boutons
    SDL_Texture* textureStart = drawText(renderer, font, "Start", colorStart);
    SDL_Texture* textureOptions = drawText(renderer, font, "Options", colorOptions);
    SDL_Texture* textureQuit = drawText(renderer, font, "Quitter", colorOptions);










    // Vérifier que les textures ont été créées avec succès
    if (!textureStart || !textureOptions || !textureQuit)
    {
        SDL_DestroyTexture(textureStart);
        SDL_DestroyTexture(textureOptions);
        SDL_DestroyTexture(textureQuit);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Positionner les boutons
    SDL_Rect rectStart = { SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 60, 100, 30 };
    SDL_Rect rectOptions = { SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 10, 100, 30 };
    SDL_Rect rectQuit = { SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 + 40, 100, 30 };

    // Boucle principale
    int quit = 0;
    SDL_Event event;
    while (!quit)
    {
        // Gérer les événements
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        int x = event.button.x;
                        int y = event.button.y;

                        // Vérifier si le bouton "Start" a été cliqué
                        if (x >= rectStart.x && x < rectStart.x + rectStart.w && y >= rectStart.y && y < rectStart.y + rectStart.h)
                        {
                            printf("Bouton \"Start\" cliqué !\n");
                        }

                        // Vérifier si le bouton "Options" a été cliqué
                        else if (x >= rectOptions.x && x < rectOptions.x + rectOptions.w && y >= rectOptions.y && y < rectOptions.y + rectOptions.h)
                        {
                            printf("Bouton \"Options\" cliqué !\n");
                        }

                        // Vérifier si le bouton "Quitter" a été cliqué
                        else if (x >= rectQuit.x && x < rectQuit.x + rectQuit.w && y >= rectQuit.y && y < rectQuit.y + rectQuit.h)
                        {
                            quit = 1;
                        }
                    }
                    break;
            }
        }

        // Effacer le rendu
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessiner les boutons
        SDL_RenderCopy(renderer, textureStart, NULL, &rectStart);
        SDL_RenderCopy(renderer, textureOptions, NULL, &rectOptions);
        SDL_RenderCopy(renderer, textureQuit, NULL, &rectQuit);

        // Mettre à jour le rendu
        SDL_RenderPresent(renderer);
    }

    // Libérer la mémoire allouée
    SDL_DestroyTexture(textureStart);
    SDL_DestroyTexture(textureOptions);
    SDL_DestroyTexture(textureQuit);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}