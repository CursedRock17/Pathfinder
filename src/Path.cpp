#include "Path.h"

unsigned short Path::get_coord(unsigned short x_coord, unsigned short y_coord)
{
   //No need to have anymore if statements
    return 0;
}


void Path::create_coord(unsigned short x_coord, unsigned short y_coord)
{
}


void Path::create_path()
{

    //Need to reset the Tileset
    for (int x = 0; x < 64; x++)
			for (int y = 0; y < 32; y++)
			{
				block_nodes[y*64 + x].visited = false;
				block_nodes[y*64 + x].global_val = INFINITY;
				block_nodes[y*64 + x].local_val = INFINITY;
				block_nodes[y*64 + x].parent = nullptr;	// No parents
			}

    //Going to need to check for obstacles
    auto heuristic = [](Node* current_node, Node* ending_node){

        int x_diff = current_node->x_coord - ending_node->x_coord;
        int y_diff = current_node->y_coord - ending_node->y_coord;

        return sqrt((x_diff * x_diff) + (y_diff * y_diff));
    };

    //Have to start with the first node and set it up
    Node* current_node = start_node;
    start_node->local_val = 0.0f;
    start_node->global_val = heuristic(current_node, end_node);

    std::list<Node*> NodesToCheck;
    NodesToCheck.push_back(start_node);

    //Make sure there's still a reason to continue moving through the search
    while(!NodesToCheck.empty() && current_node != end_node){

        NodesToCheck.sort([](Node* rhs, Node* lhs){return rhs->global_val > lhs->global_val; });

        while(!NodesToCheck.empty() && NodesToCheck.front()->visited)
            NodesToCheck.pop_front();        

        if(NodesToCheck.empty())
            break;

        current_node = NodesToCheck.front();
        current_node->visited = true; //Only check a node once

        //Go through Each node
            //Check through each nodes neighbors to find their neighbors etc.
            for(auto const visited_neighbor : current_node->neighbors){
                    //We need to add and do stuff to this neighbor
                if(!visited_neighbor->visited && !visited_neighbor->obstacle)
                    NodesToCheck.push_back(visited_neighbor);

                //Need to create the lowest possible local value, then set that as the parent

                float lowest_value = current_node->local_val + heuristic(current_node, end_node);

                if(lowest_value < visited_neighbor->local_val){
                    //Make the current parent equal to this current node because it means its a shorter path
                    //We can set this neighbors local value to the current path's length
                    visited_neighbor->parent = current_node;
                    visited_neighbor->local_val = lowest_value;

                    visited_neighbor->global_val = visited_neighbor->local_val + heuristic(visited_neighbor, end_node);
                }
            }

    }
}