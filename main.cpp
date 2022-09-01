#include <iostream>
#include "src/Graphics/Graphics.h"

int main(int argc, char* argv[])
{
    GraphicsClass g;

    while(!g.Get_Should_Stop()){
        g.Graphics_Loop();
    }

    return 0;
}