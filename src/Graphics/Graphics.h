#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_video.h>

#include "../Path.h"
#include "../Node.h"

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

//Setting up Points
void Setup_Nodes();
void Allocate_Nodes();

//Window Settings for SDL
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
static constexpr int WINDOW_WIDTH = 960;
static constexpr int WINDOW_HEIGHT = 480;

unsigned short MapWidth = 64;
unsigned short MapHeight = 32;

//SDL Objects
SDL_Rect Pixel;
std::vector<SDL_Rect> Nodes;

SDL_Event event;

bool should_stop = false;

//Need to have access to all the pathes so we can draw them
Path p;
Node dummy_node;
};

#endif