#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <cmath>
#include <array>
#include <queue>
#include <stack>

//Get our Node Structure
#include "Node.h"

class Path {
public:
//Need to use a vector of points because we need to allocate based on start and end points

//Need to access every node to change them
//The nice part about arrays is that they're preallocated
std::array<Node, 2048> block_nodes;

//Need a certain start and stop
Node* start_node = nullptr;
Node* end_node = nullptr;
Node* current_node = nullptr;

// ---------------------- Search Alogirthms ------------------- //
void create_astar();
void create_dijkstra();
void create_dstar();
void create_breadth_first();
void create_depth_first();

// ---------------------- Search Alogirthms ------------------- //
private:

unsigned short grid_height = 32;
unsigned short grid_length = 64;


};
#endif

