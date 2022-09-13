#include "Path.h"

void Path::create_dijkstra()
{
    //Create a set that holds our unvisited nodes
    std::list<Node*> unvisited_nodes;

    //Clear the block_nodes excess features
    for(int x = 0; x < grid_length; x++)
        for(int y = 0; y < grid_height; y++){
            block_nodes.at(y * grid_length + x).local_val = INFINITY;
            block_nodes.at(y * grid_length + x).global_val = INFINITY;
            block_nodes.at(y * grid_length + x).visited = false;
            block_nodes.at(y * grid_length + x).parent = nullptr;
            
            unvisited_nodes.push_back(&block_nodes.at(y * grid_length + x));
        }


    //Begin the list by setting uo the first node, will later be the robot
    //Local value is tentative distance value (length of path plus length aka 1)

    start_node->local_val = 0;
    current_node = start_node;   

    unvisited_nodes.push_front(current_node);

    /*
    For current node, check its unvisited neighbors get the local_val
    if the new value is smaller than the old, replace it
    */

    while(!unvisited_nodes.empty() && !end_node->visited){
        for(auto& u_node : current_node->neighbors){
            //We will go through the current nodes neighbors and check if they haven't been visited yet
            
            if(!u_node->visited){
            //At Each neighbor we need to see if they're total tenative distnace is more
            //Than the temporary one, we want the smallest distance possible and all lengths are 1

            float tenative_distance = current_node->local_val + 1;
            if(tenative_distance < u_node->local_val)
                u_node->local_val = tenative_distance;
            }
        }
        //After we go through this node's neighbors we can safe mark it as visited
        //We then pick a new current node in the smallest tenative distance
        current_node->visited = true;
        unvisited_nodes.pop_front();

        //We need to sort to the smallest distance to the front
        unvisited_nodes.sort([](Node* rhs, Node* lhs){ return lhs->global_val < rhs->global_val; } );
        current_node = unvisited_nodes.front();

    }

}

void Path::create_astar()
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
