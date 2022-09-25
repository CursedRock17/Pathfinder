#ifndef NODE_H
#define NODE_H

#include <utility>
#include <vector>
#include <cfloat>
#include <string>

class Node {
    public:
    //Position of the pixel
    unsigned short x_coord;
    unsigned short y_coord;
    
    //Sample to see if it needs to go back over
    bool visited{false};
    bool obstacle{false};

    //Global Val is the f(x)
    float global_val = FLT_MAX;
    float local_val = FLT_MAX;

    std::vector<Node*> neighbors;
    Node* parent = nullptr;
};

class D_Node : public Node {
    //In the D Star algo each node needs a list state
    public:
    std::string state{};

};


#endif