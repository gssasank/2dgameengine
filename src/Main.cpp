#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {
    
    std::cout << "Started execution of the main file...." << std::endl;

    Game game; // Since the "new" keyword is not being used here, C++ stores the object in the stack and destroys it when the scope ends.

    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}
