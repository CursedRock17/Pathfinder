#include "Path.h"


void Path::create_dijkstra()
{
    //Create a set that holds our unvisited nodes
    std::list<Node*> unvisited_nodes;

    //Clear the block_nodes excess features
    for(int x = 0; x < grid_length; x++)
        for(int y = 0; y < grid_height; y++){
            block_nodes.at(y * grid_length + x).local_val = INFINITY;
            block_nodes.at(y * grid_length + x).visited = false;
            block_nodes.at(y * grid_length + x).parent = nullptr;
            
            unvisited_nodes.push_back(&block_nodes.at(y * grid_length + x));
        }



    //Begin the list by setting uo the first node, will later be the robot
    //Local value is tentative distance value (length of path plus length aka 1)

    start_node->local_val = 0;
    current_node = start_node;   

    unvisited_nodes.sort([](Node* rhs, Node* lhs){ return lhs->local_val > rhs->local_val; } );
    /*
    For current node, check its unvisited neighbors get the local_val
    if the new value is smaller than the old, replace it
    */

    while(!unvisited_nodes.empty() && !end_node->visited){
        for(auto& u_node : current_node->neighbors){
            //We will go through the current nodes neighbors and check if they haven't been visited yet
            
            if(!u_node->visited && !u_node->obstacle){
            //At Each neighbor we need to see if they're total tenative distnace is more
            //Than the temporary one, we want the smallest distance possible and all lengths are 1

            float tenative_distance = current_node->local_val + 1.0f;
            if(tenative_distance < u_node->local_val){
                u_node->local_val = tenative_distance;
                u_node->parent = current_node;
                }
            }
        }
        //After we go through this node's neighbors we can safe mark it as visited
        //We then pick a new current node in the smallest tenative distance
        current_node->visited = true;

        unvisited_nodes.pop_front();

        //We need to sort to the smallest distance to the front
        unvisited_nodes.sort([](Node* rhs, Node* lhs){ return lhs->local_val > rhs->local_val; } );
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

void Path::create_dstar()
{
    //We'll need to search backwards from the goal node
    //Create our nodes to be evaluated list
    std::list<D_Node*> open_list;
    D_Node* current_node;

    //Clear the block_nodes excess features
    for(int x = 0; x < grid_length; x++)
        for(int y = 0; y < grid_height; y++){
            block_nodes.at(y * grid_length + x).local_val = INFINITY;
            block_nodes.at(y * grid_length + x).visited = false;
            block_nodes.at(y * grid_length + x).parent = nullptr;
        }

    //Set up and add the starting node which is actually the end node
    current_node = static_cast<D_Node*>(end_node);
    current_node->state = "OPEN";
    current_node->local_val = 0;
    current_node->global_val = 0;
    open_list.push_back(current_node);

    //For this algo k(x) is local, h(x) is global, while b(x) is the parent

    while(!open_list.empty() && current_node != start_node){
        //Creating a sorting method for k vals
        auto sorting_k_vals = [](Node* rhs, Node* lhs){
            return rhs->local_val > lhs->local_val;
        };
        open_list.sort(sorting_k_vals);
        current_node = open_list.front();
        //Need to remove and mark the point as closed because it's been traversed

        open_list.pop_front();

        double cost;
        for(auto& neighbor : current_node->neighbors){
            if(!neighbor->visited){
                neighbor->local_val = 1 + current_node->local_val;
                //If it's the first time it's been on the list
                if(static_cast<D_Node*>(neighbor)->state == "NEW")
                    neighbor->global_val = neighbor->local_val;
                
                if(neighbor->global_val > neighbor->local_val)
                    static_cast<D_Node*>(neighbor)->state = "RAISE";

                //If the object is an obstacle then when need to make sure it's never in the path
                if(neighbor->obstacle)
                    neighbor->local_val = 10000;

                //Might have to change how the backtracking will work
                if(neighbor->global_val < current_node->local_val){
                    current_node->parent = neighbor;
                    if(static_cast<D_Node*>(neighbor)->state == "CLOSED")
                        static_cast<D_Node*>(neighbor)->state = "LOWER";
                }
                else 
                    neighbor->parent = current_node;

                open_list.push_back(static_cast<D_Node*>(neighbor));
            }
        }

        static_cast<D_Node*>(current_node)->state = "CLOSED";
        current_node->visited = true;

    }

    //To find the path sort the h values the take the 
    //shortest parent Path from end node to start node
    auto sorting_h_vals = [](Node* rhs, Node* lhs){
            return rhs->global_val > lhs->global_val;
        };
    open_list.sort(sorting_h_vals);

    std::vector<Node*> d_star_path;
    for(auto& lower_node : open_list){
        d_star_path.push_back(lower_node);
        if(lower_node == start_node)
            break;
    }
}


std::vector<Node> Path::create_path()
{
    //Create this vector of nodes that we will give back as the appropriate path to the ending goal
    std::vector<Node> NodesToReturn;

    if(end_node != nullptr)
        {
            Node* pathing = end_node;
            while(pathing->parent != nullptr)
            {
                //If our parent was on the path and it gets closer to the start add it to the queue
                pathing = pathing->parent;
                NodesToReturn.push_back(*pathing);
            }
        }

    return NodesToReturn;
}

void Path::create_breadth_first()
{
    std::queue<Node*> node_q;

    //Clear the block_nodes excess features
    for(int x = 0; x < grid_length; x++)
        for(int y = 0; y < grid_height; y++){
            block_nodes.at(y * grid_length + x).local_val = INFINITY;
            block_nodes.at(y * grid_length + x).visited = false;
            block_nodes.at(y * grid_length + x).parent = nullptr;
               
        }

    start_node->visited = true;
    node_q.emplace(start_node);


    while(!node_q.empty()){
        current_node = node_q.front();
        node_q.pop();
        //Found the end node make the path or smthing
        if(current_node == end_node)
            break;

        for(auto& neighbor_node : current_node->neighbors){
            //Check all the neighbors as we expand outward
            if(!neighbor_node->visited && !neighbor_node->obstacle){
                neighbor_node->visited = true;
                neighbor_node->parent = current_node;
                node_q.emplace(neighbor_node);
            }
        }
    }

}

void Path::create_depth_first()
{
   //Clear the block_nodes excess features
    for(int x = 0; x < grid_length; x++)
        for(int y = 0; y < grid_height; y++){
            block_nodes.at(y * grid_length + x).local_val = INFINITY;
            block_nodes.at(y * grid_length + x).visited = false;
            block_nodes.at(y * grid_length + x).parent = nullptr;
               
        }

    std::stack<Node*> nodes_stack;
    //Only deal with the current node when changing the stack
    current_node = start_node;
    nodes_stack.emplace(current_node);

    while(!nodes_stack.empty() && current_node != end_node){
        //Take and remove the top not
        current_node = nodes_stack.top();
        nodes_stack.pop();
        if(!current_node->visited && !current_node->obstacle){
            current_node->visited = true;
            for(auto& neighbor_node : current_node->neighbors){
                if(!neighbor_node->obstacle && !neighbor_node->visited){
                    neighbor_node->parent = current_node;
                    //TODO:: ADd return type of Node
                    nodes_stack.emplace(neighbor_node);
                }
            }
        }

    }
}