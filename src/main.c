#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/* Function prototypes */
int init_sdl(SDL_Window **window, SDL_Renderer **renderer);
void event_loop(bool *running);
void clean_up(SDL_Window *window, SDL_Renderer *renderer);

/**
 * main - Entry point of the 3D raycasting game
 * 
 * Return: 0 on success, 1 on error
 */
int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    bool running = true;

    if (init_sdl(&window, &renderer) != 0)
        return (1);

    event_loop(&running);

    clean_up(window, renderer);

    return (0);
}

/**
 * init_sdl - Initializes SDL and creates the window and renderer
 * @window: Pointer to the window to be created
 * @renderer: Pointer to the renderer to be created
 * 
 * Return: 0 on success, 1 on failure
 */
int init_sdl(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return (1);
    }

    *window = SDL_CreateWindow("3D Raycasting Game", SDL_WINDOWPOS_CENTERED, 
                               SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, 
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL)
    {
        SDL_DestroyWindow(*window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }

    return (0);
}

/**
 * event_loop - Main loop to process SDL events
 * @running: Pointer to the running flag to control the loop
 */
void event_loop(bool *running)
{
    SDL_Event event;

    while (*running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                *running = false;
            }
        }

        /* Your raycasting rendering code will go here */
    }
}

/**
 * clean_up - Frees SDL resources and quits SDL
 * @window: The SDL window to destroy
 * @renderer: The SDL renderer to destroy
 */
void clean_up(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
