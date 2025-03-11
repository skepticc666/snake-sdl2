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
    bool running = true;
    if (TTF_Init() < 0)
    {
        std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    }

    TTF_Font *font;
    font = TTF_OpenFont("C:\\Programming\\C++\\sdl2 pong\\sample.ttf", 24);
    if (!font)
    {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    int grid = 50;
    int total = 1;
    int snake_dirx = 0, snake_diry = 0;

    int pl_x = width / grid;
    int pl_y = height / grid;

     SDL_Rect snake[100];
    // snake[0].x = 0;
    // snake[0].y = 0;
    // snake[0].w = grid;
    // snake[0].h = grid;

     SDL_Rect food;
    // food.x = (rand() % pl_x) * grid;
    // food.y = (rand() % pl_y) * grid;
    // food.w = 50;
    // food.h = 50;

    bool isInnit = false;
    bool gameRunning = true;

    while (running)
    {

        if (isInnit == false)
        {
            total = 1;
            // SDL_Rect snake[100];
            snake[0].x = 0;
            snake[0].y = 0;
            snake[0].w = grid;
            snake[0].h = grid;

            // SDL_Rect food;
            food.x = (rand() % pl_x) * grid;
            food.y = (rand() % pl_y) * grid;
            food.w = 50;
            food.h = 50;

            isInnit = true;
            gameRunning = true;
        }

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    snake_dirx = 1;

                    snake_diry = 0;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    snake_dirx = -1;
                    snake_diry = 0;
                }
                if (e.key.keysym.sym == SDLK_UP)
                {
                    snake_dirx = 0;
                    snake_diry = -1;
                }
                if (e.key.keysym.sym == SDLK_DOWN)
                {
                    snake_dirx = 0;
                    snake_diry = 1;
                }
                if (e.key.keysym.sym == SDLK_r)
                {
                    if(gameRunning == false){
                        gameRunning = true;
                        isInnit = false;
                    }
                }
            }
        }

        if (gameRunning == false)
        {
            continue;
        }

        // snake[0].x +=  snake_dirx*grid;
        // snake[0].y += snake_diry*grid ;

        if (snake[0].x + snake[0].w > width)
        {
            snake[0].x = 0 - snake[0].w;
        }
        else if (snake[0].x < 0)
        {
            snake[0].x = width;
        }
        else if (snake[0].y < 0)
        {
            snake[0].y = height;
        }
        else if (snake[0].y + snake[0].h > height)
        {
            snake[0].y = 0 - snake[0].h;
        }

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);

        for (int i = total - 1; i >= 0; i--)
        {

            snake[i].w = grid;
            snake[i].h = grid;

            if (i == 0)
            {

                snake[i].x += snake_dirx * grid;
                snake[i].y += snake_diry * grid;
                SDL_SetRenderDrawColor(render, 10, 255, 255, 255);
                SDL_RenderFillRect(render, &snake[i]);
                SDL_SetRenderDrawColor(render, 10, 0, 255, 255);
                SDL_RenderDrawRect(render, &snake[i]);
            }
            else
            {
                // snake[i].x =  snake_dirx*grid;
                // snake[i].y = snake_diry*grid ;
                snake[i].x = snake[i - 1].x; // snake[i].w*snake_dirx*grid ;
                snake[i].y = snake[i - 1].y; // + snake[i].h*snake_diry*grid ;
                SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
                SDL_RenderFillRect(render, &snake[i]);
                SDL_SetRenderDrawColor(render, 10, 0, 255, 255);
                SDL_RenderDrawRect(render, &snake[i]);
            }
        }

        // SDL_Delay(350);

        if (snake[0].x == food.x && snake[0].y == food.y)
        {
            while (true)
            {

                food.x = (rand() % pl_x) * grid;
                food.y = (rand() % pl_y) * grid;
                bool isBreak = true;
                for (int i = 0; i < total; i++)
                {
                    if (food.x == snake[i].x && food.y == snake[i].y)
                    {
                        isBreak = false;
                        break;
                    }
                }

                // else{
                //     SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
                //     SDL_RenderFillRect(render, &food);
                //     total++;
                //     isBreak = true;
                // }

                if (isBreak)
                {
                    total++;
                    break;
                }
            }
        }

        for (int i = 1; i < total; i++)
        {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            {
                gameRunning = false;
                // text initialization begins here
                SDL_Color text_color = {255, 0, 0, 255};
                SDL_Surface *text = TTF_RenderText_Solid(font, "GAME OVER!", text_color);

                SDL_Texture *text_texture = SDL_CreateTextureFromSurface(render, text);
                // text ends begins here

                // text.w;

                SDL_Rect src = {0, 0, text->w, text->h};
                SDL_Rect dest = {width / 2 - text->w * 4 / 2, height / 2 - text->h * 4 / 2, text->w * 4, text->h * 4};
                SDL_RenderCopy(render, text_texture, &src, &dest);
            }
        }

        // SDL_SetRenderDrawColor(render , 10 , 255 ,255 ,255);
        // SDL_RenderFillRect(render , &snake[0]);

        // SDL_SetRenderDrawColor(render , 10 , 255 ,255 ,255);
        // SDL_RenderFillRect(render , &snake[0]);
        SDL_Delay(300);

        // while(true){
        //     if(s
        //                 }nake[0].x == food.x && snake[0].y == food.y){
        //         food.x = (rand() % pl_x) * grid;
        //         food.y = (rand() % pl_y) * grid;
        //         bool isBreak = false;
        //         for(int i = 0 ; i < total  ; i++){
        //             if(food.x == snake[i].x && food.y == snake[i].y){
        //                 break;
        //             }
        //             else{
        //                 SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        //                 SDL_RenderFillRect(render, &food);
        //                 isBreak = true;
        //             }
        //         }
        //         if(isBreak){
        //             total++;
        //             break;
        //         }
        //     }

        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderFillRect(render, &food);

        SDL_RenderPresent(render);
    }
}
