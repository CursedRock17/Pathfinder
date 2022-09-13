#include <iostream>
#include "src/Graphics/Graphics.h"

int main(int argc, char* argv[])
{
    GraphicsClass g;

    std::cout << "Please Choose an Algorithm Number, this will be fixed later" << std::endl;
    g.chosen_algorithm = 1;

    while(!g.Get_Should_Stop()){
        g.Check_Status();
        g.Graphics_Loop();
    }

    return 0;
}