#pragma once
#include <SDL2/SDL.h> 
#include <SDL_ttf.h>

void snakerender(SDL_Rect* snake ,  int total , int grid , int snake_dirx , int snake_diry , SDL_Renderer* render);

class snake123{
    int width = 600;
    int height = 400;
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Event e;
    bool running = true;
    TTF_Font *font;
    int grid = 50;
    int total = 1;
    int snake_dirx = 0, snake_diry = 0;
    int pl_x = width / grid;
    int pl_y = height / grid;

     SDL_Rect snake[100];
     SDL_Rect food;
     bool isInnit = false;
     bool gameRunning = true;
     public:

     void windowInnit();
     void gameLoop();
     void snake_outside();
};