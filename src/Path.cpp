#include "Path.h"

unsigned short Path::get_coord(unsigned short x_coord, unsigned short y_coord)
{
    //Just see if said point has an object with it
    if(plotted_path[x_coord][y_coord] == 1)
        return 1;

    //No need to have anymore if statements
    return 0;
}


void Path::create_coord(unsigned short x_coord, unsigned short y_coord)
{
    plotted_path[x_coord][y_coord] = 1;
}


void Path::create_path()
{
    //Going to need to check for obstacles by rounding and checking if yheres a point
}