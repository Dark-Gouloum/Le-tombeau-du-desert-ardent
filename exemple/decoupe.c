#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

SDL_Texture* texture;
SDL_Rect src_rect, dest_rect;

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    // Créer une fenêtre et un renderer
    SDL_Window* window = SDL_CreateWindow("Découper une image BMP en sprites",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Charger l'image BMP en tant que surface
    SDL_Surface* surface = SDL_LoadBMP("animation.bmp");
    if (!surface)
    {
        printf("Erreur de chargement de l'image BMP : %s", SDL_GetError());
        return -1;
    }

    // Créer une texture à partir de la surface
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Libérer la surface
    SDL_FreeSurface(surface);

    // Définir la taille de chaque sprite
    src_rect.w = 20;
    src_rect.h = 20;

    // Définir la position et la taille de l'affichage
    dest_rect.x = 100;
    dest_rect.y = 100;
    dest_rect.w = 32;
    dest_rect.h = 32;

    // Boucle principale
    // Initialiser le compteur d'animation
    int animationCounter = 0;

    // Boucle de rendu
     int quit = 0;
    while (!quit) {

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }
    // Effacer l'écran
    SDL_RenderClear(renderer);

    // Calculer l'index de l'image à afficher
    double spriteIndex =(animationCounter  /1);

    // Récupérer la partie de l'image correspondant au sprite
    SDL_Rect srcRect = { spriteIndex * 20, 0, 20, 20 };

    // Dessiner le sprite sur l'écran
    SDL_RenderCopy(renderer, texture, &srcRect, NULL);

    // Mettre à jour l'écran
    SDL_RenderPresent(renderer);

    SDL_Delay(60);
    // Incrémenter le compteur d'animation
    animationCounter++;
    if(animationCounter == 7)
        animationCounter =0;
}
    // Libérer la texture et le renderer
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    // Quitter SDL2
    SDL_Quit();

    return 0;
}
