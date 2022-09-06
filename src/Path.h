#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <array>

//Get our Node Structure
#include "Node.h"

class Path {
public:

//Need to use a vector of points because we need to allocate based on start and end points

//have to ask for some sort of input in order for these to work, when switching to bigger system
unsigned short get_coord(unsigned short x_coord, unsigned short y_coord);
void create_coord(unsigned short x_coord, unsigned short y_coord);

//Need to access every node to change them
//The nice part about arrays is that they're preallocated
std::array<Node, 2048> block_nodes;

//Need a certain start and stop
Node* start_node = nullptr;
Node* end_node = nullptr;

//use the A* search to find stuff
void create_path();

private:
};

#endif

