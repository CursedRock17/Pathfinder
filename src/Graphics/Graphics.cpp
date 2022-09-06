#include "Graphics.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_scancode.h>

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

    //Use this to check the route and separate a normal function
        for(auto node : p.block_nodes){
            //We already have the coordinate data stored in the Node Class so we can just use that
            Pixel.x = 15 * node.x_coord;
            Pixel.y = 15 * node.y_coord;

            //Create a loop that checks through each thing to see if it's become an obstacle
            if(node.obstacle){
                //Make obstacles light blue
                SDL_SetRenderDrawColor(renderer, 8, 197, 255, 1);
            }

            //Have to check this because it;s easier than checking the whole structure, at least for starting and ending nodes
            else if(node.x_coord == p.start_node->x_coord && node.y_coord == p.start_node->y_coord)
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);

            else if(node.x_coord == p.end_node->x_coord && node.y_coord == p.end_node->y_coord){
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);
            }

            else if(node.visited){
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 1);  
            }

            else {
                //Defualt Squares can be white
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
            }
            //Fill the pxiels will whatever color needs to be set for out path
            SDL_RenderDrawRect(renderer, &Pixel);
            SDL_RenderFillRect(renderer, &Pixel);

        }
        
        if(p.end_node != nullptr)
        {
            Node* pathing = p.end_node;
            while(pathing->parent != nullptr)
            {
                //Need to draw a path to the location

                //Set the points that are apart of the path to yellow
                //Can easily get each points x_coord and set it for the pixel
                Pixel.x = 15 * pathing->x_coord;
                Pixel.y = 15 * pathing->y_coord;

                SDL_SetRenderDrawColor(renderer, 247, 255, 20, 1);

                SDL_RenderDrawRect(renderer, &Pixel);
                SDL_RenderFillRect(renderer, &Pixel);

                pathing = pathing->parent;
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

    Setup_Nodes();
}

void GraphicsClass::Setup_Nodes()
{  

    for(int x = 0; x < MapWidth; x++){
        for(int y = 0; y < MapHeight; y++){
            
            //Create a copy of each pixel and displace it by PIXEL_SIZE            
            Pixel.x = 15 * x;
            Pixel.y = 15 * y;


            //Set A Basic state for all of the block_nodes
            p.block_nodes[y * MapWidth + x].visited = false;
            p.block_nodes[y * MapWidth + x].obstacle = false;
            p.block_nodes[y * MapWidth + x].x_coord = x;
            p.block_nodes[y * MapWidth + x].y_coord = y;
            p.block_nodes[y * MapWidth + x].parent = nullptr;

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
        
            //Fill the pxiels will whatever color needs to be set for out path
            SDL_RenderDrawRect(renderer, &Pixel);
            SDL_RenderFillRect(renderer, &Pixel);
        }
    }

    //These have to be split because we need the data for pointers
    for(int x = 0; x < MapWidth; ++x){
        for(int y = 0; y < MapHeight; ++y){

            //We need to make sure each of these block_nodes has filled out neighbors and that we don't have block_nodes that dont exist
            if(y > 0)
                p.block_nodes[y * MapWidth + x].neighbors.push_back(&p.block_nodes[(y - 1) * MapWidth + (x)]);
            if(y < MapHeight - 1)
                p.block_nodes[y * MapWidth + x].neighbors.push_back(&p.block_nodes[(y + 1) * MapWidth + (x)]);
            if(x > 0)
                p.block_nodes[y * MapWidth + x].neighbors.push_back(&p.block_nodes[(y) * MapWidth + (x - 1)]);
            if(x < MapWidth -1)
                p.block_nodes[y * MapWidth + x].neighbors.push_back(&p.block_nodes[(y) * MapWidth + (x + 1)]);

        }
    }


    //After we fill out the basic information for each node and it's surrounding we need to have a starting and ending node
    p.start_node = &p.block_nodes[(MapHeight / 2) * MapWidth + 1];
    p.end_node = &p.block_nodes[(MapHeight / 2) * MapWidth + MapWidth - 2];
}


void GraphicsClass::Check_Status()
{

    //A General Keystate for our keyboard input
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT){
            should_stop = true;
        }

        if(event.type == SDL_MOUSEBUTTONDOWN){
            //Create an obstacle or move points to these points
            if (key_state[SDL_SCANCODE_LSHIFT]) {
                std::cout << "move start" << std::endl;
            }

            else if(key_state[SDL_SCANCODE_TAB]){
                std::cout << "move end" << std::endl;
            }

            else if(key_state[SDL_SCANCODE_SPACE]){
                std::cout << "Create Obstacle" << std::endl;
            }

            p.create_path();
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


/*



*/