#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

#define WAVES_SOUND "waves-at-baltic-sea-shore.wav"

#define CLAP_SOUND              "clap.ogg"
#define SNARE_SOUND             "snare.ogg"
#define TECHNO_CLAP_SNARE_SOUND "techno-clap-snare.ogg"
#define REVERB_SNARE_SOUND      "dubstep-reverb-snare.ogg"

int main()
{
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not be initialized!\n"
               "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    //Initialize SDL2_mixer
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        printf("SDL2_mixer could not be initialized!\n"
               "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow("SDL2 audio sample (Press SPACE to pause/play)",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if(!window)
    {
        printf("Window could not be created!\n"
               "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create renderer
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer)
        {
            printf("Renderer could not be created!\n"
                   "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Load .WAV sound
            Mix_Chunk *waves = Mix_LoadWAV(WAVES_SOUND);
            if(!waves)
            {
                printf(".WAV sound '%s' could not be loaded!\n"
                       "SDL_Error: %s\n", WAVES_SOUND, SDL_GetError());
                return 0;
            }

            // Load .OGG sounds
            Mix_Music *clapnsnare1 = Mix_LoadMUS(CLAP_SOUND);
            Mix_Music *clapnsnare2 = Mix_LoadMUS(SNARE_SOUND);
            Mix_Music *clapnsnare3 = Mix_LoadMUS(TECHNO_CLAP_SNARE_SOUND);
            Mix_Music *clapnsnare4 = Mix_LoadMUS(REVERB_SNARE_SOUND);
            if(!clapnsnare1 || !clapnsnare2 || !clapnsnare3 || !clapnsnare4)
            {
                printf("One of the .OGG sounds could not be loaded!\n"
                       "SDL_Error: %s\n", SDL_GetError());
                return 0;
            }

            // Play waves sound
            if(Mix_PlayChannel(-1, waves, 0) == -1)
            {
                printf("Waves sound could not be played!\n"
                       "SDL_Error: %s\n", SDL_GetError());
                Mix_FreeChunk(waves);
                return 0;
            }

         
            // Event loop exit flag
            bool quit = false;

            // Event loop
            while(!quit)
            {
                SDL_Event e;

                // Wait indefinitely for the next available event
                SDL_WaitEvent(&e);

                // User requests quit
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if(e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        if(Mix_Paused(-1))
                            Mix_Resume(-1);
                        else
                            Mix_Pause(-1);
                        break;

                    case SDLK_RIGHT:
                        if(Mix_PlayMusic(clapnsnare1, 1) == -1)
                        {
                            printf(".OGG sound could not be played!\n"
                                   "SDL_Error: %s\n", SDL_GetError());
                        }
                        break;

                    case SDLK_LEFT:
                        if(Mix_PlayMusic(clapnsnare2, 1) == -1)
                        {
                            printf(".OGG sound could not be played!\n"
                                   "SDL_Error: %s\n", SDL_GetError());
                        }
                        break;

                    case SDLK_UP:
                        if(Mix_PlayMusic(clapnsnare3, 1) == -1)
                        {
                            printf(".OGG sound could not be played!\n"
                                   "SDL_Error: %s\n", SDL_GetError());
                        }
                        break;

                    case SDLK_DOWN:
                        if(Mix_PlayMusic(clapnsnare4, 1) == -1)
                        {
                            printf(".OGG sound could not be played!\n"
                                   "SDL_Error: %s\n", SDL_GetError());
                        }
                        break;
                    }
                }

                // Initialize renderer color white for the background
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Clear screen
                SDL_RenderClear(renderer);

                // Set renderer color blue to draw the square
                SDL_SetRenderDrawColor(renderer, 0x19, 0x71, 0xA9, 0xFF);

                // Check pause status
                if(Mix_Paused(-1))
                {
                    // Set renderer color white to draw the pause symbol
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                }


                // Update screen
                SDL_RenderPresent(renderer);
            }

            // Clean up audio
            Mix_FreeChunk(waves);
            Mix_FreeMusic(clapnsnare1);
            Mix_FreeMusic(clapnsnare2);
            Mix_FreeMusic(clapnsnare3);
            Mix_FreeMusic(clapnsnare4);

            // Destroy renderer
            SDL_DestroyRenderer(renderer);
        }

        // Destroy window
        SDL_DestroyWindow(window);
    }

    // Quit SDL2_mixer
    Mix_CloseAudio();

    // Quit SDL
    SDL_Quit();

    return 0;
}
