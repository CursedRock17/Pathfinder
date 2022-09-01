#include "Graphics.h"
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_video.h>

GraphicsClass::GraphicsClass()
{
    //Created a Wrapper For the Init
    Graphics_Init();
}

GraphicsClass::~GraphicsClass()
{   
    //Created a Wrapper for the TErminate
    Graphics_Terminate();
}

void GraphicsClass::Graphics_Loop()
{
        //Need to clear the colors and make sure we start by drawing on a black backgrfound
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderClear(renderer);

    //Go through the size of the graphics
    Graphics_Update();

    SDL_RenderPresent(renderer);
    //Check to make sure the window needs to stay up

    Add_Delay();
}

void GraphicsClass::Add_Delay()
{
    SDL_Delay(10);
}

void GraphicsClass::Graphics_Update()
{
    for(int x = 0; x < 32; ++x){
        for(int y = 0; y < 16; ++y){
            
            //Create a copy of each pixel and displace it by PIXEL_SIZE
            Pixel.x = 15 * x;
            Pixel.y = 15 * y;
        
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);

            //Fill the pxiels will whatever color needs to be set for out path
            SDL_RenderDrawRect(renderer, &Pixel);
            SDL_RenderFillRect(renderer, &Pixel);

        }
    }
}

void GraphicsClass::Graphics_Init()
{
    window = SDL_CreateWindow("Pathfinder", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_RENDERER_ACCELERATED);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Init(SDL_INIT_VIDEO);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);

    //Constant Size for the Pixel
    Pixel.h = 14;
    Pixel.w = 14;

}

void GraphicsClass::Check_Status()
{
    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT){
            should_stop = true;
        }
    }
    
}

bool GraphicsClass::Get_Should_Stop()
{
    return should_stop;
}

void GraphicsClass::Graphics_Terminate()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}