#include <iostream>
#include "src/Graphics/Graphics.h"

int main(int argc, char* argv[])
{
    GraphicsClass g;
    std::string number_algo;

    std::cout << "Please Choose an Algorithm Number: " << std::endl;
    std::cin >> number_algo;
    g.Choose_Algorithm(number_algo);

    while(!g.Get_Should_Stop()){
        g.Check_Status();
        g.Graphics_Loop();
    }

    return 0;
}