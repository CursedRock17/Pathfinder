#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <utility>
#include <vector>

class Path {
public:

//Need to use a vector of points because we need to allocate based on start and end points
std::vector<std::pair<unsigned short, unsigned short>> plotted_path{};

//have to ask for some sort of input in order for these to work
void set_start(unsigned short x_coord, unsigned short y_coord);
void set_end(unsigned short x_coord, unsigned short y_coord);

void create_path();

private:

std::pair<unsigned short, unsigned short> start_point{};
std::pair<unsigned short, unsigned short> end_point{};
};

#endif