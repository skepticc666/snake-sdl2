#define SDL_MAIN_HANDLED

#include <iostream>
#include <header.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

int main()
{
    int width = 600;
    int height = 400;
    SDL_Window *window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event e;
    bool is_running = true;

    int grid = 50;

    int snake_dirx = 0, snake_diry = 0;

    int pl_x = width / grid;
    int pl_y = height / grid;

    SDL_Rect snake;
    snake.x = 0;
    snake.y = 0;
    snake.w = 50;
    snake.h = 50;

    SDL_Rect food;
    food.x = (rand() % pl_x) * grid;
    food.y = (rand() % pl_y) * grid;
    food.w = 50;
    food.h = 50;

    while (is_running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                is_running = false;
            }
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    snake_dirx += 1;
                    // snake_diry = 0;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    snake_dirx -= 1;
                    // snake_diry = 0;
                }
                if (e.key.keysym.sym == SDLK_UP)
                {
                    // snake_dirx = 0;
                    snake_diry -= 1;
                }
                if (e.key.keysym.sym == SDLK_DOWN)
                {
                    // snake_dirx = 0;
                    snake_diry += 1;
                }
            }
        }

        snake.x = snake_dirx * grid;
        snake.y = snake_diry * grid;

        SDL_Delay(100);

        if (snake.x == food.x && snake.y == food.y)
        {
            food.x = (rand() % pl_x) * grid;
            food.y = (rand() % pl_y) * grid;
        }

        // if(snake.x + snake.w > width){
        //     snake.x = width - snake.w;
        //     snake_dirx = snake.x/grid;
        // }
        // if(snake.x < 0){
        //     snake.x = 0;
        // }
        // if(snake.y < 0){
        //     snake.y = 0;
        // }
        // if(snake.y + snake.h > height){
        //     snake.y = height - snake.h;
        // }

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);

        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderFillRect(render, &snake);

        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderFillRect(render, &food);

        SDL_RenderPresent(render);
    }
}
