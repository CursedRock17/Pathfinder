#ifndef NODE_H
#define NODE_H

#include <utility>
#include <vector>

class Node {
    public:
    //Position of the pixel
    unsigned short x_coord;
    unsigned short y_coord;
    
    //Sample to see if it needs to go back over
    bool visited = false;
    bool obstacle = false;

    int local_val = INT_MAX;
    int global_val = INT_MAX;


    std::vector<Node*> neighbors;
    Node* parent = nullptr;

};


#endif