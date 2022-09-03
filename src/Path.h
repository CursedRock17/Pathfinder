#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <utility>
#include <vector>

class Path {
public:

//Need to use a vector of points because we need to allocate based on start and end points

//have to ask for some sort of input in order for these to work
//It has to be a short depending on what we reveal
unsigned short get_coord(unsigned short x_coord, unsigned short y_coord);
void create_coord(unsigned short x_coord, unsigned short y_coord);

private:
void create_path();

//Create a maxtrix of the map that we have
unsigned short plotted_path[64][32]{};
};

#endif

