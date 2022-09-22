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
            Pixel.x = PixelSize * node.x_coord;
            Pixel.y = PixelSize * node.y_coord;

            //Create a loop that checks through each thing to see if it's become an obstacle
            if(node.obstacle){
                //Make obstacles light blue
                SDL_SetRenderDrawColor(renderer, 8, 197, 255, 1);
            }

            //Have to check this because it;s easier than checking the whole structure, at least for starting and ending nodes
            else if(node.x_coord == p.start_node->x_coord && node.y_coord == p.start_node->y_coord)
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);

            else if(node.x_coord == p.end_node->x_coord && node.y_coord == p.end_node->y_coord){
                SDL_SetRenderDrawColor(renderer, 15, 97, 48, 1);
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
        
        for(auto node_on_path : p.create_path()){
            //get the current coordinate to change colors
                Pixel.x = PixelSize * node_on_path.x_coord;
                Pixel.y = PixelSize * node_on_path.y_coord;

                SDL_SetRenderDrawColor(renderer, 247, 255, 20, 1);

                //Keep the end_node as green
                if(node_on_path.x_coord == p.end_node->x_coord && node_on_path.y_coord == p.end_node->y_coord)
                    SDL_SetRenderDrawColor(renderer, 15, 97, 48, 1);
                else if(node_on_path.x_coord == p.start_node->x_coord && node_on_path.y_coord == p.start_node->y_coord)
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);


                SDL_RenderDrawRect(renderer, &Pixel);
                SDL_RenderFillRect(renderer, &Pixel);
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
            Pixel.x = PixelSize * x;
            Pixel.y = PixelSize * y;


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
    int mouse_x, mouse_y;
    Uint32 mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT){
            should_stop = true;
        }

        //When checking position, just divide by PixelSize and round down for the pixel square
        int mouse_hover_x = floor(mouse_x / PixelSize);
        int mouse_hover_y = floor(mouse_y / PixelSize);

        //These node processes are very cheap due to pointers
        if(event.type == SDL_MOUSEBUTTONDOWN){
            if (key_state[SDL_SCANCODE_LSHIFT]) {
                //Can just set the start node to wherever our mouse is
                p.start_node = &p.block_nodes[mouse_hover_y * MapWidth + mouse_hover_x];
            }

            else if(key_state[SDL_SCANCODE_TAB]){
                //Can just set the end node to wherever our mouse is
                p.end_node = &p.block_nodes[mouse_hover_y * MapWidth + mouse_hover_x];
            }

            else if(key_state[SDL_SCANCODE_SPACE]){
                //Create an obstacle, as the flip of whatever the value here is
                p.block_nodes[mouse_hover_y * MapWidth + mouse_hover_x].obstacle = !p.block_nodes[mouse_hover_y * MapWidth + mouse_hover_x].obstacle;
            }

            switch (chosen_algorithm)
            {
            case 0:
            //Run the A-Star search algo:
                p.create_astar();
                break;
            
            case 1:
            //Run the Dijkstra Algo
                p.create_dijkstra();
                break;
            case 2: 
            //Run the DStar Algo
                p.create_dstar();
                break;

            case 3: 
            //Run the BFS Algo
                p.create_breadth_first();
                break;
            case 4:
                p.create_depth_first();
                break;

            default:
            //We need an algo
                std::cout << chosen_algorithm << std::endl;
                break;
            }

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


int GraphicsClass::Choose_Algorithm(std::string number)
{
    if(number == "0"){
        chosen_algorithm = 0;
        return 0;
    }

    else if(number == "1"){
        chosen_algorithm = 1;
        return 1;
    }

    else if(number == "2"){
        chosen_algorithm = 2;
        return 2;
    }

    else if(number == "3"){
        chosen_algorithm = 3;
        return 3;
    }
    else if(number == "4"){
        chosen_algorithm = 4;
        return 4;
    }

    return -1;

}
/*



*/