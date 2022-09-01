#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL_video.h>

class GraphicsClass {
public:

GraphicsClass();
~GraphicsClass();

void Graphics_Loop();
bool Get_Should_Stop();

private:

//The main functions for the SDL
void Graphics_Init();
void Graphics_Terminate();

//Helper Functions
void Graphics_Update();
void Add_Delay();
void Check_Status();


//Window Settings for SDL
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 320;

//SDL Objects
SDL_Rect Pixel;
SDL_Event event;

bool should_stop = false;

};

#endif