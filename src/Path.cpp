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

    //Clear the block_nodes excess features
    for(int x = 0; x < grid_length; x++)
        for(int y = 0; y < grid_height; y++){
            block_nodes.at(y * grid_length + x).local_val = INFINITY;
            block_nodes.at(y * grid_length + x).global_val = INFINITY;
            block_nodes.at(y * grid_length + x).visited = false;
            block_nodes.at(y * grid_length + x).parent = nullptr;
        }

    //Create a heurisitic function that will determine the distance from current_node to end_node
    auto heuristic = [](Node* cur_node, Node* end_node){
        float x_distance = cur_node->x_coord - end_node->x_coord;
        float y_distance = cur_node->y_coord - end_node->y_coord;

        //Square these values
        x_distance *= x_distance;
        y_distance *= y_distance;

        float final_return = sqrt(x_distance + y_distance);

        return final_return;
    };


    //Must Inititalize starting node  
    start_node->local_val = 0.0f; //It's 0 distance from the start
    start_node->global_val = heuristic(start_node, end_node);

    //Create a list which all the nodes that need to be reviewed, go in
    std::list<Node*> NodesToCheck;
    NodesToCheck.push_back(start_node);

    current_node = start_node;
    
    //This loop ends when the path is from start_node to the end_node
    while(!NodesToCheck.empty() && current_node != end_node){
        //Global_Val = g(n) + h(n) : h is the heurisitc, g is the cost of the path from start to nth node

        //At each step sort, and remove the node with the lowest global_val, the f and g of neighbors are then updated
        NodesToCheck.sort([](Node* rhs, Node* lhs){ return lhs->global_val < rhs->global_val; } );
        
        while(!NodesToCheck.empty() && NodesToCheck.front()->visited)
            NodesToCheck.pop_front();

        if(NodesToCheck.empty())
            break;

        current_node = NodesToCheck.front();
        current_node->visited = true;

        //Neighbors should always be added to the list then marked as visited once hit
        for(auto& neighbor_node : current_node->neighbors){
            if(!neighbor_node->visited && !neighbor_node->obstacle)
                NodesToCheck.push_back(neighbor_node);

            //The local_val always adds 1, because that's the distance between
            float lowest_value = current_node->local_val + 1.0f;

            if(lowest_value < neighbor_node->local_val){
            //Make this neighbor node a piece of the path by setting up it's value
                neighbor_node->parent = current_node;
                neighbor_node->local_val = lowest_value;


                neighbor_node->global_val = heuristic(neighbor_node, end_node);
            }
        }

    }

}
