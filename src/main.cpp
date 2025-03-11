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

    int grid = 50;
    int total = 1;
    int snake_dirx = 0 , snake_diry = 0;


    int pl_x = width / grid;
    int pl_y = height / grid;

    SDL_Rect snake[100];
    snake[0].x = 0;
    snake[0].y = 0;
    snake[0].w = grid;
    snake[0].h = grid;



    SDL_Rect food;
    food.x = (rand() % pl_x) * grid;
    food.y = (rand() % pl_y) * grid;
    food.w = 50;
    food.h = 50;

    while (running)
    {
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
            }
        }

        snake[0].x +=  snake_dirx*grid;
        snake[0].y += snake_diry*grid ;
        SDL_Delay(300);

        if(snake[0].x == food.x && snake[0].y == food.y){
            food.x = (rand() % pl_x) * grid;
            food.y = (rand() % pl_y) * grid;
        }

        if(snake[0].x + snake[0].w > width){
            snake[0].x  = 0 - snake[0].w;
        }
        else if(snake[0].x < 0){
            snake[0].x = width;
        }
        else if(snake[0].y < 0){
            snake[0].y = height;
        }
        // else(snake[0].y + snake[0].h > height){
        //     snake[0].y = 0 - snake[0].h ;
        // }



        // for(int i =0 ; i < total ; i ++){
            
            

        //     if(i == 0){
        //         snake[i].w = grid;
        //         snake[i].h = grid;
        //         snake[i].x +=  snake_dirx*grid;
        //         snake[i].y += snake_diry*grid ;
        //         SDL_SetRenderDrawColor(render , 255 , 255 ,255 ,255);
        //         SDL_RenderFillRect(render , &snake[i]);
        //     }
            // else{
            //     snake[i].x = snake[i - 1].x + snake[i].w*snake_dirx ;
            //     snake[i].y = snake[ i - 1 ].y + snake[i].h*snake_diry ;
            //     SDL_SetRenderDrawColor(render , 10 , 255 ,255 ,255);
            //     SDL_RenderFillRect(render , &snake[i]);
            // }
            
        //}




        


        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);



        SDL_SetRenderDrawColor(render , 10 , 255 ,255 ,255);
        SDL_RenderFillRect(render , &snake[0]);



        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderFillRect(render, &food);

        SDL_RenderPresent(render);
    }
}
