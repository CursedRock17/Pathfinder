#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_video.h>


#include <iostream>

class GraphicsClass {
public:

GraphicsClass();
~GraphicsClass();

void Graphics_Loop();
bool Get_Should_Stop();
void Check_Status();

private:

//The main functions for the SDL
void Graphics_Init();
void Graphics_Terminate();

//Helper Functions
void Graphics_Update();
void Add_Delay();


//Window Settings for SDL
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
int WINDOW_WIDTH = 960;
int WINDOW_HEIGHT = 480;

//SDL Objects
SDL_Rect Pixel;
SDL_Event event;

bool should_stop = false;

};

#endif